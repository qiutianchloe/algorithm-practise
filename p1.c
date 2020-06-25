/*
 * Problem 1 in Assignment 2
 * COMP20007 Design of Algorithms
 * Semester 1 2019
 *
 * Written by: [ YOUR NAME HERE ]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* --- DO NOT CHANGE THE CODE BELOW THIS LINE --- */

void problem_1_a();
void problem_1_b();
void print_usage_and_exit(char **argv);
int* buildmaxheap(int a[], int n);
int* buildmaxheap2(int a[], int n);
void maxheapify(int a[], int i, int heapsize);
void maxheapify2(int a[], int i, int heapsize); 
void rightHeap(int a[], int n, int i); 
void insert_into_right_handed_max(int* heap,int i, int heap_size); char left_or_right(int i);
int parent_of_child(int i);
void swap_in_array(int* array, int element1, int element2);
void recurse(int* heap, int n, int root); 
void ShiftDown(int* heap, int n, int i); 
void build_heap(int *heap, int n); 

int main(int argc, char **argv) {

    if (argc != 2) {
        print_usage_and_exit(argv);
    }

    /* If the argument provided is "a" then run problem_1_a(),
    * run problem_1_b() for "b", and fail otherwise. */
    if (strcmp(argv[1], "a") == 0) {
        problem_1_a();
    }
    else if (strcmp(argv[1], "b") == 0) {
        problem_1_b();
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

/* TODO: Implement your solution to Problem 1.a. in this function. */
void problem_1_a() {
    int size, value_read, i; 
    scanf("%d\n", &size); 
    int heap[size]; 
    for (i = 0; i<size; i++){
        value_read = scanf("%d\n", &heap[i]); 
        if(!value_read){
            fprintf(stderr, "Error: invalid input format\n"); 
            exit(EXIT_FAILURE); 
        }
    } 
    int* newHeap; 
    newHeap = buildmaxheap(heap, size); 

    for(i=0; i<size; i++){
        printf("%d\n", newHeap[i]); 
    }
}


int* buildmaxheap(int a[], int n)
{
    int heapsize = n;
    int j;
    for (j = n/2; j >= 0; j--) {
        maxheapify(a, j, heapsize);
    }
    return a;
}




void maxheapify(int a[], int i, int heapsize)
{
    int temp, largest, left, right;
    left = (2*i+1);
    right = ((2*i)+2);
    if (left >= heapsize)
        return;
    else {
        if (left < (heapsize) && a[left] > a[i]) 
            largest = left;
        else
            largest = i;
        if (right < (heapsize) && a[right] > a[largest])  
            largest = right;
        if (largest != i) {
            temp = a[i];
            a[i] = a[largest];
            a[largest] = temp;
            maxheapify(a, largest, heapsize);
        }
    }
}

/* TODO: Implement your solution to Problem 1.b. in this function. */
void problem_1_b() {
    // int size, value_read, i; 
    // scanf("%d\n", &size); 
    // int heap[size]; 
    // for (i = 0; i<size; i++){
    //     value_read = scanf("%d\n", &heap[i]); 
    //     if(!value_read){
    //         fprintf(stderr, "Error: invalid input format\n"); 
    //         exit(EXIT_FAILURE); 
    //     }
    // } 
    // int* newHeap; 
    // newHeap = buildmaxheap(heap, size); 

    // rightHeap(newHeap, size, 0); 
    // int counter ; 
    // for(counter = 0; counter<size; counter++){
    //     printf("%d\n", newHeap[counter]); 
    // }
    int n, i; 
    scanf("%d", &n); 
    int heap[n]; 
    for(i= 0; i<n; i++){
        scanf("%d", &heap[i]); 
    }
    int* newheap = buildmaxheap(heap, n); 
    int heap2[n+1]; 
    for(i= 1; i<=n; i++){
        heap2[i] = newheap[i-1]; 
    }
    recurse(heap2, n, 1); 
    for(i = 1; i<=n; i++){
        printf("%d\n", heap2[i]); 

    }

}
void build_heap(int *heap, int n){
    int i; 
    for(i = n/2; i>0; i--){
        int k = i, v = heap[k], done = 0; 
        while(!done && 2*k <= n){
            int j = 2*k; 
            if(j<n && heap[j]<heap[j+1]){
                j = j+1; 
            }
            if(v>=heap[j]){
                done = 1; 
            }else{
                heap[k] = heap[j]; 
                k = j; 
            }
        }
        heap[k] = v; 
    }
}

void ShiftDown(int* heap, int n, int i){
    int k = i, v = heap[k], done = 0; 
    while(!done && 2*k <= n){
        int j = 2*k; 
        if(j<n && heap[j]<heap[j+1]){
            j = j+1; 
        }
        if(v>=heap[j]){
            done = 1; 
        }else{
            heap[k] = heap[j]; 
            k = j; 
        }
    }
    heap[k] = v; 
}
void recurse(int* heap, int n, int root){
    if(root*2>=n){
        return; 
    }
    if(heap[root*2]>heap[root*2+1]){
        int temp = heap[root*2+1]; 
        heap[root*2+1] = heap[root*2]; 
        heap[root*2] = temp; 
        ShiftDown(heap, n, root*2); 
    }
    recurse(heap, n, root*2); 
    recurse(heap, n, root*2+1); 
}