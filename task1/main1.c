#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bstdb.h"

#define STR_LENGTH 50

int main() {
    bstdb_init();
    bstdb_add("hello there", 100);
    bstdb_add("Hello Again", 500);
    bstdb_add("Hello there", 10000);
    bstdb_add("Helllllo", 600);
    bstdb_add("Hello Mr", 570);
    if (bstdb_get_name(1100) != 0) printf("Yes!\n");
    else printf("No!\n");
    return 0;
}

