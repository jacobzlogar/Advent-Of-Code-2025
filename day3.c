#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  int total = 0;
  FILE *stream;
  char *line = NULL;
  size_t size = 0;
  ssize_t nread;

  stream = fopen("day3.txt", "r");
  if (stream == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  while ((nread = getline(&line, &size, stream)) != -1) {
    int a = -1;
    int b = -1;
    int c = 0;
    for (int i = 0; i < nread; ++i) {
      int x = line[i] - '0';
      if (x > a) {
        a = x;
        b = -1;
      } else if (x > b) {
        b = x;
      }
    }
    total = total + ((a * 10) + b);
  }
  printf("total = %d\n", total);

  free(line);
  fclose(stream);
  exit(EXIT_SUCCESS);
}
