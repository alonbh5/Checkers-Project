#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "tree.h"



//-----------structs---------------------structs---------------------structs---------------------structs---------------------structs------------

typedef struct _SingleSourceMovesListCell
{
	checkersPos *position;
	unsigned short captures;
	struct _SingleSourceMovesListCell *next;
}SingleSourceMovesListCell;

typedef struct _SingleSourceMovesList
{
	SingleSourceMovesListCell *head;
	SingleSourceMovesListCell *tail;

}SingleSourceMovesList;
//-----------structs---------------------structs---------------------structs---------------------structs---------------------structs------------

//************prototype************************prototype************************prototype************************prototype**********************

void freeList(SingleSourceMovesList *lst);
void insertDataToEndList(SingleSourceMovesList *lst, SingleSourceMovesListCell *cell);
void insertDataToMiddleList(SingleSourceMovesListCell *before, SingleSourceMovesListCell *Ist_cell);
void insertDataToHeadList(SingleSourceMovesList *lst, SingleSourceMovesListCell *cell);
void makeEmptyList(SingleSourceMovesList *lst);
SingleSourceMovesListCell *Allocate_Cell(unsigned short captures, checkersPos position);

//************prototype************************prototype************************prototype************************prototype**********************


