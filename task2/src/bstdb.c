#include "bstdb.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Write your submission in this file
//
// A main function and some profiling tools have already been set up to test
// your code in the task2.c file. All you need to do is fill out this file
// with an appropriate Binary Search Tree implementation.
//
// The input data will be books. A book is comprised of a title and a word
// count. You should store both these values in the tree along with a unique
// integer ID which you will generate.
//
// We are aiming for speed here. A BST based database should be orders of
// magnitude faster than a linked list implementation if the BST is written
// correctly.
//
// We have provided an example implementation of what a linked list based
// solution to this problem might look like in the db/listdb.c file. If you
// are struggling to understand the problem or what one of the functions
// below ought to do, consider looking at that file to see if it helps your
// understanding.
//
// There are 6 functions you need to look at. Each is provided with a comment
// which explains how it should behave. The functions are:
//
//  + bstdb_init
//  + bstdb_add
//  + bstdb_get_word_count
//  + bstdb_get_name
//  + bstdb_stat
//  + bstdb_quit
//
// Do not rename these functions or change their arguments/return types.
// Otherwise the profiler will not be able to find them. If you think you
// need more functionality than what is provided by these 6 functions, you
// may write additional functions in this file.

#define STR_MAX_LEN 250
#define INT_RANGE 2147483647
#define MAX_TREE_SIZE 120000

typedef struct Node Node;
struct Node {
	int id; 
	char name[STR_MAX_LEN];
	int word_count;
	struct Node * right;
	struct Node * left;
};

Node * root;
int root_initialised = 0;

int hash_function(char* s){
    int hash = 0;
    while(*s){
        hash = hash + *s;
        s++;
    }
    return (hash % INT_RANGE);
}

void print_tree(Node * node) { 
	if (node != NULL && root_initialised) {
        if (node->left != NULL) print_tree(node->left);
		printf("%i : %s\n", node->id, node->name);
        if (node->right != NULL) print_tree(node->right);
	}
}

void delete_tree(Node * node) { 
	if (node != NULL) { 
        if (node->right != NULL) delete_tree(node->right);
        if (node->left != NULL) delete_tree(node->left);
        free(node);
    }
}

Node* tree_search(Node* node, int id){
    if (node != NULL) { 
        if (node->id == id) { 
            return node;
        } 
        else if (node->id < id) {
            if (node->right != NULL) return tree_search(node->right, id);
            else return NULL;
        }
        else if (node->id > id) {
            if (node->left != NULL) return tree_search(node->left, id);
            else return NULL;
        }
    }
    return NULL;
}

int
bstdb_init ( void ) {
	// This function will run once (and only once) when the database first
	// starts. Use it to allocate any memory you want to use or initialize 
	// some globals if you need to. Function should return 1 if initialization
	// was successful and 0 if something went wrong.

	root = (Node *)malloc(sizeof(Node));
	
	return 1;
}

void tree_insert(Node** parent_node, int id, char * name, int word_count){
    if ((*parent_node) != NULL) {
        if ((*parent_node)->id > id) {
            tree_insert(&((*parent_node)->left), id, name, word_count);
        }
        else { 
            tree_insert(&((*parent_node)->right), id, name, word_count);
        }
    }
    else {
        (*parent_node) = (Node *)malloc(sizeof(Node));
		strcpy((*parent_node)->name, name);
        (*parent_node)->id = id;
		(*parent_node)->word_count = word_count;
		(*parent_node)->right = NULL;
		(*parent_node)->left = NULL;
    }
}

int
bstdb_add ( char *name, int word_count ) {
	// This function should create a new node in the binary search tree, 
	// populate it with the name and word_count of the arguments and store
	// the result in the tree.
	//
	// This function should also generate and return an identifier that is
	// unique to this document. A user can find the stored data by passing
	// this ID to one of the two search functions below.
	//
	// How you generate this ID is up to you, but it must be an integer. Note
	// that this ID should also form the keys of the nodes in your BST, so
	// try to generate them in a way that will result in a balanced tree.
	//
	// If something goes wrong and the data cannot be stored, this function
	// should return -1. Otherwise it should return the ID of the new node
	if (root_initialised) {
		tree_insert(&(root), hash_function(name), name, word_count);
	}
	else {
		root->id = hash_function(name);
		strcpy(root->name, name);
		root->word_count = word_count;
		root_initialised = 1;
	}
	return hash_function(name);
}

int
bstdb_get_word_count ( int doc_id ) {
	// This is a search function. It should traverse the binary search tree
	// and return the word_count of the node with the corresponding doc_id.
	//
	// If the required node is not found, this function should return -1
	Node * node = tree_search(root, doc_id);

	if (node != NULL) return node->word_count;

	return -1;
}

char*
bstdb_get_name ( int doc_id ) {
	// This is a search function. It should traverse the binary search tree
	// and return the name of the node with the corresponding doc_id.
	//
	// If the required node is not found, this function should return NULL or 0
	Node * node = tree_search(root, doc_id);

	if (node != NULL) return node->name;
	
	return 0;
}

void
bstdb_stat ( void ) {
	// Use this function to show off! It will be called once after the 
	// profiler ends. The profiler checks for execution time and simple errors,
	// but you should use this function to demonstrate your own innovation.
	//
	// Suggestions for things you might want to demonstrate are given below,
	// but in general what you choose to show here is up to you. This function
	// counts for marks so make sure it does something interesting or useful.
	//
	//  + Check if your tree is balanced and print the result
	//
	//  + Does the number of nodes in the tree match the number you expect
	//    bs ased on the number of insertionyou performed?
	//
	//  + How many nodes on average did you need to traverse in order to find
	//    a search result? 
	//
	//  + Can you prove that there are no accidental duplicate document IDs
	//    in the tree?

	// print_tree(root);
}

void
bstdb_quit ( void ) {
	// This function will run once (and only once) when the program ends. Use
	// it to free any memory you allocated in the course of operating the
	// database.
	delete_tree(root);
}
