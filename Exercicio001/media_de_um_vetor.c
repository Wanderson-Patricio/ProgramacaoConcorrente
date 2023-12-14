#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define MAX 100
#define TAMANHO 500000000

double *gerar_vetor(int n) {
    double *vetor;
    int i;
    vetor = (double *)malloc(sizeof(double) * n);
    for (i=0;i<n;i++) {
        double num = (rand() / (float)RAND_MAX);
        vetor[i] = num;
    }
    return vetor;
}

int main(){
    double soma_seq = 0, soma_parallel = 0, media_seq, media_parallel;
    int number_of_threads = 3;
    double start, end, seq_time, parallel_time;
    double* vet = gerar_vetor(TAMANHO);

    //Região sequencial
    start = omp_get_wtime();
    for(int i = 0; i<TAMANHO; i++){
        soma_seq += vet[i];
    }
    end = omp_get_wtime();
    seq_time = end - start;

    //Região paralela
    start = omp_get_wtime();
    #pragma omp parallel num_threads(number_of_threads)
    {
        #pragma omp for reduction (+:soma_parallel)
        for(int i = 0; i<TAMANHO; i++){
            soma_parallel += vet[i];
        }
    }
    end = omp_get_wtime();
    parallel_time = end - start;

    media_seq = soma_seq/TAMANHO;
    media_parallel = soma_parallel/TAMANHO;
    double speedup = seq_time/parallel_time;
    double eff = speedup/number_of_threads;

    printf("Media sequencial:\t %.5f \n", media_seq);
    printf("Media paralela:\t\t %.5f \n", media_parallel);
    printf("Tempo sequencial:\t %.5f s\n", seq_time);
    printf("Tempo paralelo:\t\t %.5f s\n", parallel_time);
    printf("Speedup:\t\t %.5f \n", speedup);
    printf("Eficiência:\t\t %.5f \n", eff);

    return 0;
}
