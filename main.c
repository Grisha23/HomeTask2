#include <string.h>
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

Matrix* multiply(Matrix *matrix1, Matrix *matrix2)
{
	int M1_rows = get_rows(matrix1);
	int M1_cols = get_cols(matrix1);
	int M2_rows = get_rows(matrix2);
	int M2_cols = get_cols(matrix2);

	if (M1_cols != M2_rows) 
	{
		return NULL;
	}


	Matrix *matrix3;
	matrix3 = create_matrix(M1_rows, M2_cols);

	for(int i = 0; i < M1_rows; i++) // По строкам
	{
		for(int j = 0; j < M2_cols; j++) // По столбцам
		{
			double summ = 0.0;
			for (int k = 0; k < M1_cols; k++)
			{
				summ += get_elem(matrix1, i, k) * get_elem(matrix2, k, j);
			}
			set_elem(matrix3, i, j, summ);
			summ = 0.0;
		}
	}
	return matrix3;
}

FILE* file_open(char *file_name)
{
	FILE *file = fopen(file_name, "rt");
	if (!file)
	{
		printf("Невозможно открыть файл по адресу: %s", file_name);
		exit(0); 
	}
	else
	{
		printf("Файл открыт.");
	}
	return file;

}

void file_close(FILE *file)
{
	if (fclose(file) == 0) 
	{
		printf("Файл закрыт.\n");
	}
	else 
	{ 
		printf("error: не удалось закрыть файл!");
	}
}

void check(FILE *file)
{
	unsigned int N = 10;
	unsigned int delta=10;
	unsigned int i = 0;   
  	char* buf = (char*) malloc (sizeof(char)*N);  
  
   	while ((buf [i] = fgetc(file)) != EOF  )  
	{                
        if (++i >= N) 
		{
            N += delta;
            buf = (char*) realloc (buf, sizeof(char)*N);        
        }   
    } 

	if (i < 2)
	{
		printf("\nerror : файл пуст.");
		exit(0);
	}

	for (int j = 0; j < i; )
	{
		if(buf[j] == ',')
		{
			printf("\nУберите запятые. Разделитель - точка. Например: 1.2");
			exit(0);
		}
		if ((isspace(buf[j]))  || (ispunct(buf[j]))) j++;
			else if (buf[j] <= '9' && buf[j] >= '0') j++;
				else if (buf[j] == '-') j++;
				         else
						{
							printf("\nФайл задан некорректно. Пожалуйста, уберите лишние символы.\n");
							exit(0);
						}
	}
	fseek(file,0,SEEK_SET);
	free(buf);
} 

int main(int argc, char* argv[])
{
	//TODO

	char *file1_name = argv[1]; 
	char *file2_name = argv[2];

	FILE *file = file_open(file1_name); // Открытие файла

	check(file); // Проверка на корректность файла
	
	Matrix *matrix1;
	matrix1 = create_matrix_from_file(file);

	file_close(file); // Закрытие
	
	file = file_open(file2_name); // Открытие файла

	check(file); // Проверка на корректность файла
	
	Matrix *matrix2;
	matrix2 = create_matrix_from_file(file);

	file_close(file); // Закрытие
	
	
	Matrix *matrix3;
	matrix3 = multiply(matrix1,matrix2);
	if (!matrix3)
	{
		printf("Данные матрицы умножить нельзя");
		return 0;
	}

	int M1_row = get_rows(matrix1);
	int M2_col = get_cols(matrix2);
	
	for (int i = 0; i < M1_row; i++)
	{
		for (int j = 0;j < M2_col; j++)
		{
			printf("%f ", get_elem(matrix3, i, j));
		}
		printf("\n");
	}
	free_matrix (matrix1);
	free_matrix (matrix2);
	free_matrix (matrix3);

	
	return 0;
	
}
