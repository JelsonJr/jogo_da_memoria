#include <stdio.h>
#include <stdlib.h>
#include "Tabuleiro.h"

char **mapa;
int linhas, colunas;

void alocaTabuleiroNaMemoria(FILE* f) {
    fscanf(f, "%d %d", &linhas, &colunas);
    mapa = (char **)malloc(sizeof(char *) * linhas);
    for (int i = 0; i < linhas; i++)
        mapa[i] = (char *)malloc(sizeof(char) * (colunas + 1));
}

void liberaTabuleiroDaMemoria() {
    for (int i = 0; i < linhas; i++)
        free(mapa[i]);

    free(mapa);
}

void leTabuleiro(FILE* f) {
    for (int i = 0; i < linhas; i++) 
        fscanf(f, "%s", mapa[i]);
}

void imprimeTabuleiro() {
    for (int i = 0; i < linhas; i++) 
        printf("%s\n", mapa[i]);
}

void exibeTabuleiro() {
    FILE* f;
    f = fopen("tabuleiro.txt", "r+");
    
    if(f == 0) {
        printf("Erro na leitura do mapa");
        exit(1);
    }

    alocaTabuleiroNaMemoria(f);
    leTabuleiro(f);
    distribuiCartasNoTabuleiro();
    imprimeTabuleiro();

    fclose(f);
    liberaTabuleiroDaMemoria();
}

void distribuiCartasNoTabuleiro() {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) 
            if (mapa[i][j] == 'X') 
                mapa[i][j] = '*';
    }
}

int main() {
    exibeTabuleiro();
}