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

        /* Ensure that the algorithm runs once the edges run out. */
        while(new_edge) {
        	/* Only visit new vertices. */
            if(!(visit[new_vert_id])) {
                visit[new_vert_id] = 1;
                /* Print and push the vertex onto the stack. */
                printf("%s\n", graph->vertices[new_vert_id]->label);
                push(dep_stack, new_edge->v);
                /* Hop to the next vertex. */
                new_edge = graph->vertices[new_vert_id]->first_edge;
                new_vert_id = new_edge->v;
            } else {
            	/* Hop to the next vertex if it's been visited. */
                new_edge = new_edge->next_edge;
                /* Make sure you can actually get the vertext id. */
                if(new_edge) {
                	new_vert_id = new_edge->v;
                }
            }
        }
    }
    /* Free all the borrowed memory you filthy kleptomaniac. */
    free(visit);
    purge_stack(dep_stack);
}

void print_bfs(Graph* graph, int source_id)
/* Implements a Bredth First Search on the graph starting from the Source_id,
 * and prints each vertex as they're visited. */
{
    int i;
    int source_vert_id = source_id;
    int child_vert_id;
    int* visit = (int*)malloc((graph->maxn)*sizeof(int));
    Edge *cur_edge, *n_edge;

    /* Queue Definition, With error check for sanity. */
    list_t* BreQ = new_queue();
    if(!BreQ) {
        fprintf(stderr, "ERROR: Queue could not be formed!");
        exit(FAIL);
    }

    for(i=0; i<(graph->maxn); i++) {
        visit[i] = 0;
    }

    /* Enqueue the Source node to begin the algorithm */
    enqueue(BreQ, source_vert_id);
    visit[source_vert_id] = 1;

    while(queue_size(BreQ)) {
/*      Dequeue current vertex;
 *      for all edges connected to current vertex
 *          if unvisited
 *              mark as visited and enqueue; */
        source_vert_id = dequeue(BreQ);
        printf("%s\n", graph->vertices[source_vert_id]->label);
        child_vert_id = graph->vertices[source_vert_id]->first_edge->v;
        cur_edge = graph->vertices[source_vert_id]->first_edge;
        n_edge = cur_edge->next_edge;
        i = 1;
        while(1) {
            if(!(visit[child_vert_id])) {
                enqueue(BreQ, child_vert_id);
                visit[child_vert_id] = 1;
            }

            if(!i) {
                break;
            }
            cur_edge = n_edge;
            child_vert_id = cur_edge->v;
            n_edge = n_edge->next_edge;
            if(!n_edge) {
                i = 0;
            }
        }
    }
    free(visit);
    queue_purge(BreQ);
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
