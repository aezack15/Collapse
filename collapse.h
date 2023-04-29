#ifndef _COLLAPSE_H
#define _COLLAPSE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>

typedef struct{
int rows;
int cols;
int colors;
}gameBoard;

typedef struct{
int row;
int col;
}boardIndex;

typedef struct{
char item;
bool isVisited;
bool completeCol;
}gamePiece;

gameBoard setDifficulty();
gamePiece** createBoard(gameBoard);
void displayBoard(int,int,gamePiece**,double);
boardIndex getMove(int,int,gamePiece**);
bool legalMove(gamePiece**, boardIndex,gameBoard);
double removePieces(gamePiece**,int,int,char,gameBoard,double,int);
void collapse(gamePiece**,gameBoard);
void compress(gamePiece**,gameBoard);
bool anyMoveRemaining(gamePiece**,gameBoard);
bool anotherTry(gamePiece**,gameBoard);
void setVisited(gamePiece**,gameBoard);
void setCompletedCols(gamePiece**,gameBoard);
bool playerWins(gamePiece**,gameBoard);

#endif