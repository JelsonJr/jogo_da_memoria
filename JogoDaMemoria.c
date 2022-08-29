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
#include <windows.h> //para funcao Sleep();
#include "JogoDaMemoria.h"

char tabuleiro[M][M];
char auxiliar[M][M];
char cartas[NUMERO_DE_CARTAS] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

void resetaTabuleiro(){
    for(int i = 0; i<4; i++){
        for(int j = 0; j<4; j++){
            tabuleiro[i][j] = ' ';
            auxiliar[i][j] = '*';
        }
    }
}

void imprimeTabuleiro(){
    int i, j;
    srand(time(NULL));
    for(int a = 0; a<NUMERO_DE_CARTAS; a++){

        i = rand()% M;
        j = rand()% M;

        if(tabuleiro[i][j] != ' '){
            do{
                i = rand()% M;
                j = rand()% M;

            }while(tabuleiro[i][j] != ' ');
        }
        tabuleiro[i][j] = cartas[a];

        i = rand()% M;
        j = rand()% M;

        if(tabuleiro[i][j] != ' '){
            do{
                i = rand()% M;
                j = rand()% M;

            }while(tabuleiro[i][j] != ' ');
        }
        tabuleiro[i][j] = cartas[a];

    }
    system("cls");
    printf(" %c | %c | %c | %c \n", tabuleiro[0][0], tabuleiro[0][1], tabuleiro[0][2], tabuleiro[0][3]);
    printf("-----------------\n");
    printf(" %c | %c | %c | %c \n", tabuleiro[1][0], tabuleiro[1][1], tabuleiro[1][2], tabuleiro[1][3]);
    printf("-----------------\n");
    printf(" %c | %c | %c | %c \n", tabuleiro[2][0], tabuleiro[2][1], tabuleiro[2][2], tabuleiro[2][3]);
    printf("-----------------\n");
    printf(" %c | %c | %c | %c \n", tabuleiro[3][0], tabuleiro[3][1], tabuleiro[3][2], tabuleiro[3][3]);

}

void imprimeTabuleiroVirado(){
    system("cls");
    printf(" %c | %c | %c | %c \n", auxiliar[0][0], auxiliar[0][1], auxiliar[0][2], auxiliar[0][3]);
    printf("-----------------\n");
    printf(" %c | %c | %c | %c \n", auxiliar[1][0], auxiliar[1][1], auxiliar[1][2], auxiliar[1][3]);
    printf("-----------------\n");
    printf(" %c | %c | %c | %c \n", auxiliar[2][0], auxiliar[2][1], auxiliar[2][2], auxiliar[2][3]);
    printf("-----------------\n");
    printf(" %c | %c | %c | %c \n", auxiliar[3][0], auxiliar[3][1], auxiliar[3][2], auxiliar[3][3]);

}



int validarProximaRodada(){
    for(int i = 0; i<4; i++){
        for(int j = 0; j<4; j++){
            if(auxiliar[i][j] == '*'){
                return 1;
            }
        }
    }

    return 0;
}

void tentativaUsuario(){
    struct coordenadas c1, c2; //c1 e c2 s�o vari�veis para cada empacotamento das vari�veis "linha" e "coluna" do struct "coordenadas".
    do{
        printf("\nInsira qual posicao deseja selecionar. - (Linha 1-4, Coluna 1-4)\n");
        fflush(stdin);
        scanf("%d %d", &c1.linha, &c1.coluna);

        c1.linha--; c1.coluna--;

        while(auxiliar[c1.linha][c1.coluna] != '*'){
            system("cls");
            imprimeTabuleiroVirado();
            printf("\nInsira uma posicao valida. - (Linha 1-4, Coluna 1-4)\n");
            fflush(stdin);
            scanf("%d %d", &c1.linha, &c1.coluna);

            c1.linha--; c1.coluna--;

        }
        auxiliar[c1.linha][c1.coluna] = tabuleiro[c1.linha][c1.coluna];

        imprimeTabuleiroVirado();

        printf("\nInsira qual posicao deseja selecionar. - (Linha 1-4, Coluna 1-4)\n");
        fflush(stdin);
        scanf("%d %d", &c2.linha, &c2.coluna);

        c2.linha--; c2.coluna--;

        while(auxiliar[c2.linha][c2.coluna] != '*'){
            system("cls");
            imprimeTabuleiroVirado();
            printf("\nInsira uma posicao valida. - (Linha 1-4, Coluna 1-4)\n");
            fflush(stdin);
            scanf("%d %d", &c2.linha, &c2.coluna);

            c2.linha--; c2.coluna--;

        }

        auxiliar[c2.linha][c2.coluna] = tabuleiro[c2.linha][c2.coluna];

        imprimeTabuleiroVirado();

        if((auxiliar[c2.linha][c2.coluna] != auxiliar[c1.linha][c1.coluna]) || (c2.linha == c1.linha && c2.coluna == c1.coluna)){
            printf("\nVoce errou!");
            Sleep(2000);
            auxiliar[c1.linha][c1.coluna] = '*';
            auxiliar[c2.linha][c2.coluna] = '*';
            imprimeTabuleiroVirado();
        }else{
            printf("\nVoce acertou!");
            Sleep(2000);
            imprimeTabuleiroVirado();
        }


    } while(!validarProximaRodada());

}

int main(){
    int virar;

    resetaTabuleiro();
    printf("Voce tera 13 segundos para memorizar o tabuleiro - (Aperte 1 para confirmar)\n");
    do{
        scanf("%d", &virar);

        if(virar == 1){
            imprimeTabuleiro();
        }else{
            printf("Voce precisa confirmar para o jogo iniciar! (Aperte 1 para confirmar)\n");
        }
    }while(virar != 1);

    printf("\nMemorize!\n");
    Sleep(13000); //UsuArio tem 13 segundos para memorizar o tabuleiro
    
    imprimeTabuleiroVirado();
    tentativaUsuario();

    return 0;
}
