#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int from_index;
	int to_index;
} parameters;

int sum = 0;
int size = 20;	
int array[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};

void *runner(void *param);

int main(int argc, char *argv[]){

	pthread_t t1; //thread 1
	pthread_t t2; //thread 2
	pthread_attr_t attr; //set attributes for th=1 and t2

	//allocate memory in the heap
	parameters *dataOne = (parameters *) malloc (sizeof(parameters));
	dataOne->from_index = 0;
	dataOne->to_index = (size/2)-1;
	//printf("dataoneSize: %d",(size/2)-1);
	
	parameters *dataTwo = (parameters *) malloc (sizeof(parameters));
	dataTwo->from_index = (size/2);
	dataTwo->to_index = size-1;
	
	pthread_attr_init(&attr);  //get default attributes
	pthread_create(&t1,&attr,runner,dataOne); //create thread1
	pthread_create(&t2,&attr,runner,dataTwo); //create thread2
	pthread_join(t1, NULL); //wait for the thread to fexit
	pthread_join(t2, NULL); //wait for the thread to exit
	printf("sum = %d\n", sum); //return the sum
	free(dataOne);
	free(dataTwo);
	return 0;
}

void *runner(void *param){
	parameters *p = param;
	int i;
	for (i = p->from_index; i <= p->to_index; i++)
		sum += array[i];
	pthread_exit(0);
}



