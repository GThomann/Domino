/*
*   Ultima alteracao: 24-08 15h
*
*   Jogo de dominó em modo console
*
*   Autor: Gustavo Luiz Thomann
*
*
*/

/****** DEFINITION OF ALL FUNCTIONS RELATED TO THE GRAFICS ******/

#include<stdlib.h>
#include<stdio.h>
#include<conio.h> // para usar getch()
#include<string.h>
#include<Windows.h>

#include "..\Header\Prototypes.h"

/* definição de gotoxy(x,y) */
void gotoxy(int x, int y) //a contagem das linhas e colunas comeca sempre em 1,1
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){
		x - 1, y - 1
	});  //precisa da biblioteca <windows.h>
}

//desenha o menu principal
void mainMenu(){
	system("cls");
	gotoxy(40, 10);
	puts("M E N U  P R I N C I P A L");
	gotoxy(30, 16);
	puts("J. Jogar");
	gotoxy(30, 18);
	puts("R. Regras");
	gotoxy(30, 20);
	puts("H. Hall da Fama");
	gotoxy(30, 22);
	puts("S. Sair");
	gotoxy(55, 19);
	printf("Qual sua escolha? ");
}

// Desenha a tela do jogo
void telaBase(){
	//sera considerado uma tela cheia com 1<=x<=140 e 1<=y<=55,
	//contados a partir do canto superior esquerdo
	int x, y;
	y = 1; //coordenadas minimas
	x = 1; //coordenadas minimas
	system("cls");
	gotoxy(8, 1); //a contagem comeca sempre em 1,1
	printf("PONTUACAO DO JOGO");
	gotoxy(2, 2);
	printf("Pontos de ");
	gotoxy(2, 3); //a contagem comeca sempre em 1,1
	printf("Meus pontos: 00");
	gotoxy(100, 2);
	printf("Quantidade de pedras no monte: 00");
	//desenha as barras horizontais
	for(x = 1; x <= 140; x++){
		gotoxy(x, 4);
		printf("-");
		gotoxy(x, 40);
		printf("-");
	}
	/*
	//desenha o centro da tela
	for(y=8; y<40; y=y+2)
	{
	gotoxy(70,y);
	puts("|");
	}
	*/
	//desenha a barra vertical
	for(y = 41; y <= 49; y++){
		gotoxy(50, y);
		printf("|");
	}
	//escrita abaixo da barra inferior
	gotoxy(68, 41);
	printf("MINHAS PEDRAS");
	gotoxy(115, 41);
	puts(" ainda tem 00");
	gotoxy(129, 41);
	puts("pedra(s).");
} //fim da funcao tealBase

  // limpa os menus do jogo
void limpaMenus(int msg, int mnu, int lst){
	int i, j;
	//limpa a regiao dos menus
	if(mnu == 1){
		for(j = 41; j<49; j++){
			for(i = 0; i<49; i++){
				gotoxy(i, j);
				printf(" ");
			}
		}
	}
	//limpa a area das pedras do jogador
	if(lst == 1){
		for(j = 43; j<48; j++){
			for(i = 51; i<140; i++){
				gotoxy(i, j);
				printf(" ");
			}
		}
	}

	//limpa a area de mensagens
	//este bloco nao esta mais sendo usado - layout alterado
	if(msg == 1){
		for(i = 50; i<99; i++){
			gotoxy(i, 2); //apenas a linha das mensagens
			printf(" ");
		}
	}
} //fim da funcao limpaMenus

  //imprime as pedras da mao
void imprimePedras(struct jogador personagem){
	int x, y, j;
	x = 55; //posicao inicial
	y = 43; //posicao inicial
	for(j = 0; j<personagem.quantPedra; j++) //desenha apenas as pedras que o humano tiver na mao
	{
		//passa para a coluna ao lado
		if(y>47){
			y = 43;
			x = x + 12;
		}
		gotoxy(x, y);
		//so imprime as pedras validas
		//if(personagem[HUMANO].minhas[j].ladoE!=29) //A forma que o for foi feito tornou essa verificacao desnecessaria
		{
			printf("%d. |%d|%d|", j, personagem.minhas[j].ladoE, personagem.minhas[j].ladoD);
			y = y + 2; //pula uma linha
		}
	}
} //fim da funcao imprimePedras

  //veririca se joga novamente
char jogarDenovo(){
	char opc;
	int loop = 1;
	while(loop == 1){
		system("cls");
		gotoxy(50, 20);
		printf("Deseja jogar novamente (S/N)? ");
		opc = toupper(_getche());
		switch(opc){
			case 'S':
				loop = 0;
				break;
			case 'N':
				loop = 0;
				opc = '0'; //volta ao menu principal
				gotoxy(45, 23);
				puts("Treine mais antes de voltar!!!\n\n");
				system("pause");
				break;
			default:
				gotoxy(45, 25);
				puts("Opcao invalida.");
				Sleep(1000); //aguarda 1seg
		}
	}
	return(opc);
} //fim da funcao jogarDenovo

  //desenha uma pedra na tela
