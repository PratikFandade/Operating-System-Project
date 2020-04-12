#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

int a=5;
//void *p1,*p2;
sem_t s1,s2;

void *read();
void *write();

int main()
{
	pthread_t rth,wth;
	int r1,r2;
	sem_init(&s1,0,0);
	sem_init(&s2,0,1);
	r1 = pthread_create(&rth,NULL,read,NULL);
	r2 = pthread_create(&wth,NULL,write,NULL);
	if(r1==0 && r2 ==0)
		printf("Success\n");
	else
		printf("Fail\n");
	pthread_join(rth,NULL);//or p1
	pthread_join(wth,NULL);// or p2
	sem_destroy(&s1);
	sem_destroy(&s2);
} 

void *read()
{
	printf("I am in read\n");
	while(1)
	{
		sem_wait(&s2);
		printf("a=%d\n",a );
		sem_post(&s1);
		sleep(1);
	}
	//pthread_exit(&p1);
}

void *write()
{
	printf("I am in write\n");
	while(1)
	{
		sem_wait(&s1);
		a++;
		sem_post(&s2);
	}
	//pthread_exit(&p2);
}