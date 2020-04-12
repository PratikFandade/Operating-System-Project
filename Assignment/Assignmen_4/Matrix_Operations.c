#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 10
#define M 3
#define K 2
#define N 3

int A [M][K];
int B [K][N];
int C [M][N];

struct v {
   int i; /* row */
   int j; /* column */
};

void *thread1(void *param); /* the thread */

int main(int argc, char *argv[]) {
	printf("**************************MATRIX OPERATIONS******************************\n");
	printf("Enter the array elements of 1st array:\n");
	for (int i = 0; i < M; ++i)
	{
		for (int j = 0; j < K; ++j)
		{
			scanf("%d ",&A[i][j]);
		}
	}
	printf("Enter the array elements of 2nd array:\n");
	for (int i = 0; i < K; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			scanf("%d ",&B[i][j]);
		}
	}
	printf("\nOriginal Matrices:\n\n");
	for (int i = 0; i < M; ++i)
	{
		for (int j = 0; j < K; ++j)
		{
			printf("%d ",A[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for (int i = 0; i < K; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			printf("%d ",B[i][j]);
		}
		printf("\n");
	}
	printf("\nMatrix Multiplication:\n");

   int count = 0;
   for(int i = 0; i < M; i++) {
      for(int j = 0; j < N; j++) {*data = (struct v *) malloc(sizeof(struct v));
         data->i = i;
         data->j = j;
         /* Now create the thread passing it data as a parameter */
         pthread_t tid;       //Thread ID
         pthread_attr_t attr; //Set of thread attributes
         //Get the default attributes
         pthread_attr_init(&attr);
         //Create the thread
         pthread_create(&tid,&attr,thread1,data);
         //Make sure the parent waits for all thread to complete
         pthread_join(tid, NULL);
         count++;
      }
   }
   for(int i = 0; i < M; i++) {
      for(int j = 0; j < N; j++) {
         printf("%d ", C[i][j]);
      }
      printf("\n");
   }
}

//The thread will begin control in this function
void *thread1(void *param) {
   struct v *data = param; // the structure that holds our data
   int n, sum = 0; //the counter and sum
   for(n = 0; n < K; n++){
      sum += A[data->i][n] * B[n][data->j];
   }
   C[data->i][data->j] = sum;
   pthread_exit(0);
}