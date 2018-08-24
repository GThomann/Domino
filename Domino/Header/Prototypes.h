/*
*   Ultima alteracao: 24-08 15h
*
*   Jogo de dominó em modo console
*
*   Autor: Gustavo Luiz Thomann
*   
*
*/

#pragma once

#define FIM 50 //define o fim do jogo
#define HUMANO 1
#define MAQUINA 0
#define MONTE 2
#define MAX 30
#define PEC 28
#define PLAY 2
#define EMPTY 29

/******* STRUCTS ********/
struct pedra{
	int ladoE;
	int ladoD;
	int ladoEx; //posicao da pedra na tela (usado apenas para as pontas)
	int ladoEy; //posicao da pedra na tela (usado apenas para as pontas)
	int ladoDx; //posicao da pedra na tela (usado apenas para as pontas)
	int ladoDy; //posicao da pedra na tela (usado apenas para as pontas)
};
struct jogador{
	char nome[MAX];
	int idade;  //realmente necessario?
	int quantPedra;
	struct pedra minhas[21];
};
//definindo uma struct de um jeito diferente
typedef struct{
	char nome[MAX]; //
	int pontos;
}RECORDE;


/******** PROTOTYPES ********/
void gotoxy(int x, int y); //a contagem das linhas e colunas comeca sempre em 1,1
int pescaPedra(int *pilha, int quem, struct jogador todos[PLAY], struct pedra monte[PEC]);
void criaJogador(int tipo, struct jogador player[PLAY]); //0=pc, 1=humano
void iniciaPedras(int quem, struct jogador inicio[PLAY]);
void criaPedra(int *n, struct pedra criar[PEC]); // 2=pedra no monte, 1=pedra do humano, 0=pedra do pc
void sortear(int *turno, int *monte, struct pedra pedraMonte[PEC], struct jogador oponentes[PLAY]);
void embaralhar(struct pedra criadas[PEC]); //embaralha as pedras no monte
int maiorDuplo(struct jogador jogadorCerto);//verifica quem tem a maior pedra double e retorna o numero da pedra
int escolhePedra(struct jogador computador, struct pedra ptaJogo, char *pta); //verifica a pedra compativel para a maquina
int deitaPedra(char *direc_E, char *direc_D, int quem, struct pedra *ponta, struct jogador ambos[PLAY]); //coloca uma pedra na mesa
void desenhaPedra(char lado, struct pedra jogada, int x, int y);
void mostraLado(char orienta, int valorLado, int px, int py); //mostra o lado da pedra na tela
int jogo(char *cont, int monte, int turno, struct pedra ptaJogo, struct jogador personagem[PLAY], struct pedra pedraMonte[PEC], RECORDE jogaPontos[PLAY]); //jogo
void organizar(int opcao, struct jogador ambos[PLAY], struct pedra monte[PEC]); //opcao: 0=maquina, 1=humano e 2=monte
char jogarDenovo(); //verifica se comeca novo jogo
void limpaMenus(int msg, int mnu, int lst); //limpa todos os menus do jogo
void imprimePedras(struct jogador humano); //imprime as pedras da mao do jogador
void telaBase(); //desenha a tela do jogo
void mainMenu();
void ranking(int controle, char cont, struct jogador perdedor[PLAY], RECORDE jogaPontos[PLAY]); //cria o historico dos jogadores
void showRanking();