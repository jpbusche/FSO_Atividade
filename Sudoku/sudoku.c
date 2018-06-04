#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

typedef struct array {
	int id_grid;
    int grid[3][3];
} Array;

int sudoku[9][9];
FILE *fsudoku;

void *check_row(){
	int i, j, k;
	bool pass = true;

	for(i = 0; i < 9 && pass; i++)
	    for(j = 0; j < 9 && pass; j++)
	        for(k = 0; k < 9 && pass; k++)
	            if((j != k) && (sudoku[i][j] == sudoku[i][k])) {
	                pass = false;
	                printf("matriz[%d][%d] == matriz[%d][%d] \n",i,j,i,k);
	            }
	            
	if(pass) {
	    printf("Nao ha nenhum numero repetido entre as linhas.\n");
	} else {
	    printf("^ Esses numeros estao se repetindo na linha! ^\n");
	}
}

void *check_column(){
	int i, j, k;
	bool pass = true;

	for(j = 0; j < 9 && pass; j++)
	    for(i = 0; i < 9 && pass; i++)
	        for(k = 0; k < 9 && pass; k++)
	            if((i != k) && (sudoku[i][j] == sudoku[k][j])) {
	                pass = false;
	                printf("matriz[%d][%d] == matriz[%d][%d] \n",i,j,k,j);
	            }

	if(pass) {
		printf("Nao ha nenhum numero repetido entre as colunas.\n");
	} else {
		printf("^ Esses numeros estao se repetindo na coluna! ^\n");
	}
}

Array divide_matriz(int init_row, int init_column, int id) {
	Array sub_matrix;

	for(int i = 0; i < 3; ++i) {
	    for(int j = 0; j < 3; ++j) {
	        sub_matrix.grid[i][j] = sudoku[i + init_row][j + init_column];
	    }
	}

	sub_matrix.id_grid = id;
	return sub_matrix;
}

void *check_grid(void *param) {
	Array *sub_matrix= (Array*)param;
	int sum = 0;

	for(int i = 0; i < 3; i++) {
	    for(int j = 0; j < 3; j++) {
	        sum += sub_matrix->grid[i][j];
	    }
	}
	if (sum == 45)
		printf("Grid %d valido, nenhum numero se repete.\n", sub_matrix->id_grid);
	else {
	    printf("Grid %d invalido, algum numero se repete.\n", sub_matrix->id_grid);
	}
}

void create_matrix() {
	int sudoku_number;
	char sudoku_file[15];
	printf("Digite o numero do sudoku: ");
	scanf("%d", &sudoku_number);
	sprintf(sudoku_file, "sudokus/%d.txt", sudoku_number);
	fsudoku = fopen(sudoku_file, "r");
	if(fsudoku == NULL) {
	    printf("Este arquivo nao existe!\n");
	    exit(1);
	}
	for(int i = 0; i < 9; ++i) {
	    for(int j = 0; j < 9; ++j) {
            fscanf(fsudoku, "%d", &sudoku[i][j]);
	    }
	}
	for(int i = 0; i < 9; ++i) {
	    for(int j = 0; j < 9; ++j) {
            printf("%d ", sudoku[i][j]);
	    }
	    printf("\n");
	}
}

int main() {
	create_matrix();
	pthread_t tcolumn, trow, tgrid[9];
	pthread_attr_t attr_c, attr_r, attr_g[9];
	Array subgrids[9];
	pthread_attr_init(&attr_c);
	pthread_attr_init(&attr_r);
	pthread_create(&tcolumn, &attr_c, check_column, NULL);
	pthread_create(&trow, &attr_r, check_row, NULL);
	pthread_join(tcolumn, NULL);
	pthread_join(trow, NULL);
	subgrids[0] = divide_matriz(0, 0, 1);
	subgrids[1] = divide_matriz(0, 3, 2);
	subgrids[2] = divide_matriz(0, 6, 3);
	subgrids[3] = divide_matriz(3, 0, 4);
	subgrids[4] = divide_matriz(3, 3, 5);
	subgrids[5] = divide_matriz(3, 6, 6);
	subgrids[6] = divide_matriz(6, 0, 7);
	subgrids[7] = divide_matriz(6, 3, 8);
	subgrids[8] = divide_matriz(6, 6, 9);
	for(int i = 0; i < 9; ++i) {
		pthread_attr_init(&attr_g[i]);
		pthread_create(&tgrid[i], &attr_g[i], check_grid, &subgrids[i]);
	}
	for(int i = 0; i < 9; ++i) {
		pthread_join(tgrid[i], NULL);
	}
	fclose(fsudoku);
	return 0;
}
