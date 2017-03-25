/*  Author:     Luke Hedt
    StuID:      832153
    Date:       24/03/2017
    Name:       stack.h
    Purpose:    Header File for Stack Operations

    Comments:
*/

#ifndef STACK_H
#define STACK_H

#include "stack.c"

list_t* new_stack();
/*
	Creates a new stack object and returns a pointer to it. 
*/

int push(list_t* cstack, int cdata);
/*
	Pushes data onto the stack.
*/

int pop(list_t* cstack);
/*
	Deletes the First Element in the stack and returns it's value.
*/

int stack_size(list_t* clist);
/* 
    Returns the size of the stack.
*/

void purge_stack(list_t* cstack);
/*
	Deletes all elements in the stack and frees the stack.
*/

#endif