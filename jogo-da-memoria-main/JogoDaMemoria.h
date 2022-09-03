#define NUMERO_DE_CARTAS 8
#define LINHA 4
#define COLUNA 4

struct coordenadas {     
    /*Este struct serve para "empacotar" 
    variaveis da funcao tentativaUsuario(), facilitando a leitura do codigo.*/
    int linha, coluna;
};

typedef struct coordenadas COORDENADAS;

int ganhar();
void atribuiValorAsCartas(int *cartasLinha, int *cartasColuna);
void iniciarJogo();
void distribuiCartasNoTabuleiro();
void resetaTabuleiro();
void imprimeTabuleiro();
void desenhaTabuleiro(int viradoOuNao);
void tentativaUsuario();
void copiaTabuleiro(char matrizOriginal[LINHA][COLUNA], char matrizCopia[LINHA][COLUNA]);