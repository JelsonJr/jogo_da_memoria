
void alocaTabuleiroNaMemoria(FILE* f);
void liberaTabuleiroDaMemoria();
void leTabuleiro(FILE* f);
void imprimeTabuleiro();
void liberaTabuleiroDaMemoria();
void exibeTabuleiro();
void distribuiCartasNoTabuleiro();
void imprimeTabuleiro();

struct mesaDeJogo {
    int linhas, colunas;     
    char **tabuleiro;
};

typedef struct mesaDeJogo TABULEIRO;