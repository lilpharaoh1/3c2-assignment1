#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

#define STR_LENGTH 50

int main() {
    char data[STR_LENGTH] = "dguasmzerbcccddihvypkxqntfwloj";
    Tree_Node * node = create_bst(data);

    printf("------------------------------\n");
    tree_print_sorted(node);

    tree_delete(node);
    return 0;
}

