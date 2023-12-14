#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define MAX 100
#define TAMANHO 100000000
#define VALOR_PROCURADOO 55

int *gerar_vetor(int n) {
    int *vetor;
    int i;
    vetor = (int *)malloc(sizeof(int) * n);
    for (i=0;i<n;i++) {
        int num = (rand() % MAX);
        vetor[i] = num;
    }
    return vetor;
}

int main(){
    srand(time(NULL));
    int count_seq = 0, count_parallel = 0;
    int number_of_threads = 3;
    double start, end, seq_time, parallel_time;
    int* vet = gerar_vetor(TAMANHO);

    //Região sequencial
    start = omp_get_wtime();
    for(int i = 0; i<TAMANHO; i++){
        if(vet[i] == VALOR_PROCURADOO){
            count_seq += 1;
        }
    }
    end = omp_get_wtime();
    seq_time = end - start;

    //Região paralela
    start = omp_get_wtime();
    #pragma omp parallel num_threads(number_of_threads)
    {
        #pragma omp for reduction (+: count_parallel)
        for(int i = 0; i<TAMANHO; i++){
            if(vet[i] == VALOR_PROCURADOO){
                count_parallel += 1;
            }
        }
    }
    end = omp_get_wtime();
    parallel_time = end - start;

    double speedup = seq_time/parallel_time;
    double eff = speedup/number_of_threads;

    printf("Contagem sequencial:\t %d \n", count_seq);
    printf("Contagem paralela:\t %d \n", count_parallel);
    printf("Tempo sequencial:\t %.5f s\n", seq_time);
    printf("Tempo paralelo:\t\t %.5f s\n", parallel_time);
    printf("Speedup:\t\t %.5f \n", speedup);
    printf("Eficiência:\t\t %.5f \n", eff);

    return 0;
}
