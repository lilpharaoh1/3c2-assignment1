#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

#define STR_LENGTH 50

int main() {
    char data[STR_LENGTH] = "dguasmzerbcihvypkxqntfwloj";
    Tree_Node * node = create_bst(data);

    tree_print_sorted(node);
    printf("\n");

    tree_delete(node);
    return 0;
}

