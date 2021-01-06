#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS	5

void* thread_main(void* threadid) {
	printf("Hello SCR! Written by thread %d\n", (int) threadid);
	return NULL;
}

int main(int argc, char* argv[]) {
	pthread_t threads[NUM_THREADS];

	for (int i=0; i < NUM_THREADS; i++) {
		int err = pthread_create(threads + i, NULL, thread_main, (void *) i);
		if (err) {
			fprintf(stderr, "%s: pthread_create returned %d\n", *argv, err);
			return -1;
		}
	}

	pthread_exit(NULL);
}
