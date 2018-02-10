//Q3
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h> 

//
int numbersToPrint = 1;

//for locking
pthread_mutex_t mutex;



void *Even(void *p1);
void *Odd(void *p2);

void main(void){

	pthread_t t1; //thread 1
	pthread_t t2; //thread 2

	//create thread1 for odd numbers
	pthread_create(&t1,NULL,&Odd,NULL); 
	
	//create thread2 for even numbers
	pthread_create(&t2,NULL,&Even,NULL); 

	//wait for the thread to exit
	pthread_join(t1, NULL); 
	pthread_join(t2, NULL);

	
	printf("%s","Finished printing numbers 1-100\n");
	
}

void *Odd(void *p2){

	while(numbersToPrint <= 100){
		pthread_mutex_lock(&mutex);
		if(numbersToPrint % 2 != 0){
			printf("%d\n",numbersToPrint);
			numbersToPrint = numbersToPrint+1;
		}
		pthread_mutex_unlock(&mutex);//release lock
	}
}

void *Even(void *p1){
	
	while(numbersToPrint <= 100){
		pthread_mutex_lock(&mutex);
		if(numbersToPrint % 2 == 0){
			printf("%d\n",numbersToPrint);
			numbersToPrint = numbersToPrint+1;
		}
		pthread_mutex_unlock(&mutex);//release lock
	}
}
