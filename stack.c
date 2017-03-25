/*  Author:     Luke Hedt
    StuID:      832153
    Date:       24/03/2017
    Name:       stack.c
    Purpose:    Contains code for Stack Operations

    Comments:
*/

#include "list.h"

list_t* new_stack()
/*
	Creates a new stack object and returns a pointer to it. 
*/
{
    return new_list();
}


int push(list_t* cstack, int cdata)
/*
	Pushes data onto the stack.
*/
{
	int feed;

	feed = insert_at_head(cstack, cdata);

	if(!feed) {
		fprintf(stderr, "ERROR: unable to insert data!");
		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}

int pop(list_t* cstack)
/*
	Deletes the First Element in the stack and returns it's value.
*/
{
	return delete_head(cstack);
}

int stack_size(list_t* clist)
/* 
    Returns the size of the stack.
*/
{
    return list_size(clist);
}

void purge_stack(list_t* cstack)
/*
	Deletes all elements in the stack and frees the stack.
*/
{
	free_list(cstack);
}
