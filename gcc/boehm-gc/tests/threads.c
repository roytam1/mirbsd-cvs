#include <stdio.h>
#include <pthread.h>
#include <gc.h>

void *countdown(void *dummy) {
	int i;

	GC_init();
	for(i = 10; i >= 0; i--) {
		printf("%d\n", i);
	}
	return dummy;
}

int main(int argc, char **argv) {
	pthread_t thread1, thread2;

	GC_init();
	pthread_create(&thread1, NULL, countdown, NULL);
	countdown(&thread2);
	return 0;
}
