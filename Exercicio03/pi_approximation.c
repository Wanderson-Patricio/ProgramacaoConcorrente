#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

int main(){
    int number_of_threads = 1;
    int N = 1000000000;
    double x, deltaX, sum = 0.0, pi_serial, pi_parallel;

    deltaX = 1.0/(double) N;
    double start, end;

    //Região Sequencial
    start = omp_get_wtime();
    for(int i=0; i<N; i++){
        x = (i+0.5)*deltaX;
        sum += (4.0/(1.0+x*x));
    }
    end = omp_get_wtime();
    pi_serial = sum * deltaX;
    double serial_time = end - start;

    sum = 0.0;

    start = omp_get_wtime();
    #pragma omp parallel num_threads(number_of_threads) private(x) 
    {
        #pragma omp for reduction(+: sum)
        for(int i=0; i<N; i++){
            x = (i+0.5)*deltaX;
            sum += 4.0/(1.0+x*x);
        }
    }
    end = omp_get_wtime();
    pi_parallel = sum * deltaX;
    double parallel_time = end - start;

    double speedup = serial_time/parallel_time;
    double efficiency = speedup/number_of_threads;

    printf("pi serial \t= %.15f \n", pi_serial);
    printf("pi parallel \t= %.15f \n", pi_parallel);
    printf("serial time \t= %.5f s\n", serial_time);
    printf("parallel time   = %.5f s\n", parallel_time);
    printf("Speedup \t= %.5f \n", speedup);
    printf("Efficiency \t= %.5f \n", efficiency);

    return 0;
}
