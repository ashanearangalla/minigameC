#include<stdlib.h>
#include<stdio.h>
#include"displayMap.h"
#include"random.h"


void displayMap(int row, int col, int ** arr) {

    int i,j, rand;

    for(i = 0; i < col+2; i++) { 
            printf("*");
        }
        printf("\n");

        for(i = 0; i < row; i++) {
            printf("*");
            for(j = 0; j < col; j++) {

                if(arr[i][j] == 3) {
                    printf("0");
                } else if (arr[i][j] == 0) {
                    printf(" ");
                } else if(arr[i][j] == 4) {
                    rand = random_UCP(1,4);
                    displayEnemyRand(rand);
                    
                } else if(arr[i][j] == 2) {
                    printf("G");
                } else if(arr[i][j] == 1) {
                    printf("P");
                }else {

                }
                
            }
            printf("*\n");
           
            
        }

        for(i = 0; i < col+2; i++) { 
            printf("*");
        }
        printf("\n");
}

void displayEnemyRand(int rand) {
    if(rand == 1) {
        printf("^");
    } else if(rand == 2) {
        printf(">");
    } else if(rand == 3) {
        printf("v");
    } else {
        printf("<");
    }
}