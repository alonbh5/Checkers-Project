#include "list.h"

//INPUT:gets a list pointer
//OUTPUT:make it empty (NULL)
//------------------------------------------------------------------------------------------------------------------------------------------------
void makeEmptyList(SingleSourceMovesList *lst)
{
	// maked empty list (point to null)
	lst->head = NULL;
	lst->tail = NULL;
}
//------------------------------------------------------------------------------------------------------------------------------------------------

//INPUT:get a single source move list
//OUTPUT: free all alocations
//------------------------------------------------------------------------------------------------------------------------------------------------
void freeList(SingleSourceMovesList *lst)
{
	SingleSourceMovesListCell *cur, *temp;

	
	cur = lst->head;

	while (cur)
	{

		free(cur->position);
		temp = cur->next;
		free(cur);
		cur = temp;
	}

	free(lst);



}
//------------------------------------------------------------------------------------------------------------------------------------------------

//INPUT:gets a list and a cell
//OUTPUT:insert the cell to end of list
//------------------------------------------------------------------------------------------------------------------------------------------------
void insertDataToEndList(SingleSourceMovesList *lst, SingleSourceMovesListCell *cell)
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

//INPUT:gets data of cell
//OUTPUT:create a cell with data and return new allocate cell
//------------------------------------------------------------------------------------------------------------------------------------------------
SingleSourceMovesListCell *Allocate_Cell(unsigned short captures, checkersPos position)
{
	//create a new node with input char
	SingleSourceMovesListCell *newcell;
	checkersPos *newpos;

	newcell = (SingleSourceMovesListCell*)malloc(sizeof(SingleSourceMovesListCell)); // make space for new node
	newpos = (checkersPos*)malloc(sizeof(checkersPos));

	checkalloction(newcell);
	checkalloction(newpos);

	newpos->col = position.col;
	newpos->row = position.row;

	newcell->next = NULL;
	newcell->captures = captures;
	newcell->position = newpos;

	return (newcell);

}
//------------------------------------------------------------------------------------------------------------------------------------------------

//INPUT:gets a before cell and a cell
//OUTPUT:insert tafter "before" cell
//------------------------------------------------------------------------------------------------------------------------------------------------
void insertDataToMiddleList(SingleSourceMovesListCell *before, SingleSourceMovesListCell *Ist_cell)
{
	// get data and node, create a node and enter it after the node to end of list



	Ist_cell->next = before->next;
	before->next = Ist_cell;


}
//------------------------------------------------------------------------------------------------------------------------------------------------

//INPUT:get a list and a cell
//OUTPUT:insert the cell to head of list
//------------------------------------------------------------------------------------------------------------------------------------------------
void insertDataToHeadList(SingleSourceMovesList *lst, SingleSourceMovesListCell *cell)
{


	if (lst->head == NULL) //case list is empty
	{
		lst->head = cell;
		lst->tail = cell;
	}
	else
	{
		cell->next = lst->head;
		lst->head = cell;
	}


}
//------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------


