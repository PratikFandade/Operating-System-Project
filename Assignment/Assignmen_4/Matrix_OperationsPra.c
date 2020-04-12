#include<stdio.h>
#include<pthread.h>

int mat1[100][100];
int mat2[100][100];
int trans[100][100];
int rows, cols;

void *stat();


void *transpose()
{
  int i,j;
  for(i=0; i<rows; i++)
  {
           for(j=0; j<cols; j++)
    {
      trans[i][j]=mat1[j][i];
    }
  }
  
  printf("Transpose of matrix 1 is \n");
  
  for(i=0; i<rows; i++)
  {
           for(j=0; j<cols; j++)
    {
      printf("%d\t",trans[i][j]);
    }
    printf("\n");
  }
  pthread_exit(&stat);
}


void *add(){
  int i,j;
  for(i=0;i<rows;i++)
  {
      for(j=0; j<cols; j++)
          printf("%d ",mat1[i][j]+mat2[i][j]);
      printf("\n");
  }
  pthread_exit(&stat);
}

void *sub(){
    int i,j;
    for(i=0; i<rows; i++)
    {
        for(j=0; j<cols; j++)
            printf("%d ",mat1[i][j]-mat2[i][j]);
        printf("\n");
    }
    pthread_exit(&stat);
}


int main()
{
    int i, j;
    printf("Enter total Rows: ");
    scanf("%d",&rows); 
    printf("Enter total Columns: ");
    scanf("%d",&cols);
    
    printf("\nEnter Matrix 1 (%d X %d):",rows,cols);
    for(i=0; i<rows; i++)
    {
        for(j=0; j<cols; j++)
        {
            scanf("%d", &mat1[i][j]);
        }
    }

    printf("\nEnter Matrix 2 (%d X %d):",rows,cols);
    for(i=0; i<rows; i++)
    {
        for(j=0; j<cols; j++)
        {
            scanf("%d", &mat2[i][j]);
        }
    }

    pthread_t thread1, thread2 , thread3;
    int ret1, ret2,ret3;

    ret1 = pthread_create(&thread1,NULL,add,NULL);
    if(ret1 == 0)
      printf("Thread 1 is created successfully!\n");
    else
      printf("Thread 1 is not created!");
    pthread_join(thread1,NULL);

    ret2 = pthread_create(&thread2,NULL,sub,NULL);
    if(ret2 == 0)
      printf("Thread 2 is created successfully!\n");
    else
      printf("Thread 2 is not created!");
    pthread_join(thread2,NULL);


    ret3 = pthread_create(&thread3,NULL,transpose,NULL);
    if(ret3 == 0)
      printf("Thread 3 is created successfully!\n");
    else
      printf("Thread 3 is not created!");
    pthread_join(thread3,NULL);
}
