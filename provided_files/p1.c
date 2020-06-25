/*
 * Problem 1 in Assignment 2
 * COMP20007 Design of Algorithms
 * Semester 1 2019
 *
 * Written by: [ Tian Qiu ]
 */


/*for the better understanding, read the psuedocode for question 7a and 7b first, that will make more sense*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* --- DO NOT CHANGE THE CODE BELOW THIS LINE --- */

void problem_1_a();
void problem_1_b();
void print_usage_and_exit(char **argv);

int* buildheap(int a[], int n);
void maxheapify(int a[], int i, int heapsize);
void right_max(int* heap, int n, int root); 
void heapify(int* heap, int n, int i); 

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
    //read in all the data
    int heapsize, value_read, i; 
    scanf("%d\n", &heapsize); 
    int heap[heapsize]; 
    for (i = 0; i<heapsize; i++){
        value_read = scanf("%d\n", &heap[i]); 
    } 
    //build the max heap tree
    int* newHeap; 
    newHeap = buildheap(heap, heapsize); 

    //print that out
    for(i=0; i<heapsize; i++){
        printf("%d\n", newHeap[i]); 
    }
}


/* TODO: Implement your solution to Problem 1.b. in this function. */
void problem_1_b() {
    int heapsize, i; 
    scanf("%d", &heapsize); 
    int heap[heapsize]; 
    for(i= 0; i<heapsize; i++){
        scanf("%d", &heap[i]); 
    }
    int* newheap = buildheap(heap, heapsize); 
    int heap2[heapsize+1]; 
    for(i= 1; i<=heapsize; i++){
        heap2[i] = newheap[i-1]; 
    }
    right_max(heap2, heapsize, 1); 
    for(i = 1; i<=heapsize; i++){
        printf("%d\n", heap2[i]); 
    }

}

int* buildheap(int arr[], int heapsize)
{
    int n = heapsize;
    int k;
    for (k = n/2; k >= 0; k--) {
        maxheapify(arr, k, heapsize);
    }
    return arr;
}




void maxheapify(int arr[], int i, int heapsize)
{
    int tempvalue, largest, left, right;
    left = (2*i+1);
    right = ((2*i)+2);
    if (left >= heapsize)
        return;
    else {
        if (left < heapsize && arr[left] > arr[i]) 
            largest = left;
        else
            largest = i;
        if (right < heapsize && arr[right] > arr[largest])  
            largest = right;
        if (largest != i) {
            tempvalue = arr[i];
            arr[i] = arr[largest];
            arr[largest] = tempvalue;
            maxheapify(arr, largest, heapsize);
        }
    }
}

//the maxheapify function don't work here, so I just reference from the textbook to rewrite a heapify function
void heapify(int* heap, int n, int i){
    int non_leaf = i, value_of_node = heap[non_leaf], judge = 0; 
    while(!judge && 2*non_leaf <= n){
        int numleaf = 2*non_leaf; //number of the leaf root got
        if(numleaf<n && heap[numleaf]<heap[numleaf+1]){
            numleaf = numleaf+1; 
        }
        if(value_of_node>=heap[numleaf]){
            judge = 1; 
        }else{
            heap[non_leaf] = heap[numleaf]; 
            non_leaf = numleaf; 
        }
    }
    heap[non_leaf] = value_of_node; 
}

void right_max(int* arr, int n, int i){
    int left = i*2; 
    int right = i*2+1; 
    if(left>=n){
        return; 
    }
    if(arr[left]>arr[right]){
        int temp = arr[right]; 
        arr[right] = arr[left]; 
        arr[left] = temp; 
        heapify(arr, n, left); 
    }
    right_max(arr, n, left); 
    right_max(arr, n, right); 
}