/*	Author:		Luke Hedt
	StuID:		832153
	modname:	list.c
	Purpose:	Contains code for linked list operations.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node* next;
	struct node* last;
} node_t;

typedef struct list {
	node_t* head;
	node_t* foot;
	int size;
} list_t;

list_t* new_list()
{
/*
Creates a new empty list object and returns a pointer to it.
*/

	/* Create space for the new list. */
	list_t* nlist;
	nlist = (list_t*)malloc(sizeof(list_t));

	/* Check that the list space exists. Return an error if not. */
	if(!nlist) {
		fprintf(stderr, "ERROR: Unable to make space for New List!");
		exit(EXIT_FAILURE);
	}

	/* Set all list elements to defaults. */
	nlist->head = NULL;
	nlist->foot = NULL;
	nlist->size = 0;

	return nlist;
}


static node_t* new_node()
/* Creates a new node. Returns an error if the space
doesn't exist.*/
{
	node_t* nnode;
	nnode = (node_t*)malloc(sizeof(node_t));

	if(!nnode) {
		fprintf(stderr, "ERROR: Unable to make space for New Node!");
		exit(EXIT_FAILURE);
	}

	return nnode;
}


int insert_at_head(list_t* clist, int cdata)
/* 
Inserts data at the head of the list and remaps the list head so the list is
formatted correctly.
 */
{
	node_t* nnode;
	nnode = new_node();

	/* Reformats the head of the list and inserts the new data at the 
	head. */
	nnode->next = clist->head;
	nnode->last = NULL;
	clist->head->last = nnode;

	nnode->data = cdata;
	clist->head = nnode;
	clist->size = (clist->size + 1);

	return EXIT_SUCCESS;
}


int insert_at_foot(list_t* clist, int cdata)
/* 
Inserts data at the foot of the list and remaps the list foot so the list is
formatted correctly.
 */
{
	node_t* nnode;
	nnode = new_node();

	/* Reformats the foot of the list and inserts the new data at the 
	head. */
	nnode->next = NULL;
	nnode->last = clist->foot;
	clist->foot->next = nnode;

	nnode->data = cdata;
	clist->foot = nnode;
	clist->size = (clist->size + 1);

	return EXIT_SUCCESS;
}

int delete_head(list_t* clist)
/*
Deletes the node at the head of the list and returns its contents.
*/
{
    node_t* hnode;
    int cdata;

    hnode = clist->head;
    clist->head = clist->head->next;
    clist->head->last = NULL;
    cdata = hnode->data;

    free(hnode);
    return cdata;
}
