#include "tree.h"
//------------------------------------------------------------------------------------------------------------------------------------------------


//INPUT:gets data of tree node (captures positon and board)
//OUTPUT:allcote node and insert the data to new node 
//------------------------------------------------------------------------------------------------------------------------------------------------
SingleSourceMovesTreeNode *AllocateSingleSourceMovesTreeNode(unsigned short newcap, checkersPos position, Board newborad)
{
	SingleSourceMovesTreeNode *node;
	checkersPos *pos;
	int j, i;
	node = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
	pos = (checkersPos*)malloc(sizeof(checkersPos));
	checkalloction(node);
	checkalloction(pos);

	pos->col = position.col;
	pos->row = position.row;

	for (i = 0; i < BOARD_SIZE; i++)
		for (j = 0; j < BOARD_SIZE; j++)
			node->board[i][j] = newborad[i][j];

	node->pos = pos;
	
	node->total_captures_so_far = newcap;
	node->next_move[LEFT] = NULL;
	node->next_move[RIGHT] = NULL;

	return node;
}
//------------------------------------------------------------------------------------------------------------------------------------------------

//INPUT: gets a tree
//OUTPUT:free all alloction
//------------------------------------------------------------------------------------------------------------------------------------------------
void freeTree(SingleSourceMovesTree *tree)
{

	if (tree)
	{
		if (tree->source)
		{
			ClearTreeAux(tree->source);
			free(tree);
		}
	}
}
//------------------------------------------------------------------------------------------------------------------------------------------------

//Defult is used by FreeTree!
//INPUT:gets a node (defulte tree source)
//OUTPUT:free all alloction
//------------------------------------------------------------------------------------------------------------------------------------------------
void ClearTreeAux(SingleSourceMovesTreeNode *root)
{
	//used for clear tree
	if (root->next_move[LEFT])
		ClearTreeAux(root->next_move[LEFT]);
	if (root->next_move[RIGHT])
		ClearTreeAux(root->next_move[RIGHT]);

	free(root->pos);
	free(root);

}
//------------------------------------------------------------------------------------------------------------------------------------------------

//INPUT:gets tree node
//OUTPUT:return how many node are from that root
//------------------------------------------------------------------------------------------------------------------------------------------------
int Tree_Node_Count(SingleSourceMovesTreeNode *root)
{
	int res=0;
	
	if (root->next_move[LEFT])
		res += Tree_Node_Count(root->next_move[LEFT]);
	if (root->next_move[RIGHT])
		res += Tree_Node_Count(root->next_move[RIGHT]);

	if (root)
		return (res+1);
	else
		return 0;

}
//------------------------------------------------------------------------------------------------------------------------------------------------

//INPUT:gets tree node
//OUTPUT:return how many leaf are from that root
//------------------------------------------------------------------------------------------------------------------------------------------------
int Tree_Leaf_Count(SingleSourceMovesTreeNode *root)
{
	int res = 0;
	if (root->next_move[LEFT])
		res += Tree_Leaf_Count(root->next_move[LEFT]);
	if (root->next_move[RIGHT])
		res += Tree_Leaf_Count(root->next_move[RIGHT]);

	if (!root->next_move[LEFT] && !root->next_move[RIGHT]) //if leaf
		return (res + 1);
	else
		return res;
}
//------------------------------------------------------------------------------------------------------------------------------------------------

//INPUT:gets a tree and int space
//OUTPUT: print the tree with num of space 
//for debuge
//------------------------------------------------------------------------------------------------------------------------------------------------
void printtree(SingleSourceMovesTreeNode *root, int space)
{

	char row, col;
	 
	if (root == NULL)
		return;
	row = root->pos->row;
	col = root->pos->col;

	space += 10;

	printtree(root->next_move[RIGHT], space);

	printf("\n");
	for (int i = 10; i < space; i++)
		printf(" ");
	printf("(%c - %c)", row,col);

	printtree(root->next_move[LEFT], space);
}
//------------------------------------------------------------------------------------------------------------------------------------------------

//INPUT:gets any pointers
//OUTPUT: checks that it realy point to somthing
//used for memory alloction
//------------------------------------------------------------------------------------------------------------------------------------------------
void checkalloction(void *ptr)
{
	if (!ptr)
	{
		printf("Memory alloction error!!!! ): \n");
		exit(-1);
	}
}
//------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------