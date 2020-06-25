#include<stdio.h> 
#include<stdlib.h> 
/* A Binary Tree node */
struct TNode 
{ 
    int data; 
    struct TNode* left; 
    struct TNode* right; 
}; 
struct TNode* newNode(int data); 

/* Function protoypes */
void printGivenLevel(struct TNode* root, int level); 
int height(struct TNode* node); 
struct TNode* newNode(int data); 
/* Function to print level order traversal a tree*/
void printLevelOrder(struct TNode* root) 
{ 
    int h = height(root); 
    int i; 
    for (i=1; i<=h; i++) 
        printGivenLevel(root, i); 
} 
/* Print nodes at a given level */
void printGivenLevel(struct TNode* root, int level) 
{ 
    if (root == NULL) 
        return; 
    if (level == 1) 
        printf("%d ", root->data); 
    else if (level > 1) 
    { 
        printGivenLevel(root->left, level-1); 
        printGivenLevel(root->right, level-1); 
    } 
} 
/* Compute the "height" of a tree -- the number of 
nodes along the longest path from the root node 
down to the farthest leaf node.*/
int height(struct TNode* node) 
{ 
    if (node==NULL) 
        return 0; 
    else
    { 
        /* compute the height of each subtree */
        int lheight = height(node->left); 
        int rheight = height(node->right); 
        /* use the larger one */
        if (lheight > rheight) 
            return(lheight+1); 
        else return(rheight+1); 
    } 
} 
/* A function that constructs Balanced Binary Search Tree from a sorted array */
struct TNode* sortedArrayToBST(int arr[], int start, int end) 
{ 
    /* Base Case */ 
    if (start > end) 
        return NULL; 
    /* Get the middle element and make it root */
    int mid = (start + end)/2;  
    struct TNode *root = newNode(arr[mid]); 
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
/* Helper function that allocates a new node with the 
given data and NULL left and right pointers. */
struct TNode* newNode(int data) 
{ 
    struct TNode* node = (struct TNode*) 
                          malloc(sizeof(struct TNode)); 
    node->data = data; 
    node->left = NULL; 
    node->right = NULL; 
    return node; 
} 
/* A utility function to print preorder traversal of BST */
void preOrder(struct TNode* node) 
{ 
    if (node == NULL) 
        return; 
    preOrder(node->left);
    printf("%d ", node->data); 
    preOrder(node->right); 
} 
/* Driver program to test above functions */
int main() 
{ 
//int arr[] = {4, 34, 37, 104, 113, 145, 157, 173, 177, 183, 192, 193, 242, 248, 256, 268, 269, 272, 275, 291, 304, 351, 369, 373, 374, 376, 401, 404, 412, 474, 528, 538, 551, 577, 600, 629, 637, 655, 661, 664, 675, 684, 686, 703, 706, 708, 709, 714, 727, 754, 757, 860, 863, 881, 891, 896, 926, 928, 942, 946, 958, 993}; 
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8}; 
    int n = sizeof(arr)/sizeof(arr[0]);  
    printf("%d\n", n); 
    /* Convert List to BST */
    struct TNode *root = sortedArrayToBST(arr, 0, n-1); 
    printf("n PreOrder Traversal of constructed BST "); 
    printLevelOrder(root); 
    printf("\n"); 
    return 0; 
}