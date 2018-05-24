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

//funcao generica apenas para poder testar a check_grid
int divide_matriz(int matriz[9][9], int submatriz[3][3], int i_init, int j_init) {
      submatriz[0][0] = matriz[i_init][j_init];
      submatriz[0][1] = matriz[i_init][j_init+1];
      submatriz[0][2] = matriz[i_init][j_init+2];
      submatriz[1][0] = matriz[i_init+1][j_init];
      submatriz[1][1] = matriz[i_init+1][j_init+1];
      submatriz[1][2] = matriz[i_init+1][j_init+2];
      submatriz[2][0] = matriz[i_init+2][j_init];
      submatriz[2][1] = matriz[i_init+2][j_init+1];
      submatriz[2][2] = matriz[i_init+2][j_init+2];
}

bool check_grid(int subgrid[3][3], int id_grid) {
  int i, j, k, exist = 0;
  bool pass = true;

  for(k = 0; k < 9 && pass; k++) {
    for(i = 0; i < 3 && pass; i++) 
      for(j = 0; j < 3 && pass; j++)
        if(subgrid[i][j] == k) exist++;
              if(exist > 1) pass = false;
                  exist = 0;
  }
  if(pass == true)
  printf("Grid %d valido, nenhum numero se repete.\n", id_grid);
    return pass;
}

int main() {
  FILE *sudoku;
  int subgrid_1[3][3], subgrid_2[3][3], subgrid_3[3][3], subgrid_4[3][3],
      subgrid_5[3][3], subgrid_6[3][3], subgrid_7[3][3], subgrid_8[3][3], subgrid_9[3][3];
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
  divide_matriz(sudoku_game, subgrid_1, 0, 0);
  divide_matriz(sudoku_game, subgrid_2, 0, 3);
  divide_matriz(sudoku_game, subgrid_3, 0, 6);
  divide_matriz(sudoku_game, subgrid_4, 3, 0);
  divide_matriz(sudoku_game, subgrid_5, 3, 3);
  divide_matriz(sudoku_game, subgrid_6, 3, 6);
  divide_matriz(sudoku_game, subgrid_7, 6, 0);
  divide_matriz(sudoku_game, subgrid_8, 6, 3);
  divide_matriz(sudoku_game, subgrid_9, 6, 6);
  check_grid(subgrid_1, 1);
  check_grid(subgrid_2, 2);
  check_grid(subgrid_3, 3);
  check_grid(subgrid_4, 4);
  check_grid(subgrid_5, 5);
  check_grid(subgrid_6, 6);
  check_grid(subgrid_7, 7);
  check_grid(subgrid_8, 8);
  check_grid(subgrid_9, 9);
  
  fclose(sudoku);
  return 0;
}
