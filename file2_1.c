#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* func1(void* args) {
    int* flag1 = (int*)args;
    while (*flag1 == 0) {
        for (int i = 0; i < 10; ++i) { // Вход в КУ
            printf("1");
            fflush(stdout);  
            sleep(1); 
        } // Выход из КУ
        
        // Работа вне КУ
        sleep(1); 
    }
    pthread_exit(NULL);
}

void* func2(void* args) {
    int* flag2 = (int*)args;
    while (*flag2 == 0) {
        for (int i = 0; i < 10; ++i) { // Вход в КУ
            printf("2");
            fflush(stdout); 
            sleep(1); 
        } // Выход из КУ
        
        // Работа вне КУ
        sleep(1); 
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t id1, id2;
    int flag1 = 0;
    int flag2 = 0;

    pthread_create(&id1, NULL, func1, (void*)&flag1);
    pthread_create(&id2, NULL, func2, (void*)&flag2);

    printf("Press key to stop...\n");
    getchar();

    flag1 = 1;
    flag2 = 1;

    pthread_join(id1, NULL);
    pthread_join(id2, NULL);

    return 0;
}
