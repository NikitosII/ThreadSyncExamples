#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

sem_t semaphore;

void* func1(void* args) {
    int* flag1 = (int*)args;
    while (*flag1 == 0) {
        sem_wait(&semaphore);
        for (int i = 0; i < 10; ++i) { // Вход в КУ
            printf("1");
            fflush(stdout); /
            sleep(1); 
        } // Выход из КУ

        
        sem_post(&semaphore);
        sleep(1); // Работа вне КУ
    }
    pthread_exit(NULL);
}

void* func2(void* args) {
    int* flag2 = (int*)args;
    while (*flag2 == 0) {
        sem_wait(&semaphore);
        for (int i = 0; i < 10; ++i) { // Вход в КУ
            printf("2");
            fflush(stdout); 
            sleep(1); 
        } // Выход из КУ

        
        sem_post(&semaphore);
        sleep(1); // Работа вне КУ
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t id1, id2;
    int flag1 = 0;
    int flag2 = 0;

    // Инициализация семафора с начальным значением 1
    sem_init(&semaphore, 0, 1);

    pthread_create(&id1, NULL, func1, (void*)&flag1);
    pthread_create(&id2, NULL, func2, (void*)&flag2);

    printf("Press key to stop...\n");
    getchar();
    flag1 = 1;
    flag2 = 1;

    pthread_join(id1, NULL);
    pthread_join(id2, NULL);

    sem_destroy(&semaphore);

    return 0;
}
