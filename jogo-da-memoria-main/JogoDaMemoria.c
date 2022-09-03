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

char tabuleiro[LINHA][COLUNA], auxiliar[LINHA][COLUNA];
char cartas[NUMERO_DE_CARTAS] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

void resetaTabuleiro(){
    for(int i = 0; i<4; i++){
        for(int j = 0; j<4; j++){
            tabuleiro[i][j] = ' ';
            auxiliar[i][j] = '*';
        }
    }
}

void atribuiValorAsCartas(int *cartasLinha, int *cartasColuna) {
    srand(time(NULL));
    *cartasLinha = rand()% LINHA; *cartasColuna = rand()% COLUNA;
}

void distribuiCartasNoTabuleiro() {
    int cartasLinha, cartasColuna;
    for (int a = 0; a < NUMERO_DE_CARTAS; a++) {
        atribuiValorAsCartas(&cartasLinha, &cartasColuna);
        if(tabuleiro[cartasLinha][cartasColuna] != ' ') {
            do { 
                atribuiValorAsCartas(&cartasLinha, &cartasColuna); 
            } while(tabuleiro[cartasLinha][cartasColuna] != ' ');
        }
        tabuleiro[cartasLinha][cartasColuna] = cartas[a];
    }
}

void copiaTabuleiro(char matrizOriginal[LINHA][COLUNA], char matrizCopia[LINHA][COLUNA]) {
    int linha, coluna;
    for (linha = 0; linha < LINHA; linha++) {
        for (coluna = 0; coluna < COLUNA; coluna++)
            matrizCopia[linha][coluna] = matrizOriginal[linha][coluna];
    }
}

void desenhaTabuleiro(int viradoOuNao) {
    char tabuleiroCopia[LINHA][COLUNA];
    viradoOuNao? copiaTabuleiro(auxiliar, tabuleiroCopia) : copiaTabuleiro(tabuleiro, tabuleiroCopia);
    
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
    distribuiCartasNoTabuleiro();
    distribuiCartasNoTabuleiro();
    desenhaTabuleiro(0);
}

int ganhar(){
    for(int i = 0; i<4; i++) {
        for(int j = 0; j<4; j++)
            if(auxiliar[i][j] == '*')
                return 0;
    }
    return 1;
}

void tentativaUsuario(){
    COORDENADAS c1, c2;
    //struct coordenadas c1, c2; //c1 e c2 sao variaveis para cada empacotamento das variaveis "linha" e "coluna" do struct "coordenadas".
    desenhaTabuleiro(1);
    do{
        printf("\nInsira qual posicao deseja selecionar. - (Linha 1-4, Coluna 1-4)\n");
        fflush(stdin);
        scanf("%d %d", &c1.linha, &c1.coluna);

        c1.linha--; c1.coluna--;

        while((auxiliar[c1.linha][c1.coluna] != '*') || (c1.linha>3 || c1.linha<0 || c1.coluna>3 || c1.coluna<0)){
            system("cls");
            desenhaTabuleiro(1);
            printf("\nInsira uma posicao valida. - (Linha 1-4, Coluna 1-4)\n");
            fflush(stdin);
            scanf("%d %d", &c1.linha, &c1.coluna);

            c1.linha--; c1.coluna--;
        }
        auxiliar[c1.linha][c1.coluna] = tabuleiro[c1.linha][c1.coluna];
        desenhaTabuleiro(1);
    ////////////////////////////////////////////////////// dividir em função
        printf("\nInsira qual posicao deseja selecionar. - (Linha 1-4, Coluna 1-4)\n");
        fflush(stdin);
        scanf("%d %d", &c2.linha, &c2.coluna);

        c2.linha--; c2.coluna--;

        while((auxiliar[c2.linha][c2.coluna] != '*') || (c2.linha>3 || c2.linha<0 || c2.coluna>3 || c2.coluna<0)){
            system("cls");
            desenhaTabuleiro(1);
            printf("\nInsira uma posicao valida. - (Linha 1-4, Coluna 1-4)\n");
            fflush(stdin);
            scanf("%d %d", &c2.linha, &c2.coluna);

            c2.linha--; c2.coluna--;
        }
        auxiliar[c2.linha][c2.coluna] = tabuleiro[c2.linha][c2.coluna];
        desenhaTabuleiro(1);

        if((auxiliar[c2.linha][c2.coluna] != auxiliar[c1.linha][c1.coluna]) || (c2.linha == c1.linha && c2.coluna == c1.coluna)){ // deixar essa struct global e fazer a comparação em outra função
            printf("\nVoce errou!");
            Sleep(2000);
            auxiliar[c1.linha][c1.coluna] = '*';
            auxiliar[c2.linha][c2.coluna] = '*';
            desenhaTabuleiro(1);
        }else{
            printf("\nVoce acertou!");
            Sleep(2000);
            desenhaTabuleiro(1);
        }
    } while(!ganhar());
}

void iniciarJogo() {
    resetaTabuleiro();
    printf("Voce tera 10 segundos para memorizar o tabuleiro - (Aperte 1 para confirmar)\n");

    int virar;
    do {
        scanf("%d", &virar);
        virar == 1 ? imprimeTabuleiro() :
            printf("Voce precisa confirmar para o jogo iniciar! (Aperte 1 para confirmar)\n");
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
