#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long solve(char*, int);

long solve(char* str, int k) {
  int n = strlen(str);
  int to_drop = n - k;
  char* stack = malloc(n + 1);
  int top = 0;

  for (int i = 0; i < n; i++) {
    char c = str[i];

    while (top > 0 && stack[top - 1] < c && to_drop > 0) {
      top--;
      to_drop--;
    }

    stack[top++] = c;
  }

  stack[k] = '\0';
  return atol(stack);
}

int main() {
  long part_1 = 0;
  long part_2 = 0;

  FILE *fp;
  char *line = NULL;
  size_t size = 0;
  ssize_t nread;

  fp = fopen("day3.txt", "r");
  if (fp == NULL) {
    perror("fopen");
  }

  while ((nread = getline(&line, &size, fp)) != -1) {
    if (line[nread - 1] == '\n') {
      line[nread - 1] = '\0';
      nread--;
    }

    part_1 += solve(line, 2);
    part_2 += solve(line, 12);
  }

  printf("part 1 = %ld part 2 = %ld", part_1, part_2);

  return 0;
}
