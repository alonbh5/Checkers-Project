#pragma once

#include "q2.h"
#include "q1.h"



//-----------structs---------------------structs---------------------structs---------------------structs---------------------structs------------
typedef struct _multipleSourceMovesListCell
{
	SingleSourceMovesList *single_source_moves_list;
	struct _multipleSourceMovesListCell *next;
}MultiSourceMovesListCell;

typedef struct _multipleSourceMovesList
{
	MultiSourceMovesListCell *head;
	MultiSourceMovesListCell *tail;
}MultiSourceMovesList;

//-----------structs---------------------structs---------------------structs---------------------structs---------------------structs------------
//----------------------------------------------------------------------------------------------------------------------------------------------

//************prototype************************prototype************************prototype************************prototype**********************

MultiSourceMovesList *FindAllPossiblePlayerMoves(Board board, Player player); //Q3
//************prototype************************prototype************************prototype************************prototype**********************
