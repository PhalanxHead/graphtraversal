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

int min2(int i1, int i2)
/* Returns the minimum of 2 integers */
{
    if(i1 < i2) {
        return i1;
    }
    return i2;
}

int minD(int* arr, int* Q, int arr_size)
/* Returns the index of the minimum Vertex */
{
    int ind, c_min = -1, i = 0;
    for(i=0; i<arr_size; i++) {
        /* Skip if not in Q */
        if(!Q[i]) {
            continue;
        }
        /* Rewrite the minimum if c_min is still inf */
        if(c_min == -1) {
            c_min = arr[i];
            ind = i;
            continue;
        }
        if(arr[i] <= c_min) {
            c_min = arr[i];
            ind = i;
        }
    }
    return ind;
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
    /* Return all the borrowed memory you filthy kleptomaniac. */
    free(visit);
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
    printf("%s (0km)\n", graph->vertices[source_id]->label);
    visit[source_id] = 1;

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
            if(!(visit[new_vert_id])) {
                visit[new_vert_id] = 1;
                /* Update the cumulative weight */
                cu_weight += new_edge->weight;
                /* Print and push the vertex onto the stack. */
                printf("%s (%dkm)\n", graph->vertices[new_vert_id]->label,
                        cu_weight);
                /**/
                if(new_vert_id == destination_id) {
                     flag_dest = 1;
                     break;
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
    free(visit);
    purge_stack(dep_stack);
}

/*****************************************************************************/

void all_paths(Graph* graph, int source_id, int destination_id) {
	printf("not yet implemented: put code for part 4 here\n");
}

/*****************************************************************************/

void shortest_path(Graph* graph, int source_id, int destination_id)
/* Implements a version of Dijkstra's Algorithm and outputs the shortest path
 * as per the spec. Code based on:
 * http://www.codewithc.com/dijkstras-algorithm-in-c/ */
{
    /* VARIABLE DECLARATIONS */
    int cur_id, source_vert_id = source_id;
    int i, child_vert_id, alt, Q_size = graph->maxn;
    int* dist = (int*)malloc((graph->maxn)*sizeof(int));
    int* prev = (int*)malloc((graph->maxn)*sizeof(int));
    int* Q = (int*)malloc((graph->maxn)*sizeof(int));
    Edge *cur_edge, *n_edge;
    list_t* path_stack;

    dist[source_vert_id] = 0;

    /* Set all distances & 'previous vals' to "infinity" (or negative 1)
     * & enqueue all nodes */
    for(i=0; i<(graph->maxn); i++) {
        if(i != source_vert_id) {
            dist[i] = -1;
            prev[i] = -1;
            Q[i] = 1;
        }
    }

    /* Commence The Algorithm! Runs for as long as the queue is populated */
    while(Q_size != 0) {
        source_vert_id = minD(dist, Q, graph->maxn);
        Q[source_vert_id] = 0;
        Q_size -= 1;

        printf("Q_size = %d", Q_size);

        cur_edge = graph->vertices[source_vert_id]->first_edge;
        child_vert_id = cur_edge->v;
        n_edge = cur_edge->next_edge;

        while(cur_edge) {
            alt = dist[source_vert_id] + cur_edge->weight;
            if((alt < dist[child_vert_id]) || (dist[child_vert_id] == -1)) {
                dist[child_vert_id] = alt;
                prev[child_vert_id] = source_vert_id;
            }
            cur_edge = n_edge;
            if(cur_edge) {
                child_vert_id = cur_edge->v;
                n_edge = n_edge->next_edge;
            }
        }
    }
    cur_id = prev[destination_id];
    path_stack = new_stack();
    while(dist[cur_id] >= 0) {
        push(path_stack, cur_id);
        cur_id = prev[cur_id];
    }
    while(stack_size(path_stack)) {
        printf("%s, ", graph->vertices[pop(path_stack)]->label);
    }
    printf("%s (%dkm)", graph->vertices[destination_id]->label, 
            dist[destination_id]);
    free(Q);
    free(dist);
    free(prev);
    free_list(path_stack);
}

/*****************************************************************************/

/*
Pseudo Code for Dijkstra's Algorithm

   function Dijkstra(Graph, source):
       dist[source]  := 0                     // Distance from source to source
       for each vertex v in Graph:            // Initializations
           if v ≠ source
               dist[v]  := infinity           // Unknown distance function from source to v
               previous[v]  := undefined      // Previous node in optimal path from source
           end if
           add v to Q                         // All nodes initially in Q
       end for

      while Q is not empty:                  // The main loop
          u := vertex in Q with min dist[u]  // Source node in first case
          remove u from Q

          for each neighbor v of u:           // where v has not yet been removed from Q.
              alt := dist[u] + length(u, v)
              if alt < dist[v]:               // A shorter path to v has been found
                  dist[v]  := alt
                  previous[v]  := u
              end if
          end for
      end while
      return dist[], previous[]
  end function
*/
