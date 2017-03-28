/*  Author:     Luke Hedt
 *  StuID:      832153
 *  Date:       26/03/2017
 *  Name:       traverse.c
 *  Purpose:    Contains code for the First Design of Algorithms Assignment.
 *
 *  Comments:   
 */

/* Defines. Means that I can return these and use if(!SUCCESS) 
to verify Output. Ugly, but it works. */
#define FAIL 0
#define SUCCESS 1

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
    int cur_vert_id = source_id, order = graph->maxn;
    int new_vert_id, i;
    Edge *new_edge;
    int* visit;
    /* Stack Def */
    list_t* dep_stack;
    dep_stack = new_stack();

    /* Error detection, just in case.  */
    if(!dep_stack) {
    	fprintf(stderr, "ERROR: New Stack could not be created!");
    	exit(FAIL);
    }

    /* Create Array to store Visited values in. */
    visit = (int*)malloc((order)*sizeof(int));
    for(i=0; i<order; i++) {
        visit[i] = 0;
    }

    /* Complete operations on the Source Vertex.*/
    push(dep_stack, cur_vert_id);
    printf("%s\n", graph->vertices[source_id]->label);
    visit[source_id] = 1;

    /* The loop operates for as long as the stack is non-empty.  */
    while(stack_size(dep_stack)) {
    	/* Remove the current vertex from the stack, 
    	 * Set vars to it's first edge. */
        cur_vert_id = pop(dep_stack);
        new_edge = graph->vertices[cur_vert_id]->first_edge;
        new_vert_id = new_edge->v;
        
        while(new_edge) {
            if(!(visit[new_vert_id])) {
                visit[new_vert_id] = 1;
                printf("%s\n", graph->vertices[new_vert_id]->label);
                push(dep_stack, new_edge->v);
                new_edge = graph->vertices[new_vert_id]->first_edge;
                new_vert_id = new_edge->v;
            } else {
                new_edge = new_edge->next_edge;
                new_vert_id = new_edge->v;
            }
        }
    }

    free(visit);
    purge_stack(dep_stack);
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
