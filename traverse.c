/*  Author:     Luke Hedt
 *  StuID:      832153
 *  Date:       26/03/2017
 *  Name:       traverse.c
 *  Purpose:    Contains code for the First Design of Algorithms Assignment.
 *
 *  Comments:
 *      Algorithms based off lecture slides and DPV notes.
 */

/* Defines. Means that I can return these and use if(!SUCCESS)
to verify Output. Ugly, but it works. */
#define FAIL 0
#define SUCCESS 1

/*****************************************************************************/

/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include "traverse.h"
#include "graph.h"
#include "list.h"
#include "stack.h"
#include "queue.h"

/*****************************************************************************/

static void print_path(Graph* graph, list_t* path)
/* Prints all the items in the path stack. */
{
	node_t* c_node;

	c_node = path->foot;

	while(c_node != path->head) {
		printf("%s, ", graph->vertices[c_node->data]->label);
		c_node = c_node->last;
	}
	printf("%s\n", graph->vertices[c_node->data]->label);

}

/*****************************************************************************/

static void print_all_paths_recurse(Graph* graph, int u_id, int destination_id,
	int* visited, list_t* path)
/* Recursive Element of Part 4 */
{
    /* VARIBALE DECLARATIONS */
    Edge *cur_edge, *n_edge;

    cur_edge = graph->vertices[u_id]->first_edge;
    n_edge = cur_edge->next_edge;

	/* Mark current node as visited and store in path */
	visited[u_id] = 1;
	push(path, u_id);

	/* If u = dest, print the current path */
	if(u_id == destination_id) {
		print_path(graph, path);
	} else {
        /* If not destination, recurse for all adjacent vertices. */
		while(cur_edge) {
			if(!visited[cur_edge->v]) {
				print_all_paths_recurse(graph, cur_edge->v, destination_id,
					visited, path);
			}
            /* Next Edge assignment */
			cur_edge = n_edge;
			if(cur_edge) {
				n_edge = n_edge->next_edge;
			}
		}
	}
    /* Backtrack a level */
	pop(path);
	visited[u_id] = 0;
}

/*****************************************************************************/

