#include <stdio.h>
#include <omp.h>

int main(){

    #pragma omp parallel num_threads(5)
    {
        #pragma omp for
        for(int i = 0; i<=10; i++){
            printf("(%d) - i = (%d) \n", omp_get_thread_num(), i);
        }
    }

    return 0;
}