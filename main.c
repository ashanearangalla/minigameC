#include<stdlib.h>
#include<stdio.h>
#include"displayMap.h"
#include"random.h"


int main(int argc, char * argv[]) {

    char * fileName = argv[1];

    
    int row, col;
    int ** arr;
    int i,j;
    FILE * fpRead = fopen (fileName, "r");
    initRandom();

    if(fpRead == NULL) {
        perror("Cannot open file");
    } else {
        fscanf(fpRead, "%d %d", &row, &col);
        printf("row = %d, col = %d\n", row, col);

        arr= (int**)malloc(sizeof(int *) * row);

        for(i = 0; i < row; i++) {
            arr[i] = (int*)malloc(sizeof(int) * col);
        }

        for(i = 0; i < row; i++) {
            for(j = 0; j < col; j++) {
                fscanf(fpRead,"%d", &(arr[i][j]));
            }
            
        }

        displayMap(row, col, arr);
        
        

        for(i = 0; i < row; i++) {
            free(arr[i]);
        }
        free(arr);
        arr= NULL;
        fclose(fpRead);
    }

    return 0;
}