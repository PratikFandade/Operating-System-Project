#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
int a=7;
//void *p1, *p2;
pthread_mutex_t s1,s2;

void *read();
void *write();
int main(){
	pthread_t rth,wth;
	int r1,r2;
	pthread_mutex_init(&s1,0);
	pthread_mutex_init(&s2,0);

	r1=pthread_create(&rth,NULL,read,NULL);
	r2=pthread_create(&wth,NULL,write,NULL);
	if((r1==0)&&(r2==0)){
		printf("success\n");
	}
	else{
		printf("not\n");
	}
	
	pthread_join(rth,NULL);
	pthread_join(wth,NULL);
	pthread_mutex_destroy(&s1);
	pthread_mutex_destroy(&s2);
}
	void *read(){
		printf("i am in read\n");		
		while(1)
		{
			pthread_mutex_lock(&s2);
			printf("a=%d\n",a );
			pthread_mutex_unlock(&s1);
			sleep(1);

		}
	//	pthread_exit(&p1);
	}
	void *write(){
		printf("i am in write\n");
		while(1)
		{
			pthread_mutex_lock(&s1);
			a++;
			pthread_mutex_unlock(&s2);
		}
	//	pthread_exit(&p2);
	}
