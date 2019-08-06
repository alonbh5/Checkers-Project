#include "q4.h"

//================================================================================================================================================
															 /*STATIC FUNCTIONS*/

static void Change_Board(Board board, SingleSourceMovesList *move);
static SingleSourceMovesList *choose_turn(MultiSourceMovesList *multi_lst);
static void FreeMultiList(MultiSourceMovesList *lst);
//================================================================================================================================================

//Question 4
//INPUT:gets a board and a player
//OUTPUT:make a move with player using q1,q2,q3
//------------------------------------------------------------------------------------------------------------------------------------------------
void Turn(Board board, Player player)
{
	MultiSourceMovesList *multi_lst;
	SingleSourceMovesList *best_choice;
	int old_row, old_col;

	multi_lst = FindAllPossiblePlayerMoves(board, player);

	///(q3 will return empty list if no moves)
	if (multi_lst->head) ///if there are moves for player 
	{
		best_choice = choose_turn(multi_lst);
		Pos_To_Int(&old_row, &old_col, best_choice->head->position);
		Change_Board(board, best_choice);  
		printf("%c%c->%c%c\n", best_choice->head->position->row, best_choice->head->position->col, best_choice->tail->position->row, best_choice->tail->position->col);
		FreeMultiList(multi_lst);
	}
	


}
//------------------------------------------------------------------------------------------------------------------------------------------------

//INPUT:gets the moves list X
//OUTPUT:return single list (choose one  from list X)
//------------------------------------------------------------------------------------------------------------------------------------------------
static SingleSourceMovesList *choose_turn(MultiSourceMovesList *multi_lst)
{
	

	MultiSourceMovesListCell *cur,*res;
	unsigned short best;


	
	cur = multi_lst->head;
	res = cur;
	if (cur)
	{
		best = cur->single_source_moves_list->tail->captures;
		cur = cur->next;
		

		while (cur)
		{
			if (best <= cur->single_source_moves_list->tail->captures)
			{
				if (best == cur->single_source_moves_list->tail->captures)
				{
					if (rand() % 2)
					{
						best = cur->single_source_moves_list->tail->captures;
						res = cur;
					}
				}
				else
				{
					best = cur->single_source_moves_list->tail->captures;
					res = cur;
				}
			}
			cur = cur->next;
		}
	}
	else
	{
		printf("Q4-Choose turn error finding list head");
		exit(-4);
	}

	return (res->single_source_moves_list);
}
//------------------------------------------------------------------------------------------------------------------------------------------------

//INPUT:get a board and move list
//OUTPUT:update the board acording to list, delete eats if need to
//------------------------------------------------------------------------------------------------------------------------------------------------
static void Change_Board(Board board, SingleSourceMovesList *move)
{
	
	

	int i, j,cur_row,cur_col,new_row, new_col;
	char player;
	SingleSourceMovesListCell *cur_cell;

	
	cur_cell = move->head;

	

	while (cur_cell && cur_cell->next)
	{
		Pos_To_Int(&cur_row, &cur_col, cur_cell->position);
		cur_cell = cur_cell->next;
		Pos_To_Int(&new_row, &new_col, cur_cell->position);
		player = board[cur_row][cur_col];

		board[cur_row][cur_col] = '0'; ///delete old loction
		board[new_row][new_col] = player; /// move to new loction



		if (cur_row - new_row == 2 || cur_row - new_row == -2)///case eat
		{
			if (player == 'B')
				i = -1;
			else
				i = 1;

			if (cur_col > new_col) ///that mean is a  left eat
				j = cur_col - 1;
			else /// case right eat
				j = cur_col + 1;


			board[cur_row + i][j] = '0'; ///delete the eat
		}
		
	}

}
//------------------------------------------------------------------------------------------------------------------------------------------------

//INPUT: gets a multi move list
//OUTPUT: Free all memory alloction
static void FreeMultiList(MultiSourceMovesList *lst)
{
	MultiSourceMovesListCell *cur;

	cur = lst->head;

	while (cur)
	{
		freeList(cur->single_source_moves_list);
		cur = cur->next;
	}
	free(lst);
}
//------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------