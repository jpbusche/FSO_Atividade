#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE *sudoku;
  int sudoku_number, sudoku_game[9][9];
  char sudoku_file[12];
  scanf("%d", &sudoku_number);
  sprintf(sudoku_file, "%d.txt", sudoku_number);
  sudoku = fopen(sudoku_file, "r");
  if(sudoku == NULL) {
    printf("Este arquivo nao existe!\n");
    return 0;
  }
  for(int i = 0; i < 9; ++i) {
    for(int j = 0; j < 9; ++j) {
      fscanf(sudoku, "%d", &sudoku_game[i][j]);
    }
  }
  for(int i = 0; i < 9; ++i) {
    for(int j = 0; j < 9; ++j) {
      printf("%d ", sudoku_game[i][j]);
    }
    printf("\n");
  }
  fclose(sudoku);
  return 0;
}
