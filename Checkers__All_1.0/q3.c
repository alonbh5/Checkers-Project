#include "q3.h"

//================================================================================================================================================
															 /*STATIC FUNCTIONS*/

static void insertDataToEndList_v2(MultiSourceMovesList *lst, MultiSourceMovesListCell *cell);
static MultiSourceMovesListCell *Allocate_Cell2(SingleSourceMovesList *single_lst_data);
static MakeEmptyListMulti(MultiSourceMovesList *lst);
//================================================================================================================================================

//Question 3
//INPUT:gets a board, and player (t or p)
//OUTPUT:return all posible moves of player in multi list
//------------------------------------------------------------------------------------------------------------------------------------------------
MultiSourceMovesList *FindAllPossiblePlayerMoves(Board board, Player player)
{
	int row, col,pons;
	checkersPos pos;
	SingleSourceMovesTree *root;
	SingleSourceMovesList *single_lst;
	MultiSourceMovesList *res;
	

	res = (MultiSourceMovesList*)malloc(sizeof(MultiSourceMovesList));
	checkalloction(res);
	pons = 0;

	MakeEmptyListMulti(res);

	for (row = 0; row < BOARD_SIZE; row++)
		for (col = 0; col < BOARD_SIZE && pons !=12 ; col++)
		{
			if (board[row][col] == player)
			{
				pos = Int_To_Pos(row, col);
				root = FindSingleSourceMoves(board, &pos);
				single_lst = FindSingleSourceOptimalMove(root);
				if (single_lst->head != single_lst->tail) ///there is a move
				{
					insertDataToEndList_v2(res, Allocate_Cell2(single_lst));
				}

				freeTree(root);
				pons++;
			}
		}

	//FREE FREE FREE FREE
	return res;
}
//------------------------------------------------------------------------------------------------------------------------------------------------

//INPUT:Multi list and multi cell
//OUTPUT:add cell to end of list
//------------------------------------------------------------------------------------------------------------------------------------------------
static void insertDataToEndList_v2(MultiSourceMovesList *lst, MultiSourceMovesListCell *cell)
{
	

	if (lst->head == NULL) //case list is empty
	{
		lst->head = cell;
		lst->tail = cell;
	}
	else
	{
		lst->tail->next = cell;
		lst->tail = cell;
	}


}
//------------------------------------------------------------------------------------------------------------------------------------------------

//INPUT:gets data (single lst)
//output: allcoate a new cell with data and return it
//------------------------------------------------------------------------------------------------------------------------------------------------
static MultiSourceMovesListCell *Allocate_Cell2(SingleSourceMovesList *single_lst_data)
{
	//FIX
	MultiSourceMovesListCell *newcell;


	newcell = (MultiSourceMovesListCell*)malloc(sizeof(MultiSourceMovesListCell)); // make space for new node


	checkalloction(newcell);




	newcell->next = NULL;
	newcell->single_source_moves_list = single_lst_data;

	return (newcell);

}
//------------------------------------------------------------------------------------------------------------------------------------------------


static MakeEmptyListMulti(MultiSourceMovesList *lst)
{
	lst->head = NULL;
	lst->tail = NULL;
}
//------------------------------------------------------------------------------------------------------------------------------------------------