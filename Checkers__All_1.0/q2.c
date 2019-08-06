#include "q2.h"

//================================================================================================================================================
                                                             /*STATIC FUNCTIONS*/

static void Place_all_routs_Array(SingleSourceMovesTreeNode *root, int *index, SingleSourceMovesList **arr);
static void printarray_test(SingleSourceMovesList **arr);
static void restart_list_arr(SingleSourceMovesList **arr);
static SingleSourceMovesList *FindMaxfromArr(SingleSourceMovesList **arr);
//================================================================================================================================================

//------------------------------------------------------------------------------------------------------------------------------------------------
//Question 2
//INPUT: move tree
//OUTPUT: a list of best moves (empty list if tree is false,list with one cell if there no move)
SingleSourceMovesList *FindSingleSourceOptimalMove(SingleSourceMovesTree *moves_tree)
{
	SingleSourceMovesList *res;
	SingleSourceMovesListCell *cell;
	int i = 0;
	BOOL skip = TRUE;

	SingleSourceMovesList **arr;

	res = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));
	checkalloction(res);

	


	makeEmptyList(res);


	if (moves_tree)
	{
		if (moves_tree->source)
		{
			if (!(moves_tree->source->next_move[LEFT]) && !(moves_tree->source->next_move[RIGHT])) ///case the pon has no moves
			{
				cell = Allocate_Cell(moves_tree->source->total_captures_so_far, *(moves_tree->source->pos));
				insertDataToEndList(res, cell);
			}

			else ///case the pon has at least one move
			{
				arr = (SingleSourceMovesList**)malloc(5 * sizeof(SingleSourceMovesList*)); //max of 5 ways 
				checkalloction(arr);
				restart_list_arr(arr);
				Place_all_routs_Array(moves_tree->source, &i, arr);
				//
				//printarray_test(arr);
				//
				res = FindMaxfromArr(arr); //<-free all arr[i]
				free(arr);
			}
		}
	}

	return res;
}
//------------------------------------------------------------------------------------------------------------------------------------------------

//INPUT:gets an single list pointers array size 5
//OUTPUT:allocate for every cell space, and restart every cell to empty list
//------------------------------------------------------------------------------------------------------------------------------------------------
static void restart_list_arr(SingleSourceMovesList **arr)
{
	arr[0]= (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));
	arr[1] = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));
	arr[2] = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));
	arr[3] = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));
	arr[4] = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));

	checkalloction(arr[0]);
	checkalloction(arr[1]);
	checkalloction(arr[2]);
	checkalloction(arr[3]);
	checkalloction(arr[4]);

	makeEmptyList(arr[0]);
	makeEmptyList(arr[1]);
	makeEmptyList(arr[2]);
	makeEmptyList(arr[3]);
	makeEmptyList(arr[4]);
}
//------------------------------------------------------------------------------------------------------------------------------------------------

//INPUT:gets an array filed with all posible roots for a player
//OUTPUT:select one route (best one by eat) and return it
//free other cell from array
//------------------------------------------------------------------------------------------------------------------------------------------------
static SingleSourceMovesList *FindMaxfromArr(SingleSourceMovesList **arr)
{
	unsigned short i;
	SingleSourceMovesList *res;

	res = arr[0];
	for (i = 1; i < 5 && arr[i]->head; i++)
	{
		if (res->tail->captures <= arr[i]->tail->captures)
		{
			if (res->tail->captures == arr[i]->tail->captures)
			{
				if (rand() % 2) ///same eats
				{
					freeList(res);
					res = arr[i];
				}
			}
			else
			{
				freeList(res);
				res = arr[i];
			}
		}
		else
		{
			freeList(arr[i]);
		}
	}

	return res;
}
//------------------------------------------------------------------------------------------------------------------------------------------------

//INPUT:gets an single list pointers array size 5 and move tree, and int pointer (0)
//OUTPUT:crate all posibol routs from the tree (max is 5 in a 8x8 board...)
//every rout that is found is placed 
//------------------------------------------------------------------------------------------------------------------------------------------------
static void Place_all_routs_Array(SingleSourceMovesTreeNode *root, int *index, SingleSourceMovesList **arr)
{
	SingleSourceMovesListCell *cell;
	int leaf,j,i;

	
	

	if (root->next_move[LEFT] || root->next_move[RIGHT])
	{
		leaf = Tree_Leaf_Count(root);
		

		for (j = (*index), i = 0; i < leaf; j++, i++)
		{
			cell = Allocate_Cell(root->total_captures_so_far, *(root->pos));
			insertDataToEndList((arr[j]), cell);
		}
	}

	if (!root->next_move[LEFT] && !root->next_move[RIGHT])
	{
		cell = Allocate_Cell(root->total_captures_so_far, *(root->pos));
		insertDataToEndList(arr[(*index)], cell);
		(*index)++;
	}
	else
	{
		if (root->next_move[LEFT])
		{
			Place_all_routs_Array(root->next_move[LEFT], index, arr);

		}
		if (root->next_move[RIGHT])
		{
			Place_all_routs_Array(root->next_move[RIGHT], index, arr);
		}
	}
	
	
		
}
//------------------------------------------------------------------------------------------------------------------------------------------------

//FOR debuge
//INPUT:gets an array of routs
//OUTPUT:print every rout
//------------------------------------------------------------------------------------------------------------------------------------------------
static void printarray_test(SingleSourceMovesList **arr)
{
	int i;
	SingleSourceMovesListCell *cur;

	for (i = 0; i < 5 && arr[i]->head; i++)
	{
		printf("rout number %d", i);
		cur = arr[i]->head;
			while (cur)
			{
				printf("--> (%c - %c)", cur->position->row, cur->position->col);
				cur = cur->next;
				
			}
			printf("\n");
	}
}
//------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------