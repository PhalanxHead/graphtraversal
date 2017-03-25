/*	Author:		Luke Hedt
	StuID:		832153
	Date:		24/03/2017
	modname:	list.h
	Purpose:	Header File for Linked List Ops.
*/

#ifndef LIST_H
#define LIST_H

#include "list.c"

typedef struct list list_t;


list_t* new_list();
/*
Creates a new empty list object and returns a pointer to it.
*/

int insert_at_head(list_t* clist, int cdata);
/*
Inserts data at the head of the list and remaps the list head so the list is
formatted correctly.
 */

int insert_at_foot(list_t* clist, int cdata);
/*
Inserts data at the foot of the list and remaps the list foot so the list is
formatted correctly.
 */

int delete_head(list_t* clist);
/*
Deletes the node at the head of the list and returns its contents.
*/

int delete_foot(list_t* clist);
/*
Deletes the node at the foot of the list and returns its contents.
*/

void free_list(list_t* clist);
/*
Deletes every element in the list then frees the list.
*/

int list_size(list_t* clist);
/*
Returns the number of nodes in the list.
*/

#endif