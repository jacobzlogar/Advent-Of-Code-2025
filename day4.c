#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static const int DIRS[8][2] = {
  {-1,-1},{-1,0},{-1,1},{0,1},
  {1,1},{1,0},{1,-1},{0,-1}
};

int main() {
  long part_1 = 0;
  long part_2 = 0;
  int nread = 0;
  size_t size = 0;

  FILE *fp;

  fp = fopen("day4.txt", "r");
  if (fp == NULL) {
    perror("fopen");
  }

  char *buf = NULL;
  char** rows;
  char** rows_copy;
  rows = (char**)malloc(1024 * sizeof(char*));
  rows_copy = (char**)malloc(1024 * sizeof(char*));
  int height = 0;
 
  while ((nread = getline(&buf, &size, fp)) != -1) {
    rows_copy[height] = strdup(buf);
    rows[height++] = strdup(buf);
    buf = NULL;
    size = 0;
  }
  /* printf("rows[1] = %s\nrows_copy[1] = %s\n", rows[1], rows_copy[1]); */

  int width = strlen(rows[0]);
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (rows[i][j] != '@') continue;

      int count = 0;

      for (int k = 0; k < 8; k++) {
	int nx = i + DIRS[k][0]; 
	int ny = j + DIRS[k][1];
	if (nx >= 0 && nx < height &&
	    ny >= 0 && ny < width)  {
	  if (rows[nx][ny] == '@')
	    count++;
	}
      }

      if (count < 4) {
	rows_copy[i][j] = 'x';
	part_1++;
      }
    }
  }

  printf("part 1 = %d\n", part_1);

  part_2 = part_1;

  while (true) {
    int to_remove = 0;
    
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
	if (rows_copy[i][j] != '@') continue;

	int count = 0;

	for (int k = 0; k < 8; k++) {
	  int nx = i + DIRS[k][0];
	  int ny = j + DIRS[k][1];
	  if (nx >= 0 && nx < height &&
	      ny >= 0 && ny < width)  {
	    if (rows_copy[nx][ny] == '@')
	      count++;
	  }
	}

	if (count < 4) {
	  rows_copy[i][j] = 'x';
	  to_remove++;
	}
      }
    }
    if (to_remove == 0)
      break;
    part_2 += to_remove;
  }

  printf("part 2 = %d\n", part_2);

  return 0;
}
