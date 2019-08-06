#include "q6.h"
//------------------------------------------------------------------------------------------------------------------------------------------------

//Question 6
//INPUT:gets a board and file name
//OUTPUT:load from file (bin) to board
//------------------------------------------------------------------------------------------------------------------------------------------------
void LoadBoard(char *filename, Board board)
{
	FILE *f1;
	int row, col, i;
	short x;

	f1 = fopen(filename, "rb"); 

	if (f1)
	{

		for (row = 0; row < 8; row++)
		{
			fread(&x, sizeof(short), 1, f1);
			for (col = 0, i = 15; col < BOARD_SIZE; col++, i -= 2)
			{
				if (IS_BIT_I_SET(i, x)) //case 10
				{
					board[row][col] = 'B';
				}
				else //case 0X (x=0\1)
					if (IS_BIT_I_SET((i - 1), x))
						board[row][col] = 'T';
					else
						board[row][col] = '0';
			}

		}
		fclose(f1);
	}
	else
	{
		printf("Worng Path");
	}
		
}
//------------------------------------------------------------------------------------------------------------------------------------------------