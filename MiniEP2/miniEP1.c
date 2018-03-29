#include <sumMatrices.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>	
#include <unistd.h>

#define NUM_THREADS	8


int a = 0;
char *messages[NUM_THREADS];
pthread_mutex_t lock;


void jump(void* threadid){
    long taskid;

    printf("trying to jump");
	pthread_mutex_lock(&lock);

    sleep(1);
	if(a > 2){
		a = 0;
	}
	else{
		a++;
	}
    taskid = (long) threadid;
    printf("Thread %ld: %d\n", taskid, a);


    pthread_mutex_unlock(&lock);

    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    pthread_t threads[NUM_THREADS];
    long taskids[NUM_THREADS];
    int error_code, t;

    if(argv[2] != NULL){
    	argv[2] = 5
    }

    char lake [argv[2]] 

    // for (int i = 0; i < argv[2]; ++i)
    // {
    // 	if 
    // }

    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }

	pthread_mutex_lock(&lock);


	for(t = 0; t < NUM_THREADS; t++){
        taskids[t] = t;
        printf("Creating thread %d\n", t);
        error_code = pthread_create(&threads[t], NULL, (void*) jump, (void *) taskids[t]);
        if (error_code){
            printf("ERROR; return code from pthread_create() is %d\n", error_code);
            exit(-1);
        };
    };
    pthread_mutex_unlock(&lock);

	pthread_mutex_destroy(&lock);

    pthread_exit(NULL);

  return(0);
}