void desenhaPedra(char lado, struct pedra jogada, int x, int y){
	gotoxy(x, y);
	if(lado == 'N') //desenha a pedra na horizontal e com posicao normal
	{
		mostraLado('H', jogada.ladoE, x, y);
		mostraLado('B', jogada.ladoE, x, y); //imprime a divisao entre os lados
		mostraLado('H', jogada.ladoD, x + 8, y);
	}
	else{
		if(lado == 'I') //desenha a pedra na horizontal e com posicao invertida
		{
			mostraLado('H', jogada.ladoD, x, y);
			mostraLado('B', jogada.ladoE, x, y); //imprime a divisao entre os lados
			mostraLado('H', jogada.ladoE, x + 8, y);
		}
		else{
			if(lado == 'V') //desenha a pedra na vertical na posicao normal
			{
				mostraLado('V', jogada.ladoE, x, y);
				mostraLado('b', jogada.ladoE, x, y); //imprime a divisao entre os lados
				mostraLado('V', jogada.ladoD, x, y + 6);
			}
			if(lado == 'T') //desenha a pedra na vertical na posicao invertida
			{
				mostraLado('V', jogada.ladoD, x, y);
				mostraLado('b', jogada.ladoE, x, y); //imprime a divisao entre os lados
				mostraLado('V', jogada.ladoE, x, y + 6);
			}
		}
	}
} //fim da funcao desenha pedra

  //mostra o lado da pedra na tela
void mostraLado(char orienta, int valorLado, int px, int py){   //altera as cores para imprimir as pedras
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112); //128 eh o fundo cinza + 9 do texto azul = 137

	if(orienta == 'B') //imprime a divisao entre os lados na vertical
	{
		int i;
		for(i = py + 1; i<py + 4; i++){
			gotoxy(px + 7, i);
			putchar('|');
		}
	}
	else{
		if(orienta == 'b') //imprime a divisao entre os lados na horizontal
		{
			int i;
			for(i = px; i<px + 5; i++){
				gotoxy(i, py + 6);
				putchar('-');
			}
		}
	}
	if(orienta == 'H'){
		if(valorLado == 0){
			gotoxy(px, ++py);
			puts("       ");
			gotoxy(px, ++py);
			puts("       ");
			gotoxy(px, ++py);
			puts("       ");
		}
		else{
			if(valorLado == 1){
				gotoxy(px, ++py);
				puts("       ");
				gotoxy(px, ++py);
				puts("   *   ");
				gotoxy(px, ++py);
				puts("       ");
			}
			else{
				if(valorLado == 2){
					gotoxy(px, ++py);
					puts(" *     ");
					gotoxy(px, ++py);
					puts("       ");
					gotoxy(px, ++py);
					puts("     * ");
				}
				else{
					if(valorLado == 3){
						gotoxy(px, ++py);
						puts(" *     ");
						gotoxy(px, ++py);
						puts("   *   ");
						gotoxy(px, ++py);
						puts("     * ");
					}
					else{
						if(valorLado == 4){
							gotoxy(px, ++py);
							puts(" *   * ");
							gotoxy(px, ++py);
							puts("       ");
							gotoxy(px, ++py);
							puts(" *   * ");
						}
						else{
							if(valorLado == 5){

								gotoxy(px, ++py);
								puts(" *   * ");
								gotoxy(px, ++py);
								puts("   *   ");
								gotoxy(px, ++py);
								puts(" *   * ");
							}
							else{
								if(valorLado == 6){

									gotoxy(px, ++py);
									puts(" * * * ");
									gotoxy(px, ++py);
									puts("       ");
									gotoxy(px, ++py);
									puts(" * * * ");
								}
							}
						}
					}
				}
			}
		}
	}
	if(orienta == 'V'){
		if(valorLado == 0){

			gotoxy(px, ++py);
			puts("     ");
			gotoxy(px, ++py);
			puts("     ");
			gotoxy(px, ++py);
			puts("     ");
			gotoxy(px, ++py);
			puts("     ");
			gotoxy(px, ++py);
			puts("     ");
		}
		else{
			if(valorLado == 1){
				gotoxy(px, ++py);
				puts("     ");
				gotoxy(px, ++py);
				puts("     ");
				gotoxy(px, ++py);
				puts("  *  ");
				gotoxy(px, ++py);
				puts("     ");
				gotoxy(px, ++py);
				puts("     ");
			}
			else{
				if(valorLado == 2){
					gotoxy(px, ++py);
					puts(" *   ");
					gotoxy(px, ++py);
					puts("     ");
					gotoxy(px, ++py);
					puts("     ");
					gotoxy(px, ++py);
					puts("     ");
					gotoxy(px, ++py);
					puts("   * ");
				}
				else{
					if(valorLado == 3){
						gotoxy(px, ++py);
						puts(" *   ");
						gotoxy(px, ++py);
						puts("     ");
						gotoxy(px, ++py);
						puts("  *  ");
						gotoxy(px, ++py);
						puts("     ");
						gotoxy(px, ++py);
						puts("   * ");
					}
					else{
						if(valorLado == 4){
							gotoxy(px, ++py);
							puts(" * * ");
							gotoxy(px, ++py);
							puts("     ");
							gotoxy(px, ++py);
							puts("     ");
							gotoxy(px, ++py);
							puts("     ");
							gotoxy(px, ++py);
							puts(" * * ");
						}
						else{
							if(valorLado == 5){
								gotoxy(px, ++py);
								puts(" * * ");
								gotoxy(px, ++py);
								puts("     ");
								gotoxy(px, ++py);
								puts("  *  ");
								gotoxy(px, ++py);
								puts("     ");
								gotoxy(px, ++py);
								puts(" * * ");
							}
							else{
								if(valorLado == 6){
									gotoxy(px, ++py);
									puts(" * * ");
									gotoxy(px, ++py);
									puts("     ");
									gotoxy(px, ++py);
									puts(" * * ");
									gotoxy(px, ++py);
									puts("     ");
									gotoxy(px, ++py);
									puts(" * * ");
								}
							}
						}
					}
				}
			}
		}
	}
	//volta as configuracoes do jogo
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 63); //128 eh fundo cinza + 15 do texto branco brilhante = 143
} //fim da funcao mostraLado