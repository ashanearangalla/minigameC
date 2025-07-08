#include <stdlib.h>
#include <stdio.h>
#include "displayMap.h"
#include "random.h"
#include "terminal.h"
#include "newSleep.h"
#include "linked.h"

int main(int argc, char *argv[])
{

    int row, col;
    int ** arr;
    int ** enemyDir;
    int i, j;
    int playerRow, playerCol, endGame;
    char input;
    LINKEDLIST * history = NULL;

    /*Getting map name via args*/
    char *fileName = argv[1];
    FILE *fpRead = fopen(fileName, "r");
    endGame = 0;
    

    initRandom();
    /*Create linked list*/
    history = createLinkedList();


    if (fpRead == NULL)
    {
        perror("Cannot open file");
    }
    else
    {   /*Reading file*/
        fscanf(fpRead, "%d %d", &row, &col);
        printf("row = %d, col = %d\n", row, col);

        /*Storing Map*/
        arr = (int **)malloc(sizeof(int *) * row);

        for (i = 0; i < row; i++)
        {
            arr[i] = (int *)malloc(sizeof(int) * col);
        }

        for (i = 0; i < row; i++)
        {
            for (j = 0; j < col; j++)
            {
                fscanf(fpRead, "%d", &(arr[i][j]));
            }
        }

        /*New enemy direction array which stores enemy direction*/
        enemyDir = (int **)malloc(sizeof(int *) * row);
        for (i = 0; i < row; i++)
        {
            enemyDir[i] = (int *)malloc(sizeof(int) * col);
        }

        for (i = 0; i < row; i++)
        {
            for (j = 0; j < col; j++)
            {
                if(arr[i][j] == 4) {
                    /*Storing random number between 1-4 as direction 1 = Up, 2=Right, 3=Down, 4=Left*/
                    enemyDir[i][j] = random_UCP(1,4);
                }

            }
        }

        while (1)
        {
            /*Exit condition 3= Quit game*/
            if (endGame == 3)
            {
                printf("You quit\n");
                break;
            }
            
            system("clear");
          
            displayMap(row, col, arr, enemyDir, &playerRow, &playerCol);
            
            /*Exit condition 1 = won game*/
            if (endGame == 1)
            {
                printf("You win!\n");
                break;
            }
            /* exit condition 2 = caught to enemy*/
            if (endGame == 2)
            {
                printf("You lose!\n");
                break;
            }
            
            disableBuffer();
            scanf("%c", &input);
            enableBuffer();
            /*Moveplayer*/
            movePlayer(input, &playerRow, &playerCol, &endGame, arr, enemyDir,row, col, history);
            
            /*Rotate enemy if game in in progress*/
            if(endGame == 0 && input != 'u') {
                rotateEnemy(row, col, arr, enemyDir);
                
            }
            /*Check whether enemy detect the player*/
            checkDetectionPlayer(row,col, arr, enemyDir,&endGame, &playerRow, &playerCol);
            
            newSleep(0.05);
        }

         
        /*Free Enemy 2D array*/
        for (i = 0; i < row; i++)
        {
            free(enemyDir[i]);
        }
        free(enemyDir);

        /*Free map*/
        for (i = 0; i < row; i++)
        {
            free(arr[i]);
        }
        free(arr);
        arr = NULL;
        
        fclose(fpRead);
    }
    /*Free linked list*/
    freeList(history, freePosition);
    free(history);
    history = NULL;

    return 0;
}