#include <stdio.h>
#include <stdlib.h>

typedef struct NODE_s *NODE;
typedef struct NODE_s {
    NODE left;
    NODE right;
    int key;
    void *data;
} NODE_t[1];

typedef struct {
    NODE root;
} BST_t[1], *BST;


BST bst_init(){
    BST tree = (BST)malloc(sizeof(BST_t));
    tree->root = NULL;
    return tree;
}

NODE bst_init_node( int key, void *data) {
    NODE node = (NODE)malloc(sizeof(NODE_t));
    node->left = NULL;
    node->right = NULL;
    node->key = key;
    node->data = data;
    return node;
}

void bst_insert(BST tree, int key, void *data) {
    if(tree == NULL) {
        printf("Error: The tree not initialized.\n");
    }
    else if(tree->root == NULL) {
        tree->root = bst_init_node(key, data);
    }
    else {
        NODE node = tree->root;
        while(node != NULL) {
            if(key < node->key) {
                if(node->left != NULL) {
                    node = node->left;
                }
                else{
                    node->left = bst_init_node(key, data);
                    node = NULL;
                }
            }
            else if(key > node->key) {
                if(node->right != NULL) {
                    node = node->right;
                }
                else{
                    node->right = bst_init_node(key, data);
                    node = NULL;
                }
            }
            else{
                printf("Error: Duplicate key Entry! No action is done. \n");
                node = NULL;
            }
        }
    }
}

NODE bst_insert_rec(NODE node, int key, void *data)
{
    if(node == NULL){
        node = bst_init_node(key, data);
    }
    else {
        if(key < node->key) {
            node->left = bst_insert_rec(node->left, key, data);
        }
        else if(key > node->key) {
            node->right = bst_insert_rec(node->right, key, data);
        }
        else {
            printf("Error duplicate key entered!\n");
        }
    }
    return node;
}

void bst_insert_recursion(BST tree, int key, void *data)
{
    if(tree == NULL) {
        printf("Error: The tree not initialized.\n");
    }
    else if(tree->root == NULL) {
        tree->root = bst_init_node(key, data);
    }
    else {
        bst_insert_rec(tree->root, key, data);
    }
}

void bst_print_side_way(int key, int height)
{
    int i =1;
    while (i < height){
        printf("----");
        i++;
    }
    printf("%d\n", key);
}

void bst_reverse_in_order(NODE node, int height)
{
    if(node != NULL) {
        height++;
        if(node->right != NULL){
            bst_reverse_in_order(node->right, height);
        }
        bst_print_side_way(node->key, height);
        if(node->left != NULL){
            bst_reverse_in_order(node->left, height);
        }
    }
}




void RR(BST tree, NODE gParent, NODE parent, NODE child)
{
    parent->left = child->right;
    child->right = parent;
    if(parent == tree->root) {
        tree->root = child;
    }
    else {
        gParent->right = child;
    }
}

void makeBackbone(BST tree)
{
    NODE gParent = tree->root;
    NODE parent = tree->root;
    while( parent != NULL) {
        NODE child = parent->left;
        if(child != NULL) {
            RR(tree, gParent, parent, child);
            parent = child;
        }
        else {
            gParent = parent;
            parent = parent->right;
        }
    }
}

void LR(BST tree, NODE gParent, NODE parent, NODE child)
{
    NODE temp = child->left;
    child->left = parent;
    if(parent == tree->root) {
        tree->root = child;
    }
    else {
        gParent->right = child;
    }
    parent->right = temp;
}

void leftRotation(BST tree, int lrCount)
{
    NODE parent = tree->root;
    NODE gParent = (NODE)tree;
    NODE child = parent->right;
    while(lrCount > 0) {
        LR(tree, gParent, parent, child);
        gParent = child;
        parent = child->right;
        child = parent->right;
        lrCount--;
    }
}

int log_2_function(int value)
{
    int i;
    for (i = 0; value > 0; ++i) {
        value = value/2;
    }
    return i-1;
}

void DSW(BST tree, int nodeCount)
{
    int n = 1,
        m = log_2_function(nodeCount+1);
    for (int i = 0; i < m; ++i) {
        n = n*2;
    }
    int middle = n-1;
    leftRotation(tree, nodeCount-middle);
    while(middle > 1) {
        middle = middle/2;
        leftRotation(tree, middle);
    }
}

int main() {

    BST tree = bst_init();

    bst_insert_recursion(tree, 50, NULL);
    bst_insert_recursion(tree, 40, NULL);
    bst_insert_recursion(tree, 20, NULL);
    bst_insert_recursion(tree, 60, NULL);
    bst_insert_recursion(tree, 10, NULL);
    bst_insert_recursion(tree, 30, NULL);
    bst_insert_recursion(tree, 86, NULL);
    bst_insert_recursion(tree, 93, NULL);
    bst_insert_recursion(tree, 55, NULL);
    bst_insert_recursion(tree, 46, NULL);
    bst_insert_recursion(tree, 75, NULL);
    bst_insert_recursion(tree, 79, NULL);
    bst_insert_recursion(tree, 35, NULL);
    bst_insert_recursion(tree, 12, NULL);
    bst_insert_recursion(tree, 25, NULL);
    bst_insert_recursion(tree, 62, NULL);
    bst_insert_recursion(tree, 99, NULL);
    bst_insert_recursion(tree, 7, NULL);
    bst_insert_recursion(tree, 71, NULL);
    bst_insert_recursion(tree, 92, NULL);

    bst_reverse_in_order(tree->root, 0);
    printf("\n");
    makeBackbone(tree);
    bst_reverse_in_order(tree->root, 0);
    printf("\n");
    DSW(tree, 20);
    bst_reverse_in_order(tree->root, 0);

    free(tree);
    return 1;
}
