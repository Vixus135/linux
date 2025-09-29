#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void find_stat(int arr[], int n, int *min, int *max, double *avg) {
    	*min = *max = arr[0];
    	int sum = 0;
    	for (int i = 0; i < n; i++) {
        	if (arr[i] < *min) *min = arr[i];
        	if (arr[i] > *max) *max = arr[i];
        	sum += arr[i];
    	}
    	*avg = (double)sum / n;
}

int main() {
    	srand(time(NULL));
	int n;
	printf ("Введите размер массива: ");
	scanf("%d", &n);
	int *data = (int*)malloc(n * sizeof(int));
	if (data == NULL){printf("\nОшибка с выделением памяти\n"); return 1;}
	printf("\nСлучайный массив: ");
    	for (int i = 0; i < n; i++) {
        	data[i] = rand() % 100 + 1;
        	printf("%d ", data[i]);
    	}
    	printf("\n");
    	int min, max;
    	double avg;
	void (*func)(int[], int, int*, int*, double*) = find_stat;
    	func(data, n, &min, &max, &avg);
    	printf("\nmin: %d, max: %d, avg: %.2f\n", min, max, avg);
    	free(data);
	return 0;
}
