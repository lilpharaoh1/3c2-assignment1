// #include "t1.h"
// #include "t2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARR_SIZE 10
#define MAX_STRING_SIZE 50
#define IGN_SIZE 20000

FILE *f;

typedef struct Game Game;

struct Game { 
    char name[MAX_STRING_SIZE];
    int score;
};

Game * gameList[IGN_SIZE];

int next_field(FILE *csv, char *buffer, int max_len);


void load_file( char * fname);


void printGameList( int size );


void clearGameList();


int partition(int l, int r);


void quickSortFunc(int l, int r);


void sort();


int main()
{
    char fname[MAX_STRING_SIZE] = "t4_ign.csv";
    load_file(fname);

    sort();

    printGameList(20);

    clearGameList();
}


int next_field(FILE *csv, char *buffer, int max_len) {
    int idx = 0;
    int c = fgetc(csv);
    int in_quotes = 0;

    while (c != EOF) {
        if (c == '"') {
            in_quotes = !in_quotes;
        }
        if (c == '\n') {
            return 1;
        }
        else if (c ==  ',' && in_quotes == 0) {
            return 0;
        }
        else if (idx < max_len) {
            buffer[idx] = c;
            buffer[idx + 1] = '\0';
            idx++;
        }
        c = fgetc(csv);
    }

    return 0;
}


void load_file ( char *fname ) {
	char buf[MAX_STRING_SIZE];
    int ret;
    int field = 0;
    int idx = 0;
    int score = 0;
    char name[MAX_STRING_SIZE];

	// boiler plate code to ensure we can open the file
	f = fopen(fname, "r");
	if (!f) { 
		printf("Unable to open %s\n", fname);
		return; 
	}
	
    do {
        ret = next_field(f, buf, MAX_STRING_SIZE);
    } while (ret != 1);

	// read until the end of the file
	do {
        ret = next_field(f, buf, MAX_STRING_SIZE);
        // printf("%s", buf);
        // printf("\n");

        if (field == 3) {
            field = -1;
            int not_in = 1;
            for (int i = idx; i > idx - 3; i--) { 
                if (i > 0) {
                    if (gameList[i] != NULL) {
                        if (strcmp(gameList[i]->name, name) == 0) {
                            not_in = 0;
                            break;
                        }
                    }
                }
            }
            if (not_in == 1) {
                Game * game = (Game *)malloc(sizeof(Game));
                strcpy(game->name, name);
                game->score = score;
                gameList[idx] = game;
                idx++;
            }
        }
        else if (field == 0) { strcpy(name, buf); }
        else if (field == 2) { score = atoi(buf); }

        field++;
    } while (feof(f) != 1);

	// always remember to close your file stream
	fclose(f);

	printf("%s loaded!\n", fname);

	return;
}


void printGameList(int size) { 
    if (size < IGN_SIZE) {
        for (int i = 0; i < size; i++) { 
            if (gameList[i] != NULL) { 
                printf("Name : %s\n", gameList[i]->name);
                printf("Score : %i\n", gameList[i]->score);
                printf("-------------------------------\n");
            }
        }
    }
}


void clearGameList() { 
    for (int i = 0; i < IGN_SIZE; i++) { 
        if (gameList[i] != NULL) { 
            free(gameList[i]);
            gameList[i] = NULL;
        }
    }
}


int partition(int l, int r) {
  int pivot = r;
  r -= 1;

  while (l != r) { 
    while (gameList[l]->score > gameList[pivot]->score && l != r) { 
      l++;
    }

    while (gameList[r]->score <= gameList[pivot]->score && l != r) { 
      r--;
    }

    Game * tmp = gameList[r];
    gameList[r] = gameList[l];
    gameList[l] = tmp;
  }

  // printf("l = %i, r = %i, pivot = %i\n", l, r, pivot);

  if (gameList[pivot]->score >= gameList[l]->score) {
    Game * tmp = gameList[pivot];
    gameList[pivot] = gameList[l];
    gameList[l] = tmp;

    pivot = l;
  }

  return pivot;
}

void quickSortFunc(int l, int r) {
  int q = 0;
  if (r > l) { 
    q = partition(l, r);
    quickSortFunc(l, q-1);
    quickSortFunc(q+1, r);
  }
}

void sort() { 
    if (gameList[0] == NULL)  {
        printf("gameList[0] == NULL \n"); 
        return;
    }

    for (int end = 0; end < IGN_SIZE - 1; end++) { 
        if (gameList[end + 1] == NULL) { 
            quickSortFunc(0, end);
            return;
        }
    }
}
