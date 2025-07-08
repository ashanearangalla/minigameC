#include<stdlib.h>
#include<stdio.h>
#include"displayMap.h"
#include"random.h"
#include"newSleep.h"


/*All gameplay operations including displaying map, detection to enemy, moving playee etc.*/
void displayMap(int row, int col, int ** arr, int ** enemyDir, int* playerRow, int* playerCol) {

    int i,j;

    for(i = 0; i < col+2; i++) { 
            printf("*");
        }
        printf("\n");

        for(i = 0; i < row; i++) {
            printf("*");
            for(j = 0; j < col; j++) {
                /*Wall*/
                if(arr[i][j] == 3) {
                    printf("0");
                } else if (arr[i][j] == 0) {
                    printf(" ");
                } /*Enemy*/
                else if(arr[i][j] == 4) {
                    /* 1 = UP, 2 = RIGHT, 3 = DOWN, 4 = LEFT*/
                    if(enemyDir[i][j] == 1) {
                        printf("^");
                    } else if(enemyDir[i][j] == 2) {
                        printf(">");
                    } else if(enemyDir[i][j] == 3) {
                        printf("v");
                    } else {
                        printf("<");
                    }
                    
                }/*Goal*/
                else if(arr[i][j] == 2) {
                    printf("G");
                } else if(arr[i][j] == 1) {
                    printf("P");
                    *playerRow = i;
                    *playerCol = j;
                }else {

                }
                
            }
            printf("*\n");
           
            
        }

        for(i = 0; i < col+2; i++) { 
            printf("*");
        }
        printf("\n");
        printf("Press 'w' to move up");
        printf("\nPress 's to move down");
        printf("\nPress 'a' to move left");
        printf("\nPress 'd' to move right");
        printf("\nPress 'u' to move undo");
        printf("\nPress 'q' to move quit\n");
    
}
/*Check whether player is inline with an enemy*/
void checkDetectionPlayer(int row, int col, int **arr, int** enemyDir, int* endGame,int* playerRow, int* playerCol) {
    int i, j;
    for(i = 0; i< row; i++) {
        for(j=0; j< col; j++) {

            if(arr[i][j] == 4) { 
                int dir = enemyDir[i][j];
                int detected = 0;
                int k;
                /*Up*/
                if( dir == 1 && j == *playerCol && i > *playerRow) {
                    detected = 1;
                    for(k = i -1; k > *playerRow; k--) { /*Wall*/
                        if(arr[k][j] == 3) {
                            detected = 0;
                            break;
                        }
                    }
                    
                }
                /*Right*/
                else if( dir == 2 && i == *playerRow && j < *playerCol) {
                    detected = 1;
                    for(k = j+1; k < *playerCol; k++) {
                        if(arr[i][k] == 3) {
                            detected = 0;
                            break;
                        }
                    }
                    
                }
                /*Down*/
                else if( dir == 3 && j == *playerCol && i < *playerRow) {
                    detected = 1;
                    for(k = i+1; k < *playerRow; k++) {
                        if(arr[k][j] == 3) {
                            detected = 0;
                            break;
                        }
                    }
                }
                /*Left*/
                else if( dir == 4 && i == *playerRow && j > *playerCol) {
                    detected = 1;
                    for(k = j-1; k > *playerCol; k--) {
                        if(arr[i][k] == 3) {
                            detected = 0;
                            break;
                        }
                    }
                    
                }

                if (detected) {
                    /*Endgame key 2 = Caught to enemy*/
                    *endGame = 2;
                    arr[i][j] = 0; /*Clearing Enemy Location*/
                    enemyDir[i][j] = 0; /*Storing enemy Direstion*/
                    /*Animation*/
                    while(i != *playerRow || j != *playerCol) {
                        if(i < *playerRow) {
                            i++;
                        } else if(i > *playerRow) {
                            i--;
                        } else if(j < *playerCol) {
                            j++;
                        } else if(j > *playerCol) {
                            j--;
                        } else {
                            break;
                        }

                        arr[i][j] = 4; /*Next grid become enemy location*/
                        enemyDir[i][j] = dir; /*Direction of the enemu*/
                        system("clear");
                        displayMap(row, col, arr, enemyDir, playerRow, playerCol);
                        newSleep(0.5);
                        arr[i][j] = 0;
                    }
                    arr[i][j] = 4;
                    return;

                }

            }
        }
    }
}



void rotateEnemy(int row, int col, int **arr, int **enemyDir) {
    int i,j;
    for(i = 0; i < row; i++) {
        
        for(j = 0; j < col; j++) {
            if(arr[i][j] == 4) {
                /*Modulus returns reminder*/
                enemyDir[i][j] = (enemyDir[i][j] % 4) + 1;
            }
        }
    }
}

/*For undo*/
void rotateEnemyCounterClock(int row, int col, int **arr, int **enemyDir) {
    int i,j;
    for(i = 0; i < row; i++) {
        
        for(j = 0; j < col; j++) {
            if(arr[i][j] == 4) {
                enemyDir[i][j]--;
                if(enemyDir[i][j] == 0) {
                    enemyDir[i][j] = 4;
                }
            }
        }
    }
}

void movePlayer(int input, int* playerRow, int* playerCol,int* endGame, int ** arr,int ** enemyDir, int row, int col, LINKEDLIST* history) {
    int newRow,newCol;
    Position *pos;
   
   newRow = *playerRow;
   newCol = *playerCol;
    /*Undo*/
    if(input == 'u') {
        if(history->head !=NULL) {
            /*Getting last position via tail*/
            Position *lastPos = history->tail->data;
            arr[*playerRow][*playerCol] = 0;
            *playerRow = lastPos->row;
            *playerCol = lastPos->col;;
            arr[*playerRow][*playerCol] = 1;
            removeLast(history, freePosition);
            rotateEnemyCounterClock(row,col, arr, enemyDir);

        }
        return;
    }
    
    if(input == 'w') {
        newRow--;
    } else if(input == 's') {
        newRow++;
    } else if(input == 'a') {
        newCol--;
    } else if(input == 'd') {
        newCol++;
    } else if(input == 'q') {
        /*Endgame key 3 refers to quit*/
        *endGame=3;
    } else {
        return;
    }

    if(newRow < 0 || newRow >=row || newCol <0 || newCol >=col) {
        return;
    }
    /*Storing new position in the linked list*/
    pos =(Position*) malloc(sizeof(Position));
    pos->row = *playerRow;
    pos->col = *playerCol;
    insertLast(history,pos);

    if(arr[newRow][newCol] == 3) {
        return;
    }

    if(arr[*playerRow][*playerCol] == 1) {
        arr[*playerRow][*playerCol] = 0;
    }

    if(arr[newRow][newCol] == 2) {
        /*Endgame key 2 refers to win*/
        *endGame = 1;
    }

    if(arr[newRow][newCol] == 4) {
        /*Endgame key 2 refers to caught to enemy*/
        *endGame = 2;
    }

    
    

    arr[newRow][newCol] = 1;
    *playerRow = newRow;
    *playerCol = newCol;

    
}