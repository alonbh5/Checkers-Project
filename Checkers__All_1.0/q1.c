#include "q1.h"
#include "q7.h"
//================================================================================================================================================
															 /*STATIC FUNCTIONS*/

static void BuildMoveTreeAux(SingleSourceMovesTreeNode *root, int col, int row, unsigned short eats, char player, BOOL Moved_Flag);
static BOOL checkpos(checkersPos *pos);
static Board *Copy_Board(Board old, checkersPos newpos, int cur_row, int cur_col);

//================================================================================================================================================


//------------------------------------------------------------------------------------------------------------------------------------------------
//Question 1
//INPUT: Borad and postion x
//output:Move tree to The player in x ,
//1.NULL if invalid postion or no player there
//2.Tree with only one source (root) if there are NO moves
SingleSourceMovesTree *FindSingleSourceMoves(Board board, checkersPos *src)
{


	int row, col;
	SingleSourceMovesTree *res;
	

	
	Pos_To_Int(&row, &col, src);
	

	if (board[row][col] == '0' || !(checkpos(src)))
		return NULL;
	else
	{
		res = (SingleSourceMovesTree*)malloc(sizeof(SingleSourceMovesTree));
		checkalloction(res);
		res->source = AllocateSingleSourceMovesTreeNode(0, *src, board); //the first node will have the info that was recive
		BuildMoveTreeAux(res->source, col, row, 0, board[row][col], TRUE);
		if (res->source->next_move[RIGHT] == NULL && res->source->next_move[LEFT] == NULL) //CASE OF NO MOVES was asked to return NULL
		{
			freeTree(res);
			res = NULL;
		}
		return (res);
	}

}
//------------------------------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------------------------------
//info:recursive function that bulid move tree for a snigle pon, 
//!!ASSUME VALID INPUT!!! 
//INPUT:TREE root  (already filed ) at starting point,player loaction on board,
//how many eats at start (0),witch player is playing and if moved already flag (TRUE)
//OUTPUT: All Posible moves for player filled into root, end case of no moves will not change anything
static void BuildMoveTreeAux(SingleSourceMovesTreeNode *root, int col, int row, unsigned short eats, char player, BOOL Moved_Flag)
{

	SingleSourceMovesTreeNode *cur;
	checkersPos pos;
	Board *newboard;

	int x, left, right,end;

	left = 0;
	right = BOARD_SIZE-1;

	if (player == 'B') //Restriction and calculations are determined by which player
	{
		x = -1;
		end = 0;

	}
	else  //case T
	{
		x = 1;
		end = BOARD_SIZE-1;

	}




	if (row != end) ///if game is not over
	{
		if (root->board[row + x][col - 1] == player && root->board[row + x][col + 1] == player) ///1.no place to move because you are block by yourself
		{
			root->next_move[LEFT] = NULL;
			root->next_move[RIGHT] = NULL;
		}

		else
		{
			//case left
			if (col == left) ///2.no left
			{
				root->next_move[LEFT] = NULL;
			}
			else
			{
				if (root->board[row + x][col - 1] == '0') ///2.1.your left if free
				{
					if (Moved_Flag)
					{
						pos = Int_To_Pos(row + x, col - 1);
						newboard = Copy_Board(&root->board, pos, row, col); ///defenition of node is with a board
						cur = AllocateSingleSourceMovesTreeNode(eats, pos, *newboard);
						free(newboard);
						root->next_move[LEFT] = cur;
						BuildMoveTreeAux(cur, col - 1, row + x, eats, player, FALSE);
						
					}


				}
				else
				{
					if (col != 1) 
					{
						if (root->board[row + x][col - 1] != player && root->board[row + (2 * x)][col - 2] == '0') ///2.2 your left if enemy and free after
						{
							if (Moved_Flag)
							{
								pos = Int_To_Pos(row + (2 * x), col - 2);
								newboard = Copy_Board(&root->board, pos, row, col);
								cur = AllocateSingleSourceMovesTreeNode(eats + 1, pos, *newboard);
								free(newboard);
								root->next_move[LEFT] = cur;
								BuildMoveTreeAux(cur, col - 2, row + (2 * x), eats + 1, player, FALSE);
							}

						}
					}
				}
			}
			//case right
			if (col == right) ///3 no right
			{
				root->next_move[RIGHT] = NULL;
			}
			else
			{
				///3.1.your right if free
				if (root->board[row + x][col + 1] == '0')
				{
					if (Moved_Flag)
					{
						pos = Int_To_Pos(row + x, col + 1);
						newboard = Copy_Board(&root->board, pos, row, col);
						cur = AllocateSingleSourceMovesTreeNode(eats, pos, *newboard);
						free(newboard);
						root->next_move[RIGHT] = cur;
						BuildMoveTreeAux(cur, col + 1, row + x, eats, player, FALSE);
					}
				}
				else
				{
					///3.2.your right if enemy
					if (col != 6) 
					{
						if (root->board[row + x][col + 1] != player && root->board[row + (2 * x)][col + 2] == '0')
						{
							if (Moved_Flag)
							{
								pos = Int_To_Pos(row + (2 * x), col + 2);
								newboard = Copy_Board(&root->board, pos, row, col);
								cur = AllocateSingleSourceMovesTreeNode(eats + 1, pos, *newboard);
								free(newboard);
								root->next_move[RIGHT] = cur;
								BuildMoveTreeAux(cur, col + 2, row + (2 * x), eats + 1, player, FALSE);
							}
						}
					}
				}
			}

		}
	}







}
//------------------------------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------------------------------
//INPUT:board ,postion on board (2 ints) and loction for a new postion
//OUTPUT: new board that move the player to a new location (delete other player in case of eat)
static Board *Copy_Board(Board old, checkersPos newpos, int cur_row, int cur_col)
{
	
	

	Board *res;
	int i, j, new_row, new_col;
	char player;

	Pos_To_Int(&new_row, &new_col, &newpos);
	player = old[cur_row][cur_col];

	res = (Board*)malloc(sizeof(Board));
	checkalloction(res);

		checkalloction(memcpy(res, old, sizeof(Board))); ///copy board

	(*res)[cur_row][cur_col] = '0'; ///delete old loction
	(*res)[new_row][new_col] = player; /// move to new loction



	if (cur_row - new_row == 2 || cur_row - new_row == -2)///case eat
	{
		if (player == 'B')
			i = -1;
		else
			i = 1;

		if (cur_col > new_col) ///"left" eat
			j = cur_col - 1;
		else 
			j = cur_col + 1;


		(*res)[cur_row + i][j] = '0';
	}

	//
	//remove // if you want to see every step
	//printf("the new move!! : \n");
	//Print_Board(*res);
	//

	return res;

}
//------------------------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------------------------
//INPUT:Positon by int
//OUTPUT:Positon by char
checkersPos Int_To_Pos(int row, int col)
{
	//return formal postion type "A-3"
	checkersPos res;

	res.col = (char)(col + 1 + (int)('0'));
	res.row = (char)(row + (int)'A');
	return res;
}
//------------------------------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------------------------------
//INPUT:pointers to :2 ints (row and col) and one position by chars
//OUTPUT:fill row and col in int form 
void Pos_To_Int(int *row, int *col, checkersPos *pos)
{
	
	*col = (int)(pos->col - '0');
	*row = (int)(pos->row - 'A');
	(*col)--;

}
//------------------------------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------------------------------
//INPUT:player position for 8x8 board
//OUTPUT:FALSE if positon is
//1.row is not a cap letter
//2.col is not number
//3.positon is not on playable square
static BOOL checkpos(checkersPos *pos)
{
	

	if (pos->row < 'A' || pos->row > 'H')
		return (FALSE);
	if (pos->col < '1' || pos->col > '8')
		return (FALSE);
	if (!(pos->row - pos->col) % 2)///only black tile counts
		return (FALSE);

	return (TRUE);

}
//------------------------------------------------------------------------------------------------------------------------------------------------