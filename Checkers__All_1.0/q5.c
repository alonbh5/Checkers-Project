#include "q5.h"
//------------------------------------------------------------------------------------------------------------------------------------------------

//Question 5
//INPUT:gets a board and file name
//OUTPUT:store the board in binary 
//------------------------------------------------------------------------------------------------------------------------------------------------
void StoreBoard(Board board, char *filename)
{
	FILE *f1;
	int row, col, i;
	short x;

	f1 = fopen(filename, "wb"); 

	if (f1)
	{
		x = 0; //000000000 000000000

		for (row = 0; row < BOARD_SIZE; row++)
		{
			for (col = 0, i = 15; col < BOARD_SIZE; col++, i -= 2)
			{

				if (board[row][col] == 'T')
					SET_BIT(x, i - 1, short); //01
				if (board[row][col] == 'B')
					SET_BIT(x, i, short); //10



			}
			fwrite(&x, sizeof(short), 1, f1);
			x = 0; //000000000 000000000
		}
		fclose(f1);
	}
	else
	{
		printf("Worng Path");
	}


	
}
//------------------------------------------------------------------------------------------------------------------------------------------------