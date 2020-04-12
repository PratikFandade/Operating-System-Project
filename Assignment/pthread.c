#include <stdio.h>
#include <pthread.h>
void *test();
void *stat;
int main()
{
	pthread_t th;
	int ret;
	ret = pthread_create(&th,NULL,test,NULL);
	if(ret == 0)
		printf("Returned Successfully\n");
	else
		printf("Not Returned\n");
	printf("I am in main\n");
	pthread_join(th,stat);
}

void *test()
{
	printf("I am in thread\n");
	pthread_exit(&stat);
}