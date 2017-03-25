/*  Author:     Luke Hedt
    StuID:      832153
    Date:       24/03/2017
    Name:       queue.c
    Purpose:    Contains code for Queue Operations

    Comments:
*/

#include "list.h"


list_t* new_queue()
/* 
    Creates a new queue object, then returns a pointer to it.
*/
{
    return new_list();
}


void enqueue(list_t* cqueue, int cdata)
/*
    Adds data to the back of the Queue.
*/
{
    insert_at_foot(cqueue, cdata);
    return;
}


int dequeue(list_t* cdata, int cdata)
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
