#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bstdb.h"

#define STR_LENGTH 50

int main() {
    bstdb_init();
    bstdb_add("hello there", 100);
    bstdb_add("Hello Again", 500);
    return 0;
}

