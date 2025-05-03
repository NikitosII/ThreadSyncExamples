#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <signal.h>
#include <errno.h>
#include <string.h> 

sem_t semaphore;

// Обработчик сигнала 
void sig_handler(int signo) {
    printf("\nget SIGINT; %d\n", signo);
    sem_destroy(&semaphore);
    exit(0);
}

void* func1(void* args) {
    int* flag1 = (int*)args;
    while (*flag1 == 0) {
        while (1) {
            // Попытка захватить семафор
            int result = sem_trywait(&semaphore);
            if (result == 0) {
                // Начало КУ
                for (int i = 0; i < 10; ++i) {
                    printf("1 ");
                    fflush(stdout); 
                    sleep(1); 
                }
                // Конец КУ
                sem_post(&semaphore);
                break;

            } else {
                if (*flag1 == 1) {
                    break;
                }
                if (result != 0) { // выводить сообщение с текстом ошибки, когда функция  sem_trywait() возвращает не 0 (семафор уже занят другим потоком)
                    fprintf(stderr, "sem_trywait error: %s\n", strerror(errno));
                }
                sleep(1);
            }
        }

        
        sleep(1); // Работа вне КУ
    }
    pthread_exit(NULL);
}

void* func2(void* args) {
    int* flag2 = (int*)args;
    while (*flag2 == 0) {
        while (1) {
            // Попытка захватить семафор
            int result = sem_trywait(&semaphore);
            if (result == 0) {
                // Начало КУ
                for (int i = 0; i < 10; ++i) {
                    printf("2 ");
                    fflush(stdout); 
                    sleep(1); 
                }
                // Конец КУ
                sem_post(&semaphore);
                break;

            } else {
                if (*flag2 == 1) {
                    break;
                }
                if (result != 0) {
                    fprintf(stderr, "sem_trywait error: %s\n", strerror(errno));
                }
                sleep(1);
            }
        }


        sleep(1); // Работа вне КУ
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t id1, id2;
    int flag1 = 0;
    int flag2 = 0;
    signal(SIGINT, sig_handler);

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
