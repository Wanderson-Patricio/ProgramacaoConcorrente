#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define MAX 100
#define TAMANHO 1000000000

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

int *gerar_vetor_inteiro(int n) {
    int *vetor;
    int i;
    vetor = (int *)malloc(sizeof(int) * n);
    for (i=0;i<n;i++) {
        int num = (rand() % MAX);
        vetor[i] = num;
    }
    return vetor;
}

void mostrar_vetor(double *v,int tamanho) {
    int i;
    for (i=0;i<tamanho;i++) {
        printf("[%.5f]",v[i]);
    }
    printf("\n");
}

void mostrar_vetor_inteiro(int *v,int tamanho) {
    int i;
    for (i=0;i<tamanho;i++) {
        printf("[%d] \n",v[i]);
    }
    printf("\n");
}

int main() {
    double start, end;
    int valor_procurado = 1004;
    srand(time(NULL));
    int *vetor = gerar_vetor_inteiro(TAMANHO);

    start = omp_get_wtime();
    #pragma omp parallel num_threads(3)
    {
        #pragma omp for
        for(int i=0; i<TAMANHO; i++){
            if(vetor[i] == valor_procurado){
                //printf("Valor encontrado na posição (%d) pela thread (%d) \n", i, omp_get_thread_num());
            }
        }
    }
    end = omp_get_wtime();
    printf("\nO tempo total foi de %.6f s\n", end-start);
    
    return 0;
}