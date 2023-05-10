#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <windows.h>

void wait_four(void * args);
void wait_eight(void * args);
void kiir(char* s);
pthread_mutex_t value_mutex = PTHREAD_MUTEX_INITIALIZER;

int main()
{
    pthread_t t;
    pthread_create(&t,NULL,wait_four,NULL);
    kiir("[main] 8s calculating...\n");
    Sleep(8000);
    kiir("[main] DONE\n");
    pthread_join(t,NULL);

    pthread_create(&t,NULL,wait_eight,NULL);
    kiir("[main] 4s calculating...\n");
    Sleep(4000);
    kiir("[main] DONE\n");
    pthread_join(t,NULL);
    return 0;
}

void  wait_four(void * args)
{
    kiir("[thread] 4s calculating...\n");
    Sleep(4000);
    printf("[thread] DONE\n");
}

void wait_eight(void * args)
{
    kiir("[thread] 8s calculating...\n");
    Sleep(8000);
    printf("[thread] DONE\n");
}

void kiir(char* s)
{
    pthread_mutex_lock(&value_mutex);
    printf("%s", s);
    pthread_mutex_unlock(&value_mutex);
}
