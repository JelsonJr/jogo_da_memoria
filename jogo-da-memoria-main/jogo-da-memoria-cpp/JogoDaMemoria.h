#define NUMERO_DE_CARTAS 8
#define LINHA 4
#define COLUNA 4
    
struct mesaDeJogo {     
    int linha, coluna;
    char tabuleiro[LINHA][COLUNA];
};

typedef struct mesaDeJogo TABULEIRO;

int ganhar();
int posicaoNaoEhValida(TABULEIRO *t);
void acertouOuErrou();
void atribuiValorAsCartas(int *cartasLinha, int *cartasColuna);
void iniciarJogo();
void resetaTabuleiro();
void resetaTabuleiro();
void imprimeTabuleiro();
void desenhaTabuleiro(int viradoOuNao);
void tentativaUsuario();
void copiaTabuleiro(char matrizOriginal[LINHA][COLUNA], char matrizCopia[LINHA][COLUNA]);