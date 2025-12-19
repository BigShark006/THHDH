#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

void* do_loop(void* data)
{
	int i;
	int me = (int)(intptr_t) data;
	
	for(i=0; i<5; i++)
	{
		sleep(1);
		printf(" '%d' - Got '%d' \n", me, i);
	}
	pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
	int thr_id;
	pthread_t p_thread;
	int a = 1;
	int b = 2;
	thr_id = pthread_create(&p_thread, NULL, do_loop, (void*)(intptr_t) a);
	do_loop ((void*)(intptr_t)b);
	return 0;
}
