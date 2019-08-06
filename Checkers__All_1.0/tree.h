#pragma once


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//=======define===============define===============define===============define===============define===============define===============define===
#define _CRT_SECURE_NO_WARNINGS

typedef int BOOL;

#define FALSE 0

#define TRUE 1

#define BOARD_SIZE 8

#define LEFT 0

#define RIGHT 1

//=======define===============define===============define===============define===============define===============define===============define===



//-----------structs---------------------structs---------------------structs---------------------structs---------------------structs------------
typedef struct _checkersPos
{
	char row, col;
}checkersPos;

typedef unsigned char Board[BOARD_SIZE][BOARD_SIZE];

typedef unsigned char Player;

typedef struct _SingleSourceMovesTreeNode
{
	Board board;
	checkersPos *pos;
	unsigned short total_captures_so_far; //num of dilogim so far
	struct _SingleSourceMovesTreeNode *next_move[2]; //destny of movement
}SingleSourceMovesTreeNode;

typedef struct _SingleSourceMovesTree
{
	SingleSourceMovesTreeNode *source;
}SingleSourceMovesTree;
//-----------structs---------------------structs---------------------structs---------------------structs---------------------structs------------

//************prototype************************prototype************************prototype************************prototype**********************

void freeTree(SingleSourceMovesTree *tree);
SingleSourceMovesTreeNode *AllocateSingleSourceMovesTreeNode(unsigned short newcap, checkersPos position, Board newborad);
void checkalloction(void *ptr);
void ClearTreeAux(SingleSourceMovesTreeNode *source);
int Tree_Node_Count(SingleSourceMovesTreeNode *root);
int Tree_Leaf_Count(SingleSourceMovesTreeNode *root);
void printtree(SingleSourceMovesTreeNode *root, int space);

//************prototype************************prototype************************prototype************************prototype**********************


