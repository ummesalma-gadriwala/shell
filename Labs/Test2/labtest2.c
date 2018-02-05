// Tasnim Noshin 400043624
// Umme Salma Gadriwala 400021431


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *doubles(void *param); /* the thread */
void *triples(void *param); /* the thread */
void *sum(void *param); /* the thread */

typedef struct {
	int vOne;
	int vTwo;
	int vResult;
} parameters;

int main(int argc, char *argv[]){

	if (argc != 5) {
		fprintf(stderr,"usage: labtest2 <integer value> <integer value> <integer value> <integer value>\n");
		/*exit(1);*/
		return -1;
	}

	if (atoi(argv[1]) >= 100 || atoi(argv[2]) >= 100 || atoi(argv[3]) >= 100 || atoi(argv[4]) >= 100) {
		fprintf(stderr,"Arguments must be less than 100\n");
		/*exit(1);*/
		return -1;
	}

	pthread_t t1; //thread 1
	pthread_t t2; //thread 2
	pthread_t t3; //thread 3
	pthread_attr_t attr; //set attributes for t1, t2 and t3

	//allocate memory in the heap
	parameters *dataOne = (parameters *) malloc (sizeof(parameters));
	dataOne->vOne = atoi(argv[1]);
	dataOne->vTwo = atoi(argv[2]);
	
	//allocate memory in the heap
	parameters *dataTwo = (parameters *) malloc (sizeof(parameters));
	dataTwo->vOne = atoi(argv[3]);
	dataTwo->vTwo = atoi(argv[4]);
	
	pthread_attr_init(&attr);  //get default attributes
	pthread_create(&t1,&attr,doubles,dataOne); //create thread1
	pthread_create(&t2,&attr,triples,dataTwo); //create thread2
	pthread_join(t1, NULL); //wait for the thread to fexit
	pthread_join(t2, NULL); //wait for the thread to exit
	
	//allocate memory in the heap
	parameters *dataThree = (parameters *) malloc (sizeof(parameters));
	dataThree->vOne = dataOne->vResult;
	dataThree->vTwo = dataTwo->vResult;
	pthread_create(&t3,&attr,sum,dataThree); //create thread2
	pthread_join(t3, NULL); //wait for the thread to fexit
	printf("Value returned by Thread3 in main: %d\n", dataThree->vResult); //return the sum
	free(dataOne);
	free(dataTwo);
	free(dataThree);
	return 0;
}

void *doubles(void *param) {
	parameters *p = param;
	int vOne = p->vOne;
	int vTwo = p->vTwo;
	p->vResult = ((vOne+vTwo)*2);
	printf("doubles returns: %d\n", p->vResult);
	pthread_exit(0);
}

void *triples(void *param) {
	parameters *p = param;
	int vOne = p->vOne;
	int vTwo = p->vTwo;
	p->vResult = ((vOne+vTwo)*3);
	printf("triples returns: %d\n", p->vResult);
	pthread_exit(0);
}

void *sum(void *param) {
	parameters *p = param;
	int vOne = p->vOne;
	int vTwo = p->vTwo;
	p->vResult = (vOne+vTwo);
	printf("sum returns: %d\n", p->vResult);
	pthread_exit(0);
}
