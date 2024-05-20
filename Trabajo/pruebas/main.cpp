#include "/usr/include/pthread.h"
#include <iostream>

void* print_hello(void* threadid) {
    long tid;
    tid = (long)threadid;
    std::cout << "Hello World! Thread ID: " << tid << std::endl;
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[5];
    int rc;
    for (long t = 0; t < 5; t++) {
        std::cout << "In main: creating thread " << t << std::endl;
        rc = pthread_create(&threads[t], NULL, print_hello, (void*)t);
        if (rc) {
            std::cout << "Error: unable to create thread," << rc << std::endl;
            exit(-1);
        }
    }
    pthread_exit(NULL);
}