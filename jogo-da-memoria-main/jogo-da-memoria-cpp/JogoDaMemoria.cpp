/*
    Jogo da memoria - Feito apenas ate a parte das jogadas
    do jogador, sem sistema de pontuacao ou finalizacao do jogo
        Jelson A. Rodrigues Junior
        Lucas Vinicius M. P. S. L Morais
        Otavio Luiz
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h> //para funcao Sleep();
#include "JogoDaMemoria.h"

char cartas[NUMERO_DE_CARTAS] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
TABULEIRO tabuleiro, auxiliar; 

void resetaTabuleiro(){
    for(int i = 0; i<4; i++){
        for(int j = 0; j<4; j++) {
            tabuleiro.tabuleiro[i][j] = ' ';
            auxiliar.tabuleiro[i][j] = '*';
        }
    }
}

void atribuiValorAsCartas(int *cartasLinha, int *cartasColuna) {
    srand(time(NULL));
    *cartasLinha = rand() % LINHA; *cartasColuna = rand() % COLUNA;
}

void resetaTabuleiro() {
    int cartasLinha, cartasColuna;
    for (int a = 0; a < NUMERO_DE_CARTAS; a++) {
        atribuiValorAsCartas(&cartasLinha, &cartasColuna);
        if(tabuleiro.tabuleiro[cartasLinha][cartasColuna] != ' ') {
            do { 
                atribuiValorAsCartas(&cartasLinha, &cartasColuna); 
            } while(tabuleiro.tabuleiro[cartasLinha][cartasColuna] != ' ');
        }
        tabuleiro.tabuleiro[cartasLinha][cartasColuna] = cartas[a];
    }
}

void copiaTabuleiro(char copia[LINHA][COLUNA], char original[LINHA][COLUNA]) {
	for (int i = 0; i < LINHA; i++) {
        for (int j = 0; j < COLUNA; i++)
            copia[i][j] = original[i][j]; 
    }
}

void desenhaTabuleiro(int viradoOuNao) {
    char tabuleiroCopia[LINHA][COLUNA];
    viradoOuNao? copiaTabuleiro(auxiliar.tabuleiro, tabuleiroCopia) : copiaTabuleiro(tabuleiro.tabuleiro, tabuleiroCopia);
    
    system("cls");
    printf(" %c | %c | %c | %c \n", tabuleiroCopia[0][0], tabuleiroCopia[0][1], tabuleiroCopia[0][2], tabuleiroCopia[0][3]);
    printf("---------------\n");
    printf(" %c | %c | %c | %c \n", tabuleiroCopia[1][0], tabuleiroCopia[1][1], tabuleiroCopia[1][2], tabuleiroCopia[1][3]);
    printf("---------------\n");
    printf(" %c | %c | %c | %c \n", tabuleiroCopia[2][0], tabuleiroCopia[2][1], tabuleiroCopia[2][2], tabuleiroCopia[2][3]);
    printf("---------------\n");
    printf(" %c | %c | %c | %c \n", tabuleiroCopia[3][0], tabuleiroCopia[3][1], tabuleiroCopia[3][2], tabuleiroCopia[3][3]);
}

void imprimeTabuleiro() {
    resetaTabuleiro();
    resetaTabuleiro();
    desenhaTabuleiro(0);
}

int ganhar(){
    for(int i = 0; i<4; i++) {
        for(int j = 0; j<4; j++)
            if(auxiliar.tabuleiro[i][j] == '*')
                return 0;
    }
    return 1;
}

int posicaoNaoEhValida(TABULEIRO *t) {
    if(auxiliar.tabuleiro[t->linha][t->coluna] != '*' || (t->linha>3 || t->linha<0 || t->coluna>3 || t->coluna<0))
        return 1;

    return 0;
}

void tentativaUsuario(){
    desenhaTabuleiro(1);
    do{
        printf("\nInsira qual posicao deseja selecionar. - (Linha 1-4, Coluna 1-4)\n");
        fflush(stdin);
        scanf("%d %d", &tabuleiro.linha, &tabuleiro.coluna);

        tabuleiro.linha--; tabuleiro.coluna--;

        while(posicaoNaoEhValida(&tabuleiro)){
            system("cls");
            desenhaTabuleiro(1);
            printf("\nInsira uma posicao valida. - (Linha 1-4, Coluna 1-4)\n");
            fflush(stdin);
            scanf("%d %d", &tabuleiro.linha, &tabuleiro.coluna);

            tabuleiro.linha--; tabuleiro.coluna--;
        }
        auxiliar.tabuleiro[tabuleiro.linha][tabuleiro.coluna] = tabuleiro.tabuleiro[tabuleiro.linha][tabuleiro.coluna];
        desenhaTabuleiro(1);

        printf("\nInsira qual posicao deseja selecionar. - (Linha 1-4, Coluna 1-4)\n");
        fflush(stdin);
        scanf("%d %d", &auxiliar.linha, &auxiliar.coluna);

        auxiliar.linha--; auxiliar.coluna--;

        while(posicaoNaoEhValida(&auxiliar)){
            system("cls");
            desenhaTabuleiro(1);
            printf("\nInsira uma posicao valida. - (Linha 1-4, Coluna 1-4)\n");
            fflush(stdin);
            scanf("%d %d", &auxiliar.linha, &auxiliar.coluna);

            auxiliar.linha--; auxiliar.coluna--;
        }
        auxiliar.tabuleiro[auxiliar.linha][auxiliar.coluna] = tabuleiro.tabuleiro[auxiliar.linha][auxiliar.coluna];
        desenhaTabuleiro(1);

        acertouOuErrou();
    } while(!ganhar());
}

void acertouOuErrou() {
    if((auxiliar.tabuleiro[auxiliar.linha][auxiliar.coluna] != auxiliar.tabuleiro[tabuleiro.linha][tabuleiro.coluna]) || (auxiliar.linha == tabuleiro.linha && auxiliar.coluna == tabuleiro.coluna)){ // deixar essa struct global e fazer a comparação em outra função
        printf("\nVoce errou!");
        Sleep(2000);
        auxiliar.tabuleiro[tabuleiro.linha][tabuleiro.coluna] = '*';
        auxiliar.tabuleiro[auxiliar.linha][auxiliar.coluna] = '*';
        desenhaTabuleiro(1);
    } else{
        printf("\nVoce acertou!");
        Sleep(2000);
        desenhaTabuleiro(1);
    }
}

void iniciarJogo() {
    resetaTabuleiro();
    printf("Voce tera 10 segundos para memorizar o tabuleiro - (Aperte 1 para confirmar)\n");

    int virar;
    do {
        
        scanf("%d", &virar);
        if(virar ==1) imprimeTabuleiro();
        else printf("Voce precisa confirmar para o jogo iniciar! (Aperte 1 para confirmar)\n");

    } while(virar != 1);
    printf("\nMemorize!\n");
    Sleep(10000); //Usuario tem 10 segundos para memorizar o tabuleiro
}

int main(){
    iniciarJogo();
    desenhaTabuleiro(0);
    tentativaUsuario();
    return 0;
}