void print_dfs(Graph* graph, int source_id)
/* Conducts a Depth First Search and prints each element as it's visited.
 * This is a non-recursive implementation. */
{
    /* VARIABLE DECLARATIONS */
    int cur_vert_id = source_id, order = graph->maxn;
    int new_vert_id, i;
    Edge *new_edge;
    int* visited;

    /* Stack Def */
    list_t* dep_stack;
    dep_stack = new_stack();

    /* Error detection, just in case.  */
    if(!dep_stack) {
        fprintf(stderr, "ERROR: New Stack could not be created!");
        exit(FAIL);
    }

    /* Create Array to store visited values in. */
    visited = (int*)malloc((order)*sizeof(int));
    for(i=0; i<order; i++) {
        visited[i] = 0;
    }

    /* Complete operations on the Source Vertex.*/
    push(dep_stack, cur_vert_id);
    printf("%s\n", graph->vertices[source_id]->label);
    visited[source_id] = 1;

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
            if(!(visited[new_vert_id])) {
                visited[new_vert_id] = 1;
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
    /* Return all the borrowed memory you filthy kleptomaniac. */
    free(visited);
    purge_stack(dep_stack);
}

/*****************************************************************************/

void print_bfs(Graph* graph, int source_id)
/* Implements a Bredth First Search on the graph starting from the Source_id,
 * and prints each vertex as they're visited. This implementation will probably
 * fail with negative weighted edges. */
{
    /* VARIABLE DECLARATIONS */
    int source_vert_id = source_id;
    int i, child_vert_id;
    int* dist = (int*)malloc((graph->maxn)*sizeof(int));
    Edge *cur_edge, *n_edge;

    /* Queue Definition, With error check for sanity. */
    list_t* BreQ = new_queue();
    if(!BreQ) {
        fprintf(stderr, "ERROR: Queue could not be formed!");
        exit(FAIL);
    }

    /* Set all distances to "infinity" (or negative 1) */
    for(i=0; i<(graph->maxn); i++) {
        dist[i] = -1;
    }

    /* Enqueue the Source node to begin the algorithm */
    enqueue(BreQ, source_vert_id);
    dist[source_vert_id] = 0;

    /* Commence The Algorithm! Runs for as long as the queue is populated */
    while(queue_size(BreQ)) {
    	/* Open the source vertex and print it's name. */
        source_vert_id = dequeue(BreQ);
        printf("%s\n", graph->vertices[source_vert_id]->label);
        /* Set up the variables needed to step through the children. */
        child_vert_id = graph->vertices[source_vert_id]->first_edge->v;
        cur_edge = graph->vertices[source_vert_id]->first_edge;
        n_edge = cur_edge->next_edge;

        /* Steps through the connected nodes and enqueues anything that hasn't
         * already been added. */
        while(cur_edge) {
            if(dist[child_vert_id] < 0) {
                enqueue(BreQ, child_vert_id);
                dist[child_vert_id] = dist[source_vert_id] + 1;
            }
            cur_edge = n_edge;
            /* Quick check that we aren't on the last node. Ensures all the
             * children are enqueued correctly. */
            if(cur_edge) {
                child_vert_id = cur_edge->v;
                n_edge = n_edge->next_edge;
            }
        }
    }
    /* Return all the space you borrowed you filthy kleptomaniac. */
    free(dist);
    queue_purge(BreQ);
}

/*****************************************************************************/

void detailed_path(Graph* graph, int source_id, int destination_id)
/* A copy of Part 1's solution but edited to stop at the destination id and
 * print out the cumulative weight. */
{
    /* VARIABLE DECLARATIONS */
    int cur_vert_id = source_id, order = graph->maxn;
    int new_vert_id, i;
    int cu_weight = 0, flag_dest = 0;
    Edge *new_edge;
    int* visited;

    /* Stack Def */
    list_t* dep_stack;
    dep_stack = new_stack();

    /* Error detection, just in case.  */
    if(!dep_stack) {
    	fprintf(stderr, "ERROR: New Stack could not be created!");
    	exit(FAIL);
    }

    if(source_id == destination_id) {
    	printf("%s (0km)\n", graph->vertices[source_id]->label);
    	exit(EXIT_SUCCESS);
    }

    /* Create Array to store visited values in. */
    visited = (int*)malloc((order)*sizeof(int));
    for(i=0; i<order; i++) {
        visited[i] = 0;
    }

    /* Complete operations on the Source Vertex.*/
    push(dep_stack, cur_vert_id);
    printf("%s (0km)\n", graph->vertices[source_id]->label);
    visited[source_id] = 1;

    /* The loop operates for as long as the stack is non-empty.  */
    while(!flag_dest && stack_size(dep_stack)) {
        /* Remove the current vertex from the stack,
         * Set vars to it's first edge. */
        cur_vert_id = pop(dep_stack);

        new_edge = graph->vertices[cur_vert_id]->first_edge;
        new_vert_id = new_edge->v;

        /* Ensure that the algorithm runs once the edges run out. */
        while(new_edge) {
            /* Only visit new vertices. */
            if(!(visited[new_vert_id])) {
                visited[new_vert_id] = 1;
                /* Update the cumulative weight */
                cu_weight += new_edge->weight;
                /* Print and push the vertex onto the stack. */
                printf("%s (%dkm)\n", graph->vertices[new_vert_id]->label,
                        cu_weight);
                /**/
                if(new_vert_id == destination_id) {
                     flag_dest = 1;
                     exit(EXIT_SUCCESS);
                 }
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
    /* Return all the borrowed memory you filthy kleptomaniac. */
    free(visited);
    purge_stack(dep_stack);
}

/*****************************************************************************/

void all_paths(Graph* graph, int source_id, int destination_id)
/* Recursively prints all paths between source and destination. Code based on:
 * http://www.geeksforgeeks.org/find-paths-given-source-destination
 */
{
    /* VARIABLE/OBJECT DECLARATIONS */
	int* visited = (int*)malloc(graph->maxn * sizeof(int));
	int i;
	list_t* path = new_stack();

    /* Initialise all nodes as unvisited. */
	for(i=0; i<graph->maxn; i++) {
		visited[i] = 0;
	}

    /* Call the Recursive element of the algrithm */
	print_all_paths_recurse(graph, source_id, destination_id, visited, path);

    /* Free any taken memory, you don't wanna be caught with invalid memory ;)
    */
    free(visited);
    purge_stack(path);
}

/*****************************************************************************/

void shortest_path(Graph* graph, int source_id, int destination_id)
/* Implements a version of Dijkstra's Algorithm and outputs the shortest path
 * as per the spec. Code based on:
 * http://www.codewithc.com/dijkstras-algorithm-in-c/ */
{
    /* VARIABLE DECLARATIONS */
    int cur_id, source_vert_id = source_id;
    int i, child_vert_id, alt;
    int* dist = (int*)malloc((graph->maxn)*sizeof(int));
    int* prev = (int*)malloc((graph->maxn)*sizeof(int));
    list_t* Q = new_queue();
    Edge *cur_edge, *n_edge;
    list_t* path_stack;

    /* Check for similar inputs and outputs so it doesn't segfault */
    if(source_id == destination_id) {
    	printf("%s (0km)\n", graph->vertices[source_id]->label);
    	exit(EXIT_SUCCESS);
    }

    /* Add the source to the queue */
    enqueue(Q, source_vert_id);
    dist[source_vert_id] = 0;

    /* Set all distances & 'previous vals' to "infinity" (or negative 1)
     * & enqueue all nodes */
    for(i=0; i<(graph->maxn); i++) {
        if(i != source_vert_id) {
            dist[i] = -1;
            prev[i] = -1;
        }
    }

    /* Commence The Algorithm! Runs for as long as the queue is populated */
    while(queue_size(Q)) {
        source_vert_id = dequeue(Q);
        
        /* Set up edges for moving */
        cur_edge = graph->vertices[source_vert_id]->first_edge;
        child_vert_id = cur_edge->v;
        n_edge = cur_edge->next_edge;

        /* Loop through all the connected edges and adjust the distances and 
         * the previous node values. Enqueue anything that's changed to review
         * the distances of its children. */
        while(cur_edge) {
            alt = dist[source_vert_id] + cur_edge->weight;
            if((alt < dist[child_vert_id]) || (dist[child_vert_id] == -1)) {
                dist[child_vert_id] = alt;
                prev[child_vert_id] = source_vert_id;
                enqueue(Q, child_vert_id);
            }
            /* Move to the next edge set. */
            cur_edge = n_edge;
            if(cur_edge) {
                child_vert_id = cur_edge->v;
                n_edge = n_edge->next_edge;
            }
        }
    }

    /* Loop back through the previous nodes and add them to the stack. Break
     * once the Source id is found. */
    cur_id = prev[destination_id];
    path_stack = new_stack();
    while(1) {
        push(path_stack, cur_id);
        if(cur_id == source_id) {
        	break; 
        }
        cur_id = prev[cur_id];
    }

    /* Print out the stack. */
    while(stack_size(path_stack)) {
        printf("%s, ", graph->vertices[pop(path_stack)]->label);
    }
    printf("%s (%dkm)\n", graph->vertices[destination_id]->label,
            dist[destination_id]);
    /* Free the stolen memory */
    queue_purge(Q);
    free(dist);
    free(prev);
    free_list(path_stack);
}

/*****************************************************************************/

