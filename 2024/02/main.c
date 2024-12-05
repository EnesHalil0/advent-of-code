#include <stdio.h>
#include <stdlib.h>

#define MAX_NUMBERS 100
#define MAX_LINES 1000
#define MAX_LINE_LENGTH 1024

int is_safe(int arr[], int arr_size);

int main(int argc, char **argv) {
  FILE *fp;
  char *file_path = argv[1];
  fp = fopen(file_path, "r");

  if (fp == NULL) {
    printf("File cannot read.\n");
    return 1;
  }

  int numbers[MAX_LINES][MAX_NUMBERS];
  int line_sizes[MAX_LINES];
  int line_count = 0;

  char buffer[MAX_LINE_LENGTH];

  while (fgets(buffer, sizeof(buffer), fp) && line_count < MAX_LINES) {
    int num, num_count = 0;
    char *ptr = buffer;

    while (sscanf(ptr, "%d", &num) == 1) {
      if (num_count >= MAX_NUMBERS) {
        printf("too many numbers in line %d.\n max is %d", line_count + 1,
               MAX_NUMBERS);
        return 1;
      }
      numbers[line_count][num_count++] = num;

      while (*ptr != '\0' && *ptr != ' ' && *ptr != '\n')
        ptr++;
      while (*ptr == ' ' || *ptr == '\n')
        ptr++;
    }

    line_sizes[line_count++] = num_count;
  }

  // PART ONE
  int safe_count = 0;
  for (int i = 0; i < line_count; i++) {
    if (is_safe(numbers[i], line_sizes[i]))
      safe_count++;
  }
  printf("PART ONE:\n%d reports are safe.\n", safe_count);

  fclose(fp);
}

int is_safe(int arr[], int arr_size) {
  int inc;
  if (arr[1] - arr[0] > 0)
    inc = 1;
  else if (arr[1] - arr[0] < 0)
    inc = 0;
  else
    return 0;

  for (int i = 0; i < arr_size - 1; i++) {
    int diff = arr[i + 1] - arr[i];

    if (diff == 0)
      return 0;
    else if (diff > 0 && inc == 0)
      return 0;
    else if (diff < 0 && inc == 1)
      return 0;
    else if (abs(diff) > 3)
      return 0;
  }
  return 1;
}
