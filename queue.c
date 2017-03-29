/*  Author:     Luke Hedt
 *  StuID:      832153
 *  Date:       24/03/2017
 *  Name:       queue.c
 *  Purpose:    Contains code for Queue Operations
 */

/* Defines. Means that I can return these and use if(!SUCCESS) 
to verify Output. Ugly, but it works. */
#define FAIL 0
#define SUCCESS 1

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "queue.h"


list_t* new_queue()
/* 
    Creates a new queue object, then returns a pointer to it.
*/
{
    return new_list();
}


int enqueue(list_t* cqueue, int cdata)
/*
    Adds data to the back of the Queue.
*/
{
    int queued = insert_at_foot(cqueue, cdata);

    /* Sanity Check */
    if(!queued) {
        fprintf(stderr, "Unable to queue data!");
        exit(FAIL);
    }

    return SUCCESS;
}


int dequeue(list_t* cqueue)
/*
    Removes data from the front of the Queue.
*/
{
    return delete_head(cqueue);
}

int queue_size(list_t* cqueue)
/*
    Returns the number of nodes in the Queue.
*/
{
    return list_size(cqueue);
}

void queue_purge(list_t* cqueue)
/* 
    Deletes all data in the queue and frees the queue object.
*/
{
    free_list(cqueue);
    return;
}
