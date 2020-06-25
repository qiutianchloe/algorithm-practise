/*
 * Problem 2 in Assignment 2
 * COMP20007 Design of Algorithms
 * Semester 1 2019
 *
 * Written by: [ YOUR NAME HERE ]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>



#define MAXV 10000 /* maximum number of vertices*/

#define INFI -1 /* maximum number of vertices*/

#define NONODE -1

typedef struct node node_t;

typedef struct graph graph_t;

struct node {
	int y;                    /* the node name which transfer into the int */
    int weight;               /* the weight of edge which connect to node */
	node_t *next;             /* the pointer that point to the next node */
};


struct graph{
    node_t *edges[MAXV];      
    int degree[MAXV];         /* outdegree of each vertex */
    int nvertices;            /* number of verices in graph */
    int nedges;               /* number of edges in graph */
    int start;                /* startpoint of the path */
    int end;                  /* endpoint of the path*/
};


/* graph operations */
void insert_edge(graph_t *g, int x, int y, int z);
graph_t *make_new_graph(void);
void read_graph(graph_t *g);
void free_graph(graph_t *g);

/* --- DO NOT CHANGE THE CODE BELOW THIS LINE --- */

void problem_2_a();
void problem_2_b();
void print_usage_and_exit(char **argv);

int main(int argc, char **argv) {
  if (argc != 2) {
    print_usage_and_exit(argv);
  }

  /* If the argument provided is "a" then run problem_2_a(),
   * run problem_2_b() for "b", and fail otherwise. */
  if (strcmp(argv[1], "a") == 0) {
    problem_2_a();
  } else if (strcmp(argv[1], "b") == 0) {
    problem_2_b();
  } else {
    print_usage_and_exit(argv);
  }

  return 0;
}

/* Print the usage information and exit the program. */
void print_usage_and_exit(char **argv) {
  fprintf(stderr, "usage: %s [ab]\n", argv[0]);
  exit(EXIT_FAILURE);
}

/* --- DO NOT CHANGE THE CODE ABOVE THIS LINE --- */

/* TODO: Implement your solution to Problem 2.a. in this function. */
void problem_2_a() {
    graph_t *currentGraph = make_new_graph();   
    read_graph(currentGraph);
    int nnodes = currentGraph->nvertices; 
    int valueToEnd[nnodes]; //the weight of nodes that to the end
    int preNode[nnodes]; //which is the previous node
    int i; 
    //initialize the array
    for(i = 0; i<nnodes; i++){
      valueToEnd[i] = INFI; 
      preNode[i] = NONODE; 
    }
    //input the end node value itself
    valueToEnd[nnodes-1] = 0;
    preNode[nnodes-1] = NONODE; 

    for(i=nnodes-2; i>=0; i--){
      node_t *currentnode = currentGraph->edges[i]; 
      int minWeight = INFI; 
      int minPre = NONODE; 
      while(currentnode!=NULL){
        int node = currentnode->y; 
        if(valueToEnd[node]!=INFI){
          int currentWeight = currentnode->weight+valueToEnd[node]; 
          if(minWeight==INFI||currentWeight<minWeight){
            minWeight= currentWeight; 
            minPre = node; 
          }
        }
        currentnode = currentnode->next; 
      }
      valueToEnd[i] = minWeight; 
      preNode[i] = minPre; 
    } 

    if(valueToEnd[0]==INFI){
      printf("No Path"); 
    }else{
      int finalPath[nnodes]; 
      finalPath[0] = 0; 
      int counter = 0; 
      int node = 0; 
      while(node!=currentGraph->end){
        counter = counter + 1; 
        node = preNode[node]; 
        finalPath[counter] = node; 
      }
      printf("%d\n", valueToEnd[0]); 
      printf("%d\n", counter); 
      int k=0; 
      for(k=0; k<=counter; k++){
        printf("%d\n", finalPath[k]); 
      }

    }
    free_graph(currentGraph);

}

/* TODO: Implement your solution to Problem 2.b. in this function. */
void problem_2_b() {

}



graph_t
*make_new_graph(void){
    /* initialise the graph */
    
    graph_t *g;
    g = (graph_t*)malloc(sizeof(*g));
    assert(g!=NULL);
    
    int i;     /* counter */
    
    /* make all the int begin with zero */
    g -> nvertices = 0;
    g -> nedges = 0;
    g -> start = 0;
    g -> end = 0; 
    for(i=0; i<MAXV; i++){
        g -> degree[i] = 0;
    }
    
    /* make all the element in the pointer array point to NULL */
    for(i=0; i<MAXV; i++){
        g -> edges[i] = NULL;
    }
    return g;
}

void
read_graph(graph_t *g){
    assert(g!=NULL);
    int m=0;                               /* number of edges */
    int n=0;                               /* number of vertices */
    int z;                                 /* weight of edges */
    int x, y;                              /* edges (x, y) */

    scanf("%d\n", &n);

    int i;  /* counter */
    for(i= 0; i<n; i++){
        int noutdegree = 0; 
        scanf("%d\n", &noutdegree);
        m = m+noutdegree; 
        int j; /*counter*/
        for(j = 0; j<noutdegree; j++){
            x = i; 
            scanf("%d %d\n", &y, &z); 
            insert_edge(g, x, y, z);
        }
    }
    
    g -> nvertices = n; 
    g -> nedges = m;
    g -> start = 0; 
    g -> end = n-1; 
}

void
insert_edge(graph_t *g, int x, int y, int z){
    /* create a new edge and borrow the memory */
    node_t *new;
    new =(node_t *)malloc(sizeof(*new));
    assert(g!=NULL && new!=NULL);
    
    /* fill the information about this edge */
    new->weight = z;
    new->y = y;
    
    /* make the new edge connected to last edge connected to this startpoint */
    new->next= g->edges[x];
    /* make new edge become the new last edge connected to this startpoint */
    g->edges[x] = new;
    /* the degree of the startpoint increased */
    g->degree[x] ++;
}
void 
free_graph(graph_t *g){
    /* return the memory back */
    node_t *curr, *prev;
    assert(g!=NULL);
    int i;            
    /* return all the memory that borrow for the edge of every startpoint */
    for(i=0; i<MAXV; i++){
        if(g -> edges[i] != NULL){
            curr = g -> edges[i];
            while(curr){
                prev = curr;
                curr = curr -> next;
                free(prev);
            }
        }
    } 
    /* return the memory that borrow for the graph */
    free(g);
}