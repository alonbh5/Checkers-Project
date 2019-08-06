#include "extra.h"

//main for project- JUL 2019 MTA YEAR 1- Alon Ben Harush 312533698

void main()
{
	BOOL play;
	Board board;
	Player player;
	

	

	play = TRUE;
	

	while (play)
	{
		player = Choose_WELCOME();
		Reset_board(board);

		
		PlayGame(board, player);
		
		SavesAndLoads(board);

		
		play = play_again();
		

	}
	printf("Goodbye! \n");

}

