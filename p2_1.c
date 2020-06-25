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

typedef struct list list_t; 

struct node {
	int y;                    /* the node name which transfer into the int */
  int weight;               /* the weight of edge which connect to node */
	node_t *next;             /* the pointer that point to the next node */
};


struct list {
	node_t *head;             /* the pointer that point to the next node */
  node_t *foot; 
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
int read_graph2(graph_t *g); 
list_t *make_new_list(void); 
void free_graph(graph_t *g);
void insert_node_to_list(list_t *fuckingList, int node); 
void print_the_list(list_t *fuck);
int get_size_of_list(list_t *fuck); 

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
  graph_t *currentGraph = make_new_graph(); 
  //get the  value of k and read in the graph  
  int number_of_step = read_graph2(currentGraph); 
  //get the size of the graph
  int number_of_node = currentGraph->nvertices;
  //create two matrix for different purpose 
  int min_to_end[number_of_step+1][number_of_node]; 
  int prev[number_of_step+1][number_of_node];
  //initialize the graph 
  int k, j; /* counter */

  for(k = 0; k<number_of_step+1; k++){
    for(j = 0; j<number_of_node; j++){
      if(k==0 && j==number_of_node-1){
        min_to_end[k][j] = 0; 
        prev[k][j] = number_of_node-1; 
      }
      else{
        min_to_end[k][j] = INFI; 
        prev[k][j] = NONODE; 
      }
    }
  }

  //to fill the 2d array
  for (k = 1; k<number_of_step+1; k++){
    for(j=0; j<number_of_node; j++){
      int min_distance = INFI; 
      int prev_node = NONODE; 
      node_t *currentNode = currentGraph->edges[j]; 
      while(currentNode != NULL){
        int this_node = currentNode->y; 
        int this_weight = currentNode->weight; 
        if(min_to_end[k-1][this_node]!=INFI){
          int newWeight = this_weight + min_to_end[k-1][this_node]; 
          if(min_distance==INFI||newWeight<min_distance){
            min_distance = newWeight; 
            prev_node = this_node; 
          }else{
            //do nothing
          }
        }
        currentNode = currentNode->next; 
      }
      if(min_distance!=INFI){
        if(min_to_end[k-1][j]<min_distance && min_to_end[k-1][j]!=INFI){
          min_distance = min_to_end[k-1][j]; 
          prev_node = prev[k-1][j]; 
        }
      }
      min_to_end[k][j] = min_distance; 
      prev[k][j] = prev_node; 
    }
  }
  if(min_to_end[number_of_step][0] == INFI){
    printf("No Path"); 
  }else{
    list_t *newList = make_new_list(); 
    int h = 0; 
    int element = prev[number_of_step][0]; 
    insert_node_to_list(newList, element); 
    while(element!= number_of_node-1){ 
      h = h+1; 
      element = prev[number_of_step-h][element]; 
      if(element == newList->foot->y){
        //do nothing
      }else{
        insert_node_to_list(newList, element); 
      }
    }
    printf("%d\n",min_to_end[number_of_step][0]); 
    int sizeOfArray = get_size_of_list(newList);
    printf("%d\n", sizeOfArray); 
    printf("0\n"); 
    print_the_list(newList);
  }

  free_graph(currentGraph);
}

list_t
*make_new_list(void){
    /* initialise the list */
    
    list_t *list;
    list = (list_t*)malloc(sizeof(*list));
    assert(list!=NULL);
    list->head = NULL; 
    list->foot = NULL; 
    return list;
}

void
insert_node_to_list(list_t *fuckingList, int node){
    node_t *new;
    new =(node_t *)malloc(sizeof(*new));
    assert(fuckingList!=NULL && new!=NULL);
    new->y = node; 
    new->weight = 0; 
    if(fuckingList->head==NULL){
      fuckingList->head = new; 
      fuckingList->foot = new; 
      new->next = NULL; 
    }else{
      new->next = NULL; 
      fuckingList->foot->next = new; 
      fuckingList->foot = new; 
    }
}

void
print_the_list(list_t *fuck){
  node_t *currentnode = fuck->head; 
  while(currentnode!=NULL){
    printf("%d\n", currentnode->y); 
    currentnode = currentnode->next; 
  }
}

int
get_size_of_list(list_t *fuck){
  int n = 0; 
  node_t *currentnode = fuck->head; 
  while(currentnode!=NULL){
    n = n+1; 
    currentnode = currentnode->next; 
  }
  return n; 
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



int
read_graph2(graph_t *g){
    assert(g!=NULL);
    int number_of_step;                     /* the value of k*/
    int m=0;                               /* number of edges */
    int n=0;                               /* number of vertices */
    int z;                                 /* weight of edges */
    int x, y;                              /* edges (x, y) */

    scanf("%d %d\n", &n, &number_of_step);

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
    return number_of_step; 
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