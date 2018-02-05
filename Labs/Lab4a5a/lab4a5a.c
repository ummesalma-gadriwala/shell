// Umme Salma Gadriwala

#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>

#define NUM_THREADS 6

int amount = 0;
pthread_mutex_t mutex;

void *deposit (void *param);
void *withdraw (void *param);

int main(int argc, char *argv[]) {
	pthread_t tids[NUM_THREADS];
	pthread_attr_t attr;
	
	if (argc != 3) {
		fprintf(stderr, "usage: lab4a5a <deposit int> <withdraw int> \n");
		return -1;
	}
	
	if (atoi(argv[1]) < 0 || atoi(argv[2]) < 0) {
		fprintf(stderr, "Deposit and withdrawal amounts must be >= 0\n");
		return -1;
	}
	
	pthread_attr_init(&attr);
	int i;
	for (i = 0; i < 3; i++) {
		pthread_create(&tids[i], &attr, deposit, argv[1]);
	}
	printf("%s, %s, done\n", argv[1], argv[2]);
	for (i = 3; i < NUM_THREADS; i++) {
		pthread_create(&tids[i], &attr, withdraw, argv[2]);
	}
	
	for (i = 0; i < NUM_THREADS; i++) {
		pthread_join(tids[i], NULL);
	}
	
	printf("Final amount: %d\n", amount);
	return 0;
}

void *deposit(void *param) {
	//do {
		int d = atoi(param);
		//acquire();
		pthread_mutex_lock(&mutex);
		amount += d;
		pthread_mutex_unlock(&mutex);
		//release();
		printf("Deposited %d, Amount: %d\n", d, amount);
		pthread_exit(0);
	//} while (true);
}

void *withdraw(void *param) {
	//do {
		int w = atoi(param);
		//acquire();
		pthread_mutex_lock(&mutex);
		amount -= w;
		pthread_mutex_unlock(&mutex);
		//release();
		printf("Withdrew %d, Amount: %d\n", w, amount);
		pthread_exit(0);
	//} while (true);
}
