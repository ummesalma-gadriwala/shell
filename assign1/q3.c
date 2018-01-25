//Q3
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


unsigned int shared_data = 1;
pthread_mutex_t mutex;
unsigned int rc;

void *Even(void *p1);
void *Odd(void *p2);

void main(void){

	pthread_t t1; //thread 1
	pthread_t t2; //thread 2

	pthread_create(&t1,0,&Odd,0); //create thread1
	pthread_create(&t2,0,&Even,0); //create thread2

	sleep(3);

	pthread_join(t1, NULL); //wait for the thread to fexit
	pthread_join(t2, NULL); //wait for the thread to exit
	printf("%s","Finished printing numbers 1-100\n");
}

void *Odd(void *p2){
	rc = pthread_mutex_lock(&mutex);
	while(shared_data <= 100){
		if(shared_data%2 != 0){
			printf("%d\n",shared_data);
			shared_data++;
		}else{
		rc = pthread_mutex_unlock(&mutex);//release lock
		}
	}
}

void *Even(void *p1){
	pthread_mutex_lock(&mutex);
	while(shared_data <= 100){
		if(shared_data%2 == 0){
			printf("%d\n",shared_data);
			shared_data++;
		}else{
		rc = pthread_mutex_unlock(&mutex);//release lock
		}
	}
}

