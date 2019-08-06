#include "q7.h"

//================================================================================================================================================
															 /*STATIC FUNCTIONS*/
static BOOL Check_Win(Board board, Player cur_player);
static BOOL IsEndCaseNoMoves(Board board, int row, int col);
//================================================================================================================================================

//Question 7
//INPUT:gets a board and stating player
//OUTPUT:play game of checkers until the end
//------------------------------------------------------------------------------------------------------------------------------------------------
void PlayGame(Board board, Player starting_player)
{

	BOOL turn_T, win;
    Player player_1, player_2;

	

	player_1 = 'T';
	player_2 = 'B';

	Print_Board(board);

	if (starting_player == 'T')
	{
		turn_T = TRUE;
	}
	else
	{
		if (starting_player == 'B')
		{
			turn_T = FALSE;
		}
		else
		{
			printf("error Q7-unvlid player name");
			exit(-7);
		}
	}

	win = Check_Win(board, starting_player);

	while (!win)
	{

		if (turn_T) //turn of T
		{
			printf("player TOP_DOWN's turn\n");
			Turn(board, player_1);
			//
			//Print_Board(board); //remove "//" if you want to see board in real time
			//
			if (Check_Win(board, player_1))
				win = TRUE;
		}
		else
		{
			printf("player BOTTOM_UP's turn\n");
			Turn(board, player_2);
			//
			//Print_Board(board); //remove "//" if you want to see board in real time
			//
			if (Check_Win(board, player_2))
				win = TRUE;
		}
		
		
		turn_T = !turn_T;

	}

	if (turn_T) //turn of T
		printf("player TOP_DOWN's turn\n");
	else
		printf("player BOTTOM_UP's turn\n");

}
//------------------------------------------------------------------------------------------------------------------------------------------------

//INPUT:gets checkers board
//OUTPUT:print it to screen
//------------------------------------------------------------------------------------------------------------------------------------------------
void Print_Board(Board board)
{
	int row, col, i;
	char ch = 'A';
	ch--;
	printf("+-+-+-+-+-+-+-+-+-+\n");
	printf("+ |1|2|3|4|5|6|7|8|\n");

	for (row = 0, i = 0; i < 17; i++)
	{

		if (i % 2 == 0)
		{
			printf("+-+-+-+-+-+-+-+-+-+\n");
		}
		else
		{
			ch = ch + 1;
			printf("|%c", ch);
			for (col = 0; col < 8; col++)
			{
				if (board[row][col] == '0')
					printf("| ");
				else
					printf("|%c", board[row][col]);

			}
			printf("|\n");
			row++;
		}
	}
}
//------------------------------------------------------------------------------------------------------------------------------------------------

//INPUT:gets checkers board and player that playing now
//OUTPUT:check if its a win by:
//1. T is at the bottom row
//2. B is in the upper row
//3. T or B has no players left
//4.current player had no moves left
//------------------------------------------------------------------------------------------------------------------------------------------------
static BOOL Check_Win(Board board,Player cur_player)
{
	BOOL res;
	int row,col, B_pons, T_pons,T_endcase,B_endcase;
	B_pons = 0; ///how many B
	T_pons = 0; ///how many T 
	T_endcase = 0; ///how many T cant move
	B_endcase = 0; ///how many B cant move
	res = FALSE;

	for (row = 0; row < BOARD_SIZE && !res; row++)
	{
		if (board[0][row] == 'B' || board[BOARD_SIZE-1][row] == 'T') ///case one of them win
			res = TRUE;

		for (col = 0; col < BOARD_SIZE && !res; col++)
		{
			if (board[row][col] == 'B')
			{
				B_pons++;
				if (IsEndCaseNoMoves(board, row, col)) ///no moves
					B_endcase++;
			}
			if (board[row][col] == 'T')
			{
				T_pons++;
				if (IsEndCaseNoMoves(board, row, col)) ///no moves
					T_endcase++;
			}
		}
	}

	if (!res)
	{
		if (T_pons == 0 || B_pons == 0) ///all got eat
			res = TRUE;
		else
			if (B_endcase == B_pons) //case no moves for B and its turn
			{
				if (cur_player == 'B')
					res = TRUE;
			}
			else
				if (T_endcase == T_pons) //case no moves for B and its turn
				{
					if (cur_player == 'T')
						res = TRUE;
				}
	}
			

	return res;
}
//------------------------------------------------------------------------------------------------------------------------------------------------

//INPUT: board, row and col for check
//OUTPUT: check if from that postion there are no moves ( true) else false
//------------------------------------------------------------------------------------------------------------------------------------------------
static BOOL IsEndCaseNoMoves(Board board, int row, int col)
{
	BOOL res;
	SingleSourceMovesList *check;
	checkersPos pos;

	pos = Int_To_Pos(row, col);

	check = FindSingleSourceMoves(board, &pos);

	if (check)
	{
		freeTree(check);
		res = FALSE;
	}
	else
		res = TRUE;

	return res;
	

	
}
//------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------

