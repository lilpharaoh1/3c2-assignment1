#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"


void tree_insert(Tree_Node** root, char data){

    if ((*root) != NULL) { 
        if ((int) data < (int) (*root)->data) {
            tree_insert(&((*root)->left), data);
        }
        else { 
            tree_insert(&((*root)->right), data);
        }
    }
    else {
        (*root) = (Tree_Node *)malloc(sizeof(Tree_Node *));
        (*root)->data = data;
    }
    }

Tree_Node* create_bst (char data[]) {
    Tree_Node * head = (Tree_Node *)malloc(sizeof(Tree_Node *));
    head->data = data[0];

    for (int i = 1; i < strlen(data); i++) { 
        tree_insert(&head, data[i]);
    }
    
    return head;
}

Tree_Node* tree_search(Tree_Node* root, char data){
    if (root != NULL) { 
        if ((int) root->data == (int)data) { 
            return root;
        } 
        else if ((int) root->data < (int) data) {
            if (root->right != NULL) return tree_search(root->right, data);
            else return NULL;
        }
        else if ((int) root->data > (int) data) {
            if (root->left != NULL) return tree_search(root->left, data);
            else return NULL;
        }
    }
    return NULL;
}

void tree_print_sorted(Tree_Node* root){
    if (root != NULL) {
        if (root->left != NULL) tree_print_sorted(root->left);
        printf("%c \n", root->data);
        if (root->right != NULL) tree_print_sorted(root->right);
    }
}

void tree_delete(Tree_Node* root){
    if (root != NULL) { 
        if (root->right != NULL) tree_delete(root->right);
        if (root->left != NULL) tree_delete(root->left);
        free(root);
    }
}