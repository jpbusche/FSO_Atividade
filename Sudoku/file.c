#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool check_row(int matriz[9][9]){
    int i, j, k;
    bool pass = true;

    for(i = 0; i < 9 && pass; i++)
        for(j = 0; j < 9 && pass; j++)
            for(k = 0; k < 9 && pass; k++)
                if((j != k) && (matriz[i][j] == matriz[i][k])){
                    pass = false;
                    printf("matriz[%d][%d] == matriz[%d][%d] \n",i,j,i,k);
                }
    return pass;
}

bool check_column(int matriz[9][9]){
    int i, j, k;
    bool pass = true;

    for(j = 0; j < 9 && pass; j++)
        for(i = 0; i < 9 && pass; i++)
            for(k = 0; k < 9 && pass; k++)
                if((i != k) && (matriz[i][j] == matriz[k][j])) {
                    pass = false;
                    printf("matriz[%d][%d] == matriz[%d][%d] \n",i,j,k,j);
                }
    return pass;
}

int main() {
  FILE *sudoku;
  int sudoku_number, sudoku_game[9][9];
  char sudoku_file[15];
  printf("Digite o numero do sudoku: ");
  scanf("%d", &sudoku_number);
  sprintf(sudoku_file, "sudokus/%d.txt", sudoku_number);
  printf("%s\n", sudoku_file);
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
  if(check_row(sudoku_game)){
    printf("Nao ha nenhum numero repetido entre as linhas.\n");
  } else {
    printf("^ Esses numeros estao se repetindo na linha! ^\n");
  }
  if(check_column(sudoku_game)){
    printf("Nao ha nenhum numero repetido entre as colunas.\n");
  } else {
    printf("^ Esses numeros estao se repetindo na coluna!\n");
  }
  fclose(sudoku);
  return 0;
}
