#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct array {
        int subgrid[3][3];
} Array;

bool check_row(int matrix[9][9]){
        int i, j, k;
        bool pass = true;

        for(i = 0; i < 9 && pass; i++)
                for(j = 0; j < 9 && pass; j++)
                        for(k = 0; k < 9 && pass; k++)
                                if((j != k) && (matrix[i][j] == matrix[i][k])) {
                                        pass = false;
                                        printf("matriz[%d][%d] == matriz[%d][%d] \n",i,j,i,k);
                                }
        return pass;
}

bool check_column(int matrix[9][9]){
        int i, j, k;
        bool pass = true;

        for(j = 0; j < 9 && pass; j++)
                for(i = 0; i < 9 && pass; i++)
                        for(k = 0; k < 9 && pass; k++)
                                if((i != k) && (matrix[i][j] == matrix[k][j])) {
                                        pass = false;
                                        printf("matriz[%d][%d] == matriz[%d][%d] \n",i,j,k,j);
                                }
        return pass;
}

Array divide_matriz(int matrix[9][9], int init_row, int init_column) {
        Array sub_matrix;

        for(int i = 0; i < 3; ++i) {
                for(int j = 0; j < 3; ++j) {
                        sub_matrix.subgrid[i][j] = matrix[i + init_row][j + init_column];
                }
        }
        return sub_matrix;
}

void check_grid(Array sub_matrix, int id_grid) {
        int sum = 0;

        for(int i = 0; i < 3; i++) {
                for(int j = 0; j < 3; j++) {
                        sum += sub_matrix.subgrid[i][j];
                }
        }
        if (sum == 45)
                printf("Grid %d valido, nenhum numero se repete.\n", id_grid);
        else {
                printf("Grid %d invalido, algum numero se repete.\n", id_grid);
        }
}

int main() {
        FILE *sudoku;
        Array subgrid_1, subgrid_2, subgrid_3, subgrid_4, subgrid_5,
              subgrid_6, subgrid_7, subgrid_8, subgrid_9;

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
        if(check_row(sudoku_game)) {
                printf("Nao ha nenhum numero repetido entre as linhas.\n");
        } else {
                printf("^ Esses numeros estao se repetindo na linha! ^\n");
        }
        if(check_column(sudoku_game)) {
                printf("Nao ha nenhum numero repetido entre as colunas.\n");
        } else {
                printf("^ Esses numeros estao se repetindo na coluna! ^\n");
        }
        subgrid_1 = divide_matriz(sudoku_game, 0, 0);
        subgrid_2 = divide_matriz(sudoku_game, 0, 3);
        subgrid_3 = divide_matriz(sudoku_game, 0, 6);
        subgrid_4 = divide_matriz(sudoku_game, 3, 0);
        subgrid_5 = divide_matriz(sudoku_game, 3, 3);
        subgrid_6 = divide_matriz(sudoku_game, 3, 6);
        subgrid_7 = divide_matriz(sudoku_game, 6, 0);
        subgrid_8 = divide_matriz(sudoku_game, 6, 3);
        subgrid_9 = divide_matriz(sudoku_game, 6, 6);
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
