#include "extra.h"

//================================================================================================================================================
															 /*STATIC FUNCTIONS*/

static char* GetOneStirng();

//================================================================================================================================================

//INPUT:board 8x8
//OUTPUT:restart the board to standart checkers game 8x8
//------------------------------------------------------------------------------------------------------------------------------------------------
void Reset_board(Board board)
{
	int col, row;

	for (row = 0; row < BOARD_SIZE; row++)
	{
		for (col = 0; col < BOARD_SIZE; col++)
		{
			if (row < 3) //place of T
			{
				if (row == 1)
				{
					if (col % 2 == 0)
						board[row][col] = 'T';
					else
					{
						board[row][col] = '0';
					}
				}
				else //case row 0 or 2
				{
					if (col % 2)
						board[row][col] = 'T';
					else
					{
						board[row][col] = '0';
					}
				}
			}
			else
			{
				if (row > 4) //place of B
				{
					if (row == 6)
					{
						if (col % 2)
							board[row][col] = 'B';
						else
						{
							board[row][col] = '0';
						}
					}
					else //case row 0 or 2
					{
						if (col % 2 == 0)
							board[row][col] = 'B';
						else
						{
							board[row][col] = '0';
						}
					}
				}
				else
				{
					board[row][col] = '0';
				}
			}
		}
	}
}
//------------------------------------------------------------------------------------------------------------------------------------------------

//CHOOSE MANU
//ask the player how he would like to start with
//------------------------------------------------------------------------------------------------------------------------------------------------
Player Choose_WELCOME()
{
	BOOL  flag;
	Player player;
	int choice;

	flag = TRUE;


	while (flag)
	{
		printf("Welcome To Checkers By Alon Ben Harush! \n");
		printf("Please Select Your Choice: (Write the number) \n");
		printf("1 - Start with T | 2 - Start with B | 3-Random \n");
		scanf("%d", &choice);
		printf("\n");
		if (choice == 1)
		{
			player = 'T';
			flag = FALSE;
		}
		else
		{
			if (choice == 2)
			{
				player = 'B';
				flag = FALSE;
			}
			else
			{
				if (choice == 3)
				{
					if (rand() % 2)
						player = 'T';
					else
						player = 'B';

					flag = FALSE;

				}
				else
				{
					printf("TRY AGIAN! \n");
				}
			}
		}
	}
	return player;
}
//------------------------------------------------------------------------------------------------------------------------------------------------

//Play agian manu
//------------------------------------------------------------------------------------------------------------------------------------------------
BOOL play_again()
{
	BOOL play, flag;
	int ans;

	flag = TRUE;

	while (flag)
	{
		printf("Play Again?: 1 - YES | 0 -NO \n");
		scanf("%d", &ans);
		if (ans == 1)
		{
			play = TRUE;
			flag = FALSE;
		}
		else
		{
			if (ans == 0)
			{
				play = FALSE;
				flag = FALSE;
			}
			else
			{
				printf("SORRY TRY AGAIN \n");
			}
		}
	}
	return play;
}
//------------------------------------------------------------------------------------------------------------------------------------------------

//Save and Load Manu
//------------------------------------------------------------------------------------------------------------------------------------------------
void SavesAndLoads(Board board)
{
	int ans;
	BOOL flag, flag2;
	char *path;
	FILE *f1;

	flag = TRUE;
	flag2 = TRUE;


	while (flag)
	{
		printf("Do You Want To Save End Board To File Or Load Any Board From File?: \n");
		printf("( 2 - SAVE | 1 - LOAD | 0 - NO ) \n");
		scanf("%d", &ans);
		if (ans == 1 || ans == 0 || ans == 2)
			flag = FALSE;
		else
		{
			printf("ERROR - WORNG INPUT,TRY AGIAN \n");
		}

	}

	flag = TRUE;

	if (ans == 2)
	{
		printf("SAVE\n");
		printf("Please Enter Path For Saving (file will be overwrite if exist): \n");


		path = GetOneStirng();

		f1 = fopen(path, "rb");
		if (f1)
		{
			printf("FILE IS OVERWRITTEN: \n");
			fclose(f1);

		}
		else
		{
			printf("FILE DID NOT FOUND , Creating new one : \n");
			f1 = fopen(path, "wb");
			fclose(f1);
		}

		StoreBoard(board, path);
		printf("Board Saved \n");
		free(path);



	}
	if (ans == 1)
	{
		printf("LOAD\n");
		printf("Please Enter Path To Load From: \n");


		path = GetOneStirng();


		f1 = fopen(path, "rb");
		if (f1)
		{
			fclose(f1);
			LoadBoard(path, board);
			printf("Board From %s :\n", path);
			Print_Board(board);
			free(path);

		}
		else
		{
			printf("ERROR - FILE DID NOT FOUND  \n");

		}

	}

}
//------------------------------------------------------------------------------------------------------------------------------------------------

//Crate Any size string
//------------------------------------------------------------------------------------------------------------------------------------------------
static char* GetOneStirng()
{


	char* str;
	unsigned int logsize, phySize;
	logsize = 0;
	phySize = 1;
	char c;

	str = (char*)malloc(sizeof(char)*phySize);

	c = getchar();
	c = getchar();


	while (c != '\n')
	{
		if (logsize == phySize)
		{
			phySize *= 2;
			str = (char*)realloc(str, sizeof(char)*phySize);
			checkalloction(str);
		}

		str[logsize++] = c;

		c = getchar();
	}

	str = (char*)realloc(str, sizeof(char)*(logsize + 1));
	checkalloction(str);
	str[logsize] = '\0';

	return str;

}
//------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------