/*
 * Problem 3 in Assignment 2
 * COMP20007 Design of Algorithms
 * Semester 1 2019
 *
 * Written by: [ Tian Qiu ]
 */

/* --- DO NOT CHANGE THE CODE BELOW THIS LINE --- */

/*
the functions used in the q3, reference from the website GeeksforGeeks
*/
#include<stdio.h> 
#include<stdlib.h> 
#include <assert.h>
 

typedef struct node node_t; 

struct node 
{ 
    int element; 
    struct node *left; 
    struct node *right; 
}; 

node_t *create_new_node(int number); 
void printLevelByLevel(node_t* root, int level);  
int Height(node_t* node); 
int convertTreeToArray(node_t* root, int array[], int pos); 
int numOfNode(node_t* node); 
node_t* insert_node(node_t* node, int element); 
node_t* sortedArrayToBST(int arr[], int start, int end); 



/*these are the only hundred lines of the code I have to deal with */



void problem_3();

int main(int argc, char **argv) {
  problem_3();
  return 0;
}

/* --- DO NOT CHANGE THE CODE ABOVE THIS LINE --- */

/* TODO: Implement your solution to Problem 3 in this function. */
void problem_3() {
    int size, i, currentnode; 
    scanf("%d\n", &size); 
    int nodes[size]; 

    //read in the input
    for (i = 0; i<size; i++){
        currentnode = scanf("%d\n", &nodes[i]); 
        if(!currentnode){
            fprintf(stderr, "Error: invalid input format\n"); 
            exit(EXIT_FAILURE); 
        }
    } 

    //insert all the input to BST
    int k; 
    node_t *root = NULL; 
    root = insert_node(root, nodes[0]);
    for(k=1; k<size; k++){
      insert_node(root, nodes[k]); 
    } 
    //calculate the height
    int height = Height(root); 

    //calculate the size
    int treesize = numOfNode(root); 
    printf("%d\n", treesize);
    printf("%d\n", height);

    //convert the tree into the sorted array 
    int arr[treesize]; 
    convertTreeToArray(root, arr, 0); 

    //convert the sorted array into the balanced BST
    struct node *root2 = sortedArrayToBST(arr, 0, treesize-1); 

    //find out the size of the balanced BST
    int bbtreesize = numOfNode(root2); 

    printf("%d\n", bbtreesize); 

    //print out the array in the certain order 
    int newheight = Height(root2); 
    int l; 
    for (l=1; l<=newheight; l++) 
        printLevelByLevel(root2, l); 
}

node_t *create_new_node(int number) 
{ 
    node_t *temp =  (node_t *)malloc(sizeof(node_t)); 
    temp->element = number; 
    temp->left = temp->right = NULL; 
    return temp; 
} 

/* Print nodes at a level order */
void printLevelByLevel(node_t* root, int level) 
{ 
    if (root == NULL) 
        return; 
    if (level == 1) 
        printf("%d\n", root->element); 
    else if (level > 1) 
    { 
        printLevelByLevel(root->left, level-1); 
        printLevelByLevel(root->right, level-1); 
    } 
} 

int Height(node_t* node)  
{ 
   if (node==NULL)  
       return 0; 
   else 
   { 
       int height_of_left_tree = Height(node->left); 
       int height_of_right_tree = Height(node->right); 

       if (height_of_left_tree > height_of_right_tree)  
           return(height_of_left_tree+1); 
       else return(height_of_right_tree+1); 
   } 
}  

int convertTreeToArray(node_t* root, int array[], int pos) {
    if (root->left != NULL) {
        pos = convertTreeToArray(root->left, array, pos);
    }
    array[pos++] = root->element;
    if (root->right != NULL) {
        pos = convertTreeToArray(root->right, array, pos);
    }
    return pos; 
}

int numOfNode(node_t* node)  
{  
    if (node == NULL)  
        return 0;  
    else
        return(numOfNode(node->left) + 1 + numOfNode(node->right));  
} 


node_t* insert_node(node_t* node, int key) 
{ 

    if (node == NULL) return create_new_node(key); 
  
    if (key < node->element) 
        node->left  = insert_node(node->left, key); 
    else if (key > node->element) 
        node->right = insert_node(node->right, key);    
  
    return node; 
}


struct node* sortedArrayToBST(int arr[], int start, int end) 
{ 
    if (start > end) 
        return NULL; 
    int mid = (start + end)/2;  
    node_t *root = create_new_node(arr[mid]); 

    root->left = sortedArrayToBST(arr, start, mid-1); 

    root->right = sortedArrayToBST(arr, mid+1, end); 

    //add the new -1 node into the tree if the tree is not complete
    if(root->right!=NULL && root->left==NULL){
        root->left = create_new_node(-1); 
    }
    return root; 
} 
