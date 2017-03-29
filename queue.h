/*	Author:		Luke Hedt
 *	StuID:		832153
 *	Date:		25/03/2017
 *	Name:		queue.h
 *	Purpose:	Header File for Queue Ops.
 */

#ifndef QUEUE_H
#define QUEUE_H


list_t* new_queue();
/* 
    Creates a new queue object, then returns a pointer to it.
*/

int enqueue(list_t* cqueue, int cdata);
/*
    Adds data to the back of the Queue.
*/

int dequeue(list_t* cqueue);
/*
    Removes data from the front of the Queue.
*/

int queue_size(list_t* cqueue);
/*
    Returns the number of nodes in the Queue.
*/

void queue_purge(list_t* cqueue);
/* 
    Deletes all data in the queue and frees the queue object.
*/

#endif
