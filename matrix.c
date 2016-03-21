#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

//TODO

Matrix* create_matrix_from_file(FILE* file) 
{
	Matrix *matrix;

	int row;
	int col;
	
	fscanf(file, "%d", &row);// строки
	
	fscanf(file, "%d", &col); // столбцы 

	matrix = create_matrix(row, col);
	
	for (int i = 0; i < row; i++)
	{
		for(int j = 0; j < col; j++)
		{
			if (fscanf(file, "%lf;", &matrix->elem[i][j]) == -1 )
			{
				printf("\nerror: недостающее количество элементов. \n");
				exit(0);
			} 
		}
	}
	return matrix;
}


Matrix* create_matrix(int row, int col)
{
	Matrix *matrix = malloc(sizeof(struct Matrix));

	matrix->row = row;
	matrix->col = col;
	matrix->elem = (double**) malloc(matrix->row * sizeof(double*));
	
	for (int i = 0; i < row; i++)
	{
		matrix->elem[i] = (double*) calloc(matrix->col, sizeof(double));
	}
	return matrix;

}

void free_matrix(Matrix* matrix)
{
	int row = get_rows(matrix);
	for (int i = 0; i < row; i++)
	{
		free(matrix->elem[i]);
	}
	free(matrix->elem);
	free(matrix);
}


double get_elem(Matrix* matrix, int row, int col)
{
	return matrix->elem[row][col];
}
void set_elem(Matrix* matrix, int row, int col, double val)
{
	matrix->elem[row][col] = val;
}

int get_rows(Matrix* matrix)
{
	return matrix->row;
}

int get_cols(Matrix* matrix)
{
	return matrix->col;
}


