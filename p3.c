/*
 * Problem 3 in Assignment 2
 * COMP20007 Design of Algorithms
 * Semester 1 2019
 *
 * Written by: [ YOUR NAME HERE ]
 */

/* --- DO NOT CHANGE THE CODE BELOW THIS LINE --- */
#include<stdio.h> 
#include<stdlib.h> 
#include <assert.h>
   
struct node 
{ 
    int key; 
    struct node *left, *right; 
}; 

void printLevelOrder(struct node* root); 
void printGivenLevel(struct node* root, int level) ;  
   
// A utility function to create a new BST node 
struct node *newNode(int item) 
{ 
    struct node *temp =  (struct node *)malloc(sizeof(struct node)); 
    temp->key = item; 
    temp->left = temp->right = NULL; 
    return temp; 
} 
   
// A utility function to do inorder traversal of BST 
void inorder(struct node *root) 
{ 
    if (root != NULL) 
    { 
        inorder(root->left); 
        printf("%d, ", root->key); 
        inorder(root->right); 
    } 
} 
   
/* A utility function to insert a new node with given key in BST */
struct node* insert(struct node* node, int key) 
{ 
    /* If the tree is empty, return a new node */
    if (node == NULL) return newNode(key); 
  
    /* Otherwise, recur down the tree */
    if (key < node->key) 
        node->left  = insert(node->left, key); 
    else if (key > node->key) 
        node->right = insert(node->right, key);    
  
    /* return the (unchanged) node pointer */
    return node; 
}

int maxDepth(struct node* node)  
{ 
   if (node==NULL)  
       return 0; 
   else 
   { 
       /* compute the depth of each subtree */
       int lDepth = maxDepth(node->left); 
       int rDepth = maxDepth(node->right); 
  
       /* use the larger one */
       if (lDepth > rDepth)  
           return(lDepth+1); 
       else return(rDepth+1); 
   } 
}  

int sizeofTree(struct node* node)  
{  
    if (node == NULL)  
        return 0;  
    else
        return(sizeofTree(node->left) + 1 + sizeofTree(node->right));  
}  
int fill_array(struct node* root, int array[], int pos) {
    if (root->left != NULL) {
        pos = fill_array(root->left, array, pos);
    }
    array[pos++] = root->key;
    if (root->right != NULL) {
        pos = fill_array(root->right, array, pos);
    }
    return pos; // return the last position filled in by this invocation
}

/* A function that constructs Balanced Binary Search Tree from a sorted array */
struct node* sortedArrayToBST(int arr[], int start, int end) 
{ 
    /* Base Case */ 
    if (start > end) 
        return NULL; 
    /* Get the middle element and make it root */
    int mid = (start + end)/2;  
    struct node *root = newNode(arr[mid]); 
/* Recursively construct the left subtree and make it 
left child of root */
    root->left = sortedArrayToBST(arr, start, mid-1); 
/* Recursively construct the right subtree and make it 
right child of root */
    root->right = sortedArrayToBST(arr, mid+1, end); 
    if(root->right!=NULL && root->left==NULL){
        root->left = newNode(-1); 
    }
    return root; 
} 


void printLevelOrder(struct node* root) 
{ 
    int h = maxDepth(root); 
    int i; 
    for (i=1; i<=h; i++) 
        printGivenLevel(root, i); 
} 
/* Print nodes at a given level */
void printGivenLevel(struct node* root, int level) 
{ 
    if (root == NULL) 
        return; 
    if (level == 1) 
        printf("%d\n", root->key); 
    else if (level > 1) 
    { 
        printGivenLevel(root->left, level-1); 
        printGivenLevel(root->right, level-1); 
    } 
} 

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


    for (i = 0; i<size; i++){
        currentnode = scanf("%d\n", &nodes[i]); 
        if(!currentnode){
            fprintf(stderr, "Error: invalid input format\n"); 
            exit(EXIT_FAILURE); 
        }
    } 
    // node_t *rootNode = NULL;  
    // rootNode = insert_node_to_tree(rootNode, nodes[0]); 

    int k; 
    struct node *root = NULL; 
    root = insert(root, nodes[0]);
    for(k=1; k<size; k++){
      insert(root, nodes[k]); 
    } 
    int height = maxDepth(root); 
    int treesize = sizeofTree(root); 
    printf("%d\n", treesize);
    printf("%d\n", height);
    int arr[treesize]; 
    fill_array(root, arr, 0); 
    // for (k = 0; k<treesize; k++){
    //     printf("%d\n", arr[k]); 
    // }
    struct node *root2 = sortedArrayToBST(arr, 0, treesize-1); 
    int bbtreesize = sizeofTree(root2); 
    printf("%d\n", bbtreesize); 
    printLevelOrder(root2); 
}
