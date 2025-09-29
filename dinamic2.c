#include <stdio.h>
#include <stdlib.h>

int main(){
	int rows, cols;
	printf("Введите размер массива (2 числа через пробел, строки на столбцы): ");
	scanf("%d %d", &rows, &cols);
	int **matrix = (int**)malloc(rows * sizeof(int*));
    	if (matrix == NULL) {
        	printf("Ошибка с выделением памяти!\n");
        	return 1;
    	}
    	for (int i = 0; i < rows; i++) {
        	matrix[i] = (int*)malloc(cols * sizeof(int));
        	if (matrix[i] == NULL) {
            		printf("Ошибка с выделением памяти\n", i);
            		return 1;
        	}
    	}

    	printf("\nЗаполнение матрицы:\n");
    	for (int i = 0; i < rows; i++) {
        	for (int j = 0; j < cols; j++) {
            		matrix[i][j] = i * 10 + j;
            		printf("matrix[%d][%d] = %2d, адрес = %p\n",
                   	i, j, matrix[i][j], &matrix[i][j]);
        	}
       	printf("\n");
    	}
	printf("Адрес указателя matrix: %p\n", &matrix);
	for (int i = 0; i < rows; i++) {
        	free(matrix[i]);
    	}
    	free(matrix);
    	return 0;
}
