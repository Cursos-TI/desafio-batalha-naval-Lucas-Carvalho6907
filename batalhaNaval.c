#include <stdio.h>
#include <stdlib.h>

#define TAM 10              // Tamanho do tabuleiro (10x10)
#define NAVIO 3             // Valor que representa o navio
#define AGUA 0              // Valor que representa água
#define HABILIDADE 5        // Valor que representa habilidade aplicada
#define TAM_HABILIDADE 5    // Tamanho das matrizes de habilidade (5x5)

// Inicializa o tabuleiro com água
void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = AGUA;
}

// Exibe o tabuleiro no formato limpo para GitHub
void exibirTabuleiroGitHub(int tabuleiro[TAM][TAM]) {
    printf("Tabuleiro:\n\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Posiciona navio horizontal (3 casas)
void posicionarNavioHorizontal(int tabuleiro[TAM][TAM], int linha, int coluna) {
    for (int i = 0; i < 3 && (coluna + i) < TAM; i++) {
        tabuleiro[linha][coluna + i] = NAVIO;
    }
}

// Posiciona navio vertical (3 casas)
void posicionarNavioVertical(int tabuleiro[TAM][TAM], int linha, int coluna) {
    for (int i = 0; i < 3 && (linha + i) < TAM; i++) {
        tabuleiro[linha + i][coluna] = NAVIO;
    }
}

// Cria padrão em forma de cone (pirâmide)
void criarMatrizCone(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++)
        for (int j = 0; j < TAM_HABILIDADE; j++)
            matriz[i][j] = (j >= TAM_HABILIDADE / 2 - i && j <= TAM_HABILIDADE / 2 + i) ? 1 : 0;
}

// Cria padrão em forma de cruz
void criarMatrizCruz(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++)
        for (int j = 0; j < TAM_HABILIDADE; j++)
            matriz[i][j] = (i == TAM_HABILIDADE / 2 || j == TAM_HABILIDADE / 2) ? 1 : 0;
}

// Cria padrão em forma de octaedro (losango)
void criarMatrizOctaedro(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++)
        for (int j = 0; j < TAM_HABILIDADE; j++)
            matriz[i][j] = (abs(i - TAM_HABILIDADE / 2) + abs(j - TAM_HABILIDADE / 2) <= TAM_HABILIDADE / 2) ? 1 : 0;
}

// Aplica matriz de habilidade no tabuleiro
void aplicarHabilidade(int tabuleiro[TAM][TAM], int matriz[TAM_HABILIDADE][TAM_HABILIDADE], int origem_linha, int origem_coluna) {
    int offset = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int linhaTab = origem_linha - offset + i;
            int colunaTab = origem_coluna - offset + j;

            if (linhaTab >= 0 && linhaTab < TAM && colunaTab >= 0 && colunaTab < TAM) {
                if (matriz[i][j] == 1 && tabuleiro[linhaTab][colunaTab] == AGUA) {
                    tabuleiro[linhaTab][colunaTab] = HABILIDADE;
                }
            }
        }
    }
}

// Função principal
int main() {
    int tabuleiro[TAM][TAM];
    inicializarTabuleiro(tabuleiro);

    // Posiciona navios
    posicionarNavioHorizontal(tabuleiro, 1, 1); // (1,1) horizontal
    posicionarNavioVertical(tabuleiro, 2, 9);   // (2,9) vertical

    // Criação de padrões de habilidade
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];

    criarMatrizCone(cone);
    criarMatrizCruz(cruz);
    criarMatrizOctaedro(octaedro);

    // Aplicação das habilidades
    aplicarHabilidade(tabuleiro, cone, 0, 7);
    aplicarHabilidade(tabuleiro, cruz, 4, 2);
    aplicarHabilidade(tabuleiro, octaedro, 6, 8);

    // Exibe o tabuleiro final no formato desejado
    exibirTabuleiroGitHub(tabuleiro);

    return 0;
}
