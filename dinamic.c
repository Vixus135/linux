#include <stdio.h>
#include <stdlib.h>

int main(){
	int N;
	printf("Введите размер массива: ");
	scanf("%d", &N);

	int *arr = (int*)malloc(N * sizeof(int));
	if (arr == NULL){
		printf("Ошибка с выдилиением памяти!\n");
		return 1;
	}
	printf("Заполнение массива:\n");
	for (int i = 0; i < N; i++){
		arr[i] = i * 10;
		printf("arr[%d] = %d, адрес = %p\n", i, arr[i], &arr[i]);
	}
	printf("\nАдрес указателя: %p\n", &arr);
	free(arr);
	return 0;
}
