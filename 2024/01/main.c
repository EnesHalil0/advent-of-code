#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define SIZE 1000
/*#define SIZE 6*/

int compare(const void *a, const void *b);
void part_one(int l_arr[], int r_arr[]);
void part_two(int l_arr[], int r_arr[]);
int number_of_similar(int num, int arr[]);

int main(int argc, char **argv) {
  FILE *fp;
  char *file_path = argv[1];
  fp = fopen(file_path, "r");

  if (fp == NULL) {
    printf("File cannot read.\n");
    return 1;
  }

  int l_arr[SIZE] = {0};
  int r_arr[SIZE] = {0};

  for (int i = 0; i < SIZE; i++) {
    fscanf(fp, "%d %d", &l_arr[i], &r_arr[i]);
  }
  fclose(fp);

  part_one(l_arr, r_arr);
  part_two(l_arr, r_arr);

  return 0;
}

void part_one(int l_arr[], int r_arr[]) {
  // sorting
  qsort(l_arr, SIZE, sizeof(int), compare);
  qsort(r_arr, SIZE, sizeof(int), compare);

  // total distance
  int sum = 0;
  for (int i = 0; i < SIZE; i++) {
    sum += abs(l_arr[i] - r_arr[i]);
  }
  printf("PART ONE:\ntotal distance: %d\n", sum);
}

void part_two(int l_arr[], int r_arr[]) {
  int score = 0;

  for (int i = 0; i < SIZE; i++) {
    score += l_arr[i] * number_of_similar(l_arr[i], r_arr);
  }

  printf("PART TWO\nSimilarity Score: %d\n", score);
}

int number_of_similar(int num, int arr[]) {
  int n = 0;
  for (int i = 0; i < SIZE; i++) {
    if (num == arr[i]) {
      n++;
    }
  }
  return n;
}

int compare(const void *a, const void *b) { return (*(int *)a - *(int *)b); }
