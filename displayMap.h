#ifndef DISPLAYMAP_H
#define DISPLAYMAP_H
#include"linked.h"

void displayMap(int row, int col, int ** arr, int ** enemyDir, int* playerRow, int* playerCol);
void rotateEnemy(int row, int col, int **arr, int **enemyDir);
void rotateEnemyCounterClock(int row, int col, int **arr, int **enemyDir);
void checkDetectionPlayer(int row, int col, int **arr, int** enemyDir,int* endGame, int* playerRow, int* playerCol);
void movePlayer(int input, int* playerRow, int* playerCol,int* endGame, int ** arr, int ** enemyDir, int row, int col, LINKEDLIST* history);
#endif