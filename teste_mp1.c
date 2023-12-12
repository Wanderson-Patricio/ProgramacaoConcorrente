#include <stdio.h>
#include <omp.h>

int main(){

    #pragma omp parallel num_threads(5)
    {
        //Região Paralela
        printf("Mensagem da thread %d - ", omp_get_thread_num());
        printf("Hello World!\n");
    }

    return 0;
}