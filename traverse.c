/*  Author:     Luke Hedt
 *  StuID:      832153
 *  Date:       26/03/2017
 *  Name:       traverse.c
 *  Purpose:    Contains code for the First Design of Algorithms Assignment.
 *
 *  Comments:   
 */

#include <stdio.h>
#include <stdlib.h>
#include "traverse.h"
#include "graph.h"
#include "list.h"
#include "stack.h"
#include "queue.h"


void print_dfs(Graph* graph, int source_id) 
/* Conducts a Depth First Search and prints each element as it's visited.
 * This is a non-recursive implementation. */
{
    /* VARIABLE DECLARATIONS */
    int vert = source_id;
    int i;
    int* visit;
    int order = graph->maxn;
    list_t* dep_stack;

    dep_stack = new_stack();
    /* Error detection, just in case.  */
    if(!(push(dep_stack, vert))) {
        fprintf(stderr, "ERROR: Could not push data on the stack!");
        exit(EXIT_FAILURE);
    }

    /* Create Array to store Visited values in. */
    visit = (int*)malloc((order)*sizeof(int));
    for(i=0; i<order; i++) {
        visit[i] = 0;
    }

    while(stack_size(dep_stack)) {
       vert = pop(dep_stack); 
       if(!(visit[vert])) {
           visit[vert] = 1;
        /*   for all edges from v to w in G.adjacentEdges(vert)
        *       push(dep_stack, w)
        */
       }
    }
}

void print_bfs(Graph* graph, int source_id) {
	printf("not yet implemented: put code for part 2 here\n");
}

void detailed_path(Graph* graph, int source_id, int destination_id) {
	printf("not yet implemented: put code for part 3 here\n");
}

void all_paths(Graph* graph, int source_id, int destination_id) {
	printf("not yet implemented: put code for part 4 here\n");
}

void shortest_path(Graph* graph, int source_id, int destination_id) {
	printf("not yet implemented: put code for part 5 here\n");
}
