/*
*   Ultima alteracao: 24-08 15h
*
*   Jogo de dominó em modo console
*
*   Autor: Gustavo Luiz Thomann
*
*
*/

/****** DEFINITION OF ALL FUNCTIONS RELATED TO THE GAME LOGIC ******/

#include<stdlib.h>
#include<stdio.h>
#include<conio.h> // para usar getch()
#include<string.h>
#include<time.h> //para usar a funcao rand() e srand()
#include<windows.h> //para usar meu gotoxy, SetConsoleTextAttribute() e Sleep()

#include "..\Header\Prototypes.h"

//cria o jogador
void criaJogador(int tipo, struct jogador player[PLAY]){
	int i;
	printf("\nCriando jogador ...");
	if(tipo == HUMANO){
		//printf("\nHumano: ");
		printf("\nQual o seu nome? ");
		gets(player[tipo].nome);
		//printf("Qual sua idade? "); //desnecessario por hora
		//scanf("%d",&player[tipo].idade); //desnecessario por hora
		player[tipo].quantPedra = 0;
	}
	else{
		printf("\nOponente: ");
		strcpy(player[tipo].nome, "Dominordico");
		player[tipo].idade = 36;
		player[tipo].quantPedra = 0;
		printf("\n%s ", player[tipo].nome);
		printf("\nIdade aproximada: %d geracoes de processadores\n", player[tipo].idade);
		for(i = 0; i<21; i++){
			player[tipo].minhas[i].ladoE = 29;
			player[tipo].minhas[i].ladoEx = 6;
			player[tipo].minhas[i].ladoEy = 10;
			player[tipo].minhas[i].ladoD = 29;
			player[tipo].minhas[i].ladoDx = 1;
			player[tipo].minhas[i].ladoDy = 10;
		}
	}
} //fim da funcao criaJogador

  //inicia as pedras dos jogadores
void iniciaPedras(int quem, struct jogador inicio[PLAY]){
	int i;
	for(i = 0; i<21; i++){
		inicio[quem].minhas[i].ladoE = 29;
		inicio[quem].minhas[i].ladoEx = 6;
		inicio[quem].minhas[i].ladoEy = 10;
		inicio[quem].minhas[i].ladoD = 29;
		inicio[quem].minhas[i].ladoDx = 1;
		inicio[quem].minhas[i].ladoDy = 10;
	}
} //fim da funcao iniciaPedras

  //pesca uma pedra do monte
int pescaPedra(int *pilha, int quem, struct jogador todos[PLAY], struct pedra monte[PEC]){
	int pedra, temp, posAux;
	srand((unsigned)time(NULL)); //gera uma numero inicial(semente) para gerar os aleatorios a partir da hora atual
								 //sorteia 1 pedra distinta
	temp = 0;
	pedra = rand() % (*pilha); // faz a divisao inteira por quantas pedras houver no monte
							   //dificilmente executara esse bloco
	if(monte[pedra].ladoE == 29) //se encontrar o 29, o Monte nao tem essa pedra
	{
		temp = 1; //a pedra nao esta no monte
	}
	if(temp == 0){
		posAux = todos[quem].quantPedra; //posicao da pedra a ser pescada
		todos[quem].minhas[posAux] = monte[pedra]; //copia a pedra do monte para o jogador
												   //elimina a pedra do monte
		monte[pedra].ladoE = 29;
		monte[pedra].ladoD = 29;
		organizar(MONTE, todos, monte);
		//retira uma a pedra do monte(quantidade)
		(*pilha)--; //necessario os parenteses para lidar com o ponteiro
		todos[quem].quantPedra++; //soma 1 pedra ao estoque do jogador
	}
	return(temp);
} //fim da funcao pescaPedra

  //organiza as pedras
void organizar(int opcao, struct jogador ambos[PLAY], struct pedra monte[PEC]){
	int i;

	if(opcao == 2) //organiza as pedras do monte
	{
		for(i = 0; i<PEC; i++){
			//comeca a reorganizar a partir da primeira invalida encontrada
			if(monte[i].ladoE == 29){
				if((i + 1)<PEC){
					monte[i] = monte[i + 1];
					monte[i + 1].ladoE = 29;
					monte[i + 1].ladoD = 29;
				}
			}
		}
	}
	else //organiza as pedras dos jogadores
	{
		for(i = 0; i<(PEC - 7); i++){
			//comeca a reorganizar a partir da primeira invalida encontrada
			if(ambos[opcao].minhas[i].ladoE == 29){
				if((i + 1)<(PEC - 7)){
					ambos[opcao].minhas[i] = ambos[opcao].minhas[i + 1];
					ambos[opcao].minhas[i + 1].ladoE = 29;
					ambos[opcao].minhas[i + 1].ladoD = 29;
				}
			}
		}
	}
} //fim da funcao organizar

  //criacao das pedras do jogo
void criaPedra(int *n, struct pedra criar[PEC]) // 0=pedra no monte, 1=pedras do pc, 2=pedra do humano
{
	int i, j;
	printf("\nCriando pedras ...");
	Sleep(500); //apenas para visualizar
	for(i = 0; i<(PEC); i++) //inicializa as pecas
	{
		criar[i].ladoE = 29; //pedra impossivel
		criar[i].ladoD = 29; //pedra impossivel
							 //coordenadas iniciais
		criar[i].ladoDx = 6;
		criar[i].ladoDy = 10;
		criar[i].ladoEx = 1;
		criar[i].ladoEy = 1;
	}
	//criacao das pedras
	for(i = 0; i<7; i++){
		for(j = 0; j <= i; j++){
			criar[*n].ladoE = i;
			criar[*n].ladoD = j;
			(*n)++;
		}
	}
	Sleep(500); //retarda em 500 milisegundos
} //fim da funcao criaPedra

  //embaralha as pedras no monte
void embaralhar(struct pedra criadas[PEC]){
	struct pedra aux;
	int i, k;

	printf("\nEmbaralhando pedras ...");
	Sleep(500); //apenas para visualizar
				//gera uma numero inicial(semente)
				//para gerar os aleatorios a partir da hora atual
	srand((unsigned)time(NULL));
	for(k = 0; k<PEC; k++){
		i = rand() % 100; // faz a divisao inteira por 100
		i = i % 28; //faz a divisao inteira por 28
		if(i != k){
			aux = criadas[i];
			criadas[i] = criadas[k];
			criadas[k] = aux;
		}
	}
} //fim da funcao embaralhar

  //sorteia as pedras -> OTIMIZAR
void sortear(int *turno, int *monte, struct pedra pedraMonte[PEC], struct jogador oponentes[PLAY]){
	int ret;
	//sorteando 7 pedras para cada um intercalando
	printf("\nSorteando pedras ...");
	printf("\nAguarde... ");
	ret = 1;
	//*********otimizar essa parte!!!!!!!!
	//executa esse bloco enquanto os dois jogadores nao possuirem 7 pedras cada
	while(!((oponentes[HUMANO].quantPedra == 7) && (oponentes[MAQUINA].quantPedra == 7))){
		if(((*turno) == HUMANO) && (oponentes[HUMANO].quantPedra<7)){
			ret = pescaPedra(&(*monte), HUMANO, oponentes, pedraMonte); //sorteia as pedras para o humano, primeiro sorteio
			if(ret == 0){
				(*turno) = MAQUINA;
			}
		}
		if(((*turno) == MAQUINA) && (oponentes[MAQUINA].quantPedra<7)){
			ret = pescaPedra(&(*monte), MAQUINA, oponentes, pedraMonte); //sorteia as pedras para o pc, segundo sorteio
			if(ret == 0){
				(*turno) = HUMANO;
			}
		}
		Sleep(100); //apenas para visualizar
	}
} //fim da funcao sortear

  //verifica quem tem a maior pedra double
int maiorDuplo(struct jogador jogadorCerto){
	int i, n, mDuplo;
	n = 0; //sera usado para comparar qual a dupla e a maior (caso haja mais de uma)
	mDuplo = EMPTY; //valor padrao para falta da pedra
	for(i = 0; i<jogadorCerto.quantPedra; i++) //percorre todas as pedras do jogador
	{
		if((jogadorCerto.minhas[i].ladoE != EMPTY)) //verifica se eh uma pedra valida
		{
			//verifica se os dois lados sao iguais
			if(jogadorCerto.minhas[i].ladoE == jogadorCerto.minhas[i].ladoD){
				n++; //
				if(n == 2){
					//compara apenas um lado porque se chegou aqui
					//os dois lados sao iguais
					if(jogadorCerto.minhas[i].ladoE>jogadorCerto.minhas[mDuplo].ladoE){
						mDuplo = i; //guarda a posicao da  maior pedra
						n = 1; //considera como se houvesse apenas uma dupla
					}
					else{
						n = 1;
					}
				}
				else{
					mDuplo = i; //guarda a posicao da pedra
				}
			}
		}
	}
	return(mDuplo); //retorna qual a maior pedra dupla
} //fim da funcao maiorDuplo

  //escolhe a pedra a ser jogada pelo PC e indica a ponta
int escolhePedra(struct jogador computador, struct pedra ptaJogo, char *pta){
	int i, escolha;
	for(i = 0; i<computador.quantPedra; i++){
		//verifica lado esquerdo da mesa
		if((ptaJogo.ladoE == computador.minhas[i].ladoE) || (ptaJogo.ladoE == computador.minhas[i].ladoD)){
			(*pta) = 'E';
			escolha = i; //guarda o indice da pedra compativel
			break; //sai do for quando encontrar a primeira (inteligencia 0)
		}
		else{
			//verifica o lado direito
			if((ptaJogo.ladoD == computador.minhas[i].ladoE) || (ptaJogo.ladoD == computador.minhas[i].ladoD)){
				(*pta) = 'D';
				escolha = i; //guarda o indice da pedra compativel
				break; //sai do for quando encontrar a primeira (inteligencia 0)
			}
			else{
				escolha = -1; //a pedra nao combina com a ponta
			}
		}
	}
	return(escolha);
} //fim da funcao escolePedra

  // Faz a jogada e retorna a direcao da proxima N=sentido normal, I=sentido invertido
int deitaPedra(char *direc_E, char *direc_D, int quem, struct pedra *ponta, struct jogador ambos[PLAY]){
	int opc, confirma;
	char pta;
	confirma = 0; //se der tudo certo nao sera alterado
				  //inicializacoes
	pta = 'X';
	opc = 0;
	if(quem == HUMANO){
		gotoxy(5, 43);
		printf("Qual o numero da pedra que deseja jogar? ");
		opc = (_getche() - '0'); //converte o valor de char para o int correspondente
		gotoxy(5, 44);
		printf("Qual lado da mesa deseja combinar (E/D)? ");
		pta = toupper(_getche());
	}
	else{
		if(quem == MAQUINA){
			gotoxy(2, 44);
			printf("%s joga agora!", ambos[quem].nome);
			Sleep(2000); //aguarda 2 seg
						 //passa como parametros 2 e 3 o valor do endereco apontado por ponta e o endereco de pta
			opc = escolhePedra(ambos[MAQUINA], (*ponta), &pta); //verifica se tem uma pedra que encaixa e retorna qual e'
			if(opc == -1) // a pedra nao serve
			{
				pta = 'X'; //apenas para garantir que nao tera lixo
			}
		}
		else{
			puts("DEU MERDA.Turno indefinido!");
			_getch();
		}
	}
	//codigo comum para humano e maquina
	switch(pta){
		case 'E':
		{
			switch(*direc_E){
				case 'N': //situacao normal
				{
					if((*ponta).ladoEx - 5 >= 11) //esta longe da borda esquerda
					{
						if((*ponta).ladoE == ambos[quem].minhas[opc].ladoE) //ponta esquerda igual ao lado esquerdo da pedra
						{
							desenhaPedra('I', ambos[quem].minhas[opc], (*ponta).ladoEx - 17, (*ponta).ladoEy);
							(*ponta).ladoE = ambos[quem].minhas[opc].ladoD; //a ponta recebe o lado livre
						}
						else{
							if((*ponta).ladoE == ambos[quem].minhas[opc].ladoD) //ponta esquerda igual ao lado direito da pedra
							{
								desenhaPedra('N', ambos[quem].minhas[opc], (*ponta).ladoEx - 17, (*ponta).ladoEy);
								(*ponta).ladoE = ambos[quem].minhas[opc].ladoE; //a ponta recebe o lado livre
							}
							else{
								gotoxy(2, 47);
								printf("A pedra selecionada nao combina com essa ponta.");
								Sleep(1500); //aguarda 1,5segundos
								confirma = 1; //algo deu errado
								break;
							}
						}
						//atualiza as coordenadas
						(*ponta).ladoEx = (*ponta).ladoEx - 17;
						(*ponta).ladoEy = (*ponta).ladoEy;
					}
					else{
						if((*ponta).ladoEx - 6<11) //proximo da borda esquerda -> chegando
						{
							if((*ponta).ladoE == ambos[quem].minhas[opc].ladoE) //ponta esquerda igual ao lado esquerdo da pedra
							{
								desenhaPedra('V', ambos[quem].minhas[opc], (*ponta).ladoEx - 7, (*ponta).ladoEy);
								(*ponta).ladoE = ambos[quem].minhas[opc].ladoD;
							}
							else{
								if((*ponta).ladoE == ambos[quem].minhas[opc].ladoD) //ponta esquerda igual ao lado direito da pedra
								{
									desenhaPedra('T', ambos[quem].minhas[opc], (*ponta).ladoEx - 7, (*ponta).ladoEy);
									(*ponta).ladoE = ambos[quem].minhas[opc].ladoE;
								}
								else{
									gotoxy(2, 47);
									printf("A pedra selecionada nao combina com essa ponta.");
									Sleep(1500); //aguarda 1,5segundos
									confirma = 1; //algo deu errado
									break;
								}
							}
							(*direc_E) = 'I'; //inverte a direcao do desenho na tela
							(*ponta).ladoEy = (*ponta).ladoEy + 8;
							(*ponta).ladoEx = (*ponta).ladoEx;
						}
					}
					ambos[quem].minhas[opc].ladoD = 29;
					ambos[quem].minhas[opc].ladoE = 29;
					ambos[quem].quantPedra--;
					break;
				}
				case 'I': //situacao invertida
				{
					if(((*ponta).ladoEx >= 11) && ((*ponta).ladoEx + 6<65)) //esta entre a borda esquerda e o centro
					{
						if((*ponta).ladoE == ambos[quem].minhas[opc].ladoE) //ponta esquerda igual ao lado esquerdo da pedra
						{
							desenhaPedra('N', ambos[quem].minhas[opc], (*ponta).ladoEx, (*ponta).ladoEy);
							(*ponta).ladoE = ambos[quem].minhas[opc].ladoD; //a ponta recebe o lado livre
						}
						else{
							if((*ponta).ladoE == ambos[quem].minhas[opc].ladoD) //ponta esquerda igual ao lado direito da pedra
							{
								desenhaPedra('I', ambos[quem].minhas[opc], (*ponta).ladoEx, (*ponta).ladoEy);
								(*ponta).ladoE = ambos[quem].minhas[opc].ladoE; //a ponta recebe o lado livre
							}
							else{
								gotoxy(2, 47);
								printf("A pedra selecionada nao combina com essa ponta.");
								Sleep(1500); //aguarda 1,5segundos
								confirma = 1; //algo deu errado
								break;
							}
						}
						(*ponta).ladoEx = (*ponta).ladoEx + 17; //atualiza as coordenadas
						(*ponta).ladoEy = (*ponta).ladoEy;
					}
					else{
						if((*ponta).ladoEx + 6 >= 65) //proximo ao centro da tela
						{
							if((*ponta).ladoE == ambos[quem].minhas[opc].ladoE) //ponta esquerda igual ao lado esquerdo da pedra
							{
								desenhaPedra('V', ambos[quem].minhas[opc], (*ponta).ladoEx, (*ponta).ladoEy);
								(*ponta).ladoE = ambos[quem].minhas[opc].ladoD; //a ponta recebe o lado livre
							}
							else{
								if((*ponta).ladoE == ambos[quem].minhas[opc].ladoD) //ponta esquerda igual ao lado direito da pedra
								{
									desenhaPedra('T', ambos[quem].minhas[opc], (*ponta).ladoEx, (*ponta).ladoEy);
									(*ponta).ladoE = ambos[quem].minhas[opc].ladoE; //a ponta recebe o lado livre
								}
								else{
									gotoxy(2, 47);
									printf("A pedra selecionada nao combina com essa ponta.");
									Sleep(1500); //aguarda 1,5segundos
									confirma = 1; //algo deu errado
									break;
								}
							}
							(*direc_E) = 'N'; //inverte a direcao do desenho na tela
							(*ponta).ladoEx = (*ponta).ladoEx; //atualiza as coordenadas
							(*ponta).ladoEy = (*ponta).ladoEy + 8;
						}
					}
					ambos[quem].minhas[opc].ladoD = 29;
					ambos[quem].minhas[opc].ladoE = 29;
					ambos[quem].quantPedra--;
					break;
				}
			}
			break;
		}
		case 'D':
		{
			switch(*direc_D){
				case 'N': //situacao normal
				{
					if((*ponta).ladoDx + 6<131) //esta longe da borda direita
					{
						if((*ponta).ladoD == ambos[quem].minhas[opc].ladoE) //ponta direita igual ao lado esquerdo da pedra
						{
							desenhaPedra('N', ambos[quem].minhas[opc], (*ponta).ladoDx + 1, (*ponta).ladoDy);
							(*ponta).ladoD = ambos[quem].minhas[opc].ladoD; //a ponta recebe o lado livre
						}
						else{
							if((*ponta).ladoD == ambos[quem].minhas[opc].ladoD) //ponta direita igual ao lado direito da pedra
							{
								desenhaPedra('I', ambos[quem].minhas[opc], (*ponta).ladoDx + 1, (*ponta).ladoDy);
								(*ponta).ladoD = ambos[quem].minhas[opc].ladoE; //a ponta recebe o lado livre
							}
							else{
								gotoxy(2, 47);
								printf("A pedra selecionada nao combina com essa ponta.");
								Sleep(1500); //aguarda 1,5segundos
								confirma = 1; //algo deu errado
								break;
							}
						}
						//atualiza as coordenadas
						(*ponta).ladoDx = (*ponta).ladoDx + 17;
						(*ponta).ladoDy = (*ponta).ladoDy;
					}
					else{
						if((*ponta).ladoDx + 6 >= 131) //proximo da borda direita -> chegando
						{
							if((*ponta).ladoD == ambos[quem].minhas[opc].ladoE) //ponta direita igual ao lado esquerdo da pedra
							{
								(*ponta).ladoD = ambos[quem].minhas[opc].ladoD;
								desenhaPedra('V', ambos[quem].minhas[opc], (*ponta).ladoDx + 1, (*ponta).ladoDy);
							}
							else{
								if((*ponta).ladoD == ambos[quem].minhas[opc].ladoD) //ponta direita igual ao lado direito da pedra
								{
									(*ponta).ladoD = ambos[quem].minhas[opc].ladoE;
									desenhaPedra('T', ambos[quem].minhas[opc], (*ponta).ladoDx + 1, (*ponta).ladoDy);
								}
								else{
									gotoxy(2, 47);
									printf("A pedra selecionada nao combina com essa ponta.");
									Sleep(1500); //aguarda 1,5segundos
									confirma = 1; //algo deu errado
									break;
								}
							}
							(*direc_D) = 'I'; //inverte a direcao do desenho na tela
							(*ponta).ladoDy = (*ponta).ladoDy + 8;
							(*ponta).ladoDx = (*ponta).ladoDx + 1;
						}
					}
					ambos[quem].minhas[opc].ladoD = 29;
					ambos[quem].minhas[opc].ladoE = 29;
					ambos[quem].quantPedra--;
					break;
				}
				case 'I': //situacao invertida
				{
					if(((*ponta).ladoDx - 6>87) && ((*ponta).ladoDx + 6<131)) //esta entre a borda direita e o centro
					{
						if((*ponta).ladoD == ambos[quem].minhas[opc].ladoE) //ponta direita igual ao lado esquerdo da pedra
						{
							desenhaPedra('I', ambos[quem].minhas[opc], (*ponta).ladoDx - 17, (*ponta).ladoDy);
							(*ponta).ladoD = ambos[quem].minhas[opc].ladoD; //a ponta recebe o lado livre
						}
						else{
							if((*ponta).ladoD == ambos[quem].minhas[opc].ladoD) //ponta direita igual ao lado direito da pedra
							{
								desenhaPedra('N', ambos[quem].minhas[opc], (*ponta).ladoDx - 17, (*ponta).ladoDy);
								(*ponta).ladoD = ambos[quem].minhas[opc].ladoE; //a ponta recebe o lado livre
							}
							else{
								gotoxy(2, 47);
								printf("A pedra selecionada nao combina com essa ponta.");
								Sleep(1500); //aguarda 1,5segundos
								confirma = 1; //algo deu errado
								break;
							}
						}
						(*ponta).ladoDx = (*ponta).ladoDx - 17; //atualiza as coordenadas
						(*ponta).ladoDy = (*ponta).ladoDy;
					}
					else{
						if((*ponta).ladoDx - 6 <= 87) //proximo ao centro da tela -> chegando
						{
							if((*ponta).ladoD == ambos[quem].minhas[opc].ladoE) //ponta esquerda igual ao lado esquerdo da pedra
							{
								desenhaPedra('V', ambos[quem].minhas[opc], (*ponta).ladoDx - 7, (*ponta).ladoDy);
								(*ponta).ladoD = ambos[quem].minhas[opc].ladoD; //a ponta recebe o lado livre
							}
							else{
								if((*ponta).ladoD == ambos[quem].minhas[opc].ladoD) //ponta esquerda igual ao lado direito da pedra
								{
									desenhaPedra('T', ambos[quem].minhas[opc], (*ponta).ladoDx - 7, (*ponta).ladoDy);
									(*ponta).ladoD = ambos[quem].minhas[opc].ladoE; //a ponta recebe o lado livre
								}
								else{
									gotoxy(2, 47);
									printf("A pedra selecionada nao combina com essa ponta.");
									Sleep(1500); //aguarda 1,5segundos
									confirma = 1; //algo deu errado
									break;
								}
							}
							(*direc_D) = 'N'; //inverte a direcao do desenho na tela
							(*ponta).ladoDx = (*ponta).ladoDx - 1; //atualiza as coordenadas
							(*ponta).ladoDy = (*ponta).ladoDy + 8;
						}
					}
					if((*ponta).ladoDx + 6 >= 131) //proximo da borda direita -> saindo
					{
						if((*ponta).ladoD == ambos[quem].minhas[opc].ladoE) //ponta direita igual ao lado esquerdo da pedra
						{
							desenhaPedra('I', ambos[quem].minhas[opc], (*ponta).ladoDx - 17, (*ponta).ladoDy);
							(*ponta).ladoD = ambos[quem].minhas[opc].ladoD; //a ponta recebe o lado livre
						}
						else{
							if((*ponta).ladoD == ambos[quem].minhas[opc].ladoD) //ponta direita igual ao lado direito da pedra
							{
								desenhaPedra('N', ambos[quem].minhas[opc], (*ponta).ladoDx - 17, (*ponta).ladoDy);
								(*ponta).ladoD = ambos[quem].minhas[opc].ladoE; //a ponta recebe o lado livre
							}
							else{
								gotoxy(2, 47);
								printf("A pedra selecionada nao combina com essa ponta.");
								Sleep(1500); //aguarda 1,5segundos
								confirma = 1; //algo deu errado
								break;
							}
						}
						(*ponta).ladoDx = (*ponta).ladoDx - 17; //atualiza as coordenadas
						(*ponta).ladoDy = (*ponta).ladoDy;
					}
					ambos[quem].minhas[opc].ladoD = 29;
					ambos[quem].minhas[opc].ladoE = 29;
					ambos[quem].quantPedra--;
					break;
				}
			}
			break;
		}
		default:
			if(opc == -1) //o PC nao tem uma pedra compativel
			{
				confirma = -1;
				break;
			}
			else{
				limpaMenus(0, 1, 0);
				gotoxy(20, 45);
				printf("Opcao invalida");
				Sleep(1000);
				confirma = 1; //algo deu errado
				break;
			}

	}
	return(confirma);
} //fim da funcao deitaPedra

  //jogo com as logicas
int jogo(char *cont, int monte, int turno, struct pedra ptaJogo, struct jogador personagem[PLAY], struct pedra pedraMte[PEC], RECORDE jogaPontos[PLAY]){
	int ret, acabou, pesca, contaPassa;
	char opc, direc_D, direc_E;

	//inicializacao das direcoes. Todas normais
	direc_E = 'N';
	direc_D = 'N';
	acabou = 0;
	contaPassa = 0; //inicializa a variavel se passarem a vez mais que 3 vezes, significa que travou a partida


	gotoxy(strlen(personagem[MAQUINA].nome) + 12, 2);
	/*
	printf(": %.2d", jogaPontos[MAQUINA].pontos); //formata a saida com dois algarismos
	gotoxy(14,3);
	printf(" %.2d", jogaPontos[HUMANO].pontos);
	*/
	while(acabou == 0) //enquanto os jogadores possuirem pedras para jogar
	{
		organizar(HUMANO, personagem, pedraMte); //reorganiza as pedras do humano
		organizar(MAQUINA, personagem, pedraMte); //reorganiza as pedras da maquina
												  //atualiza a informacao do numero de pedras do oponente
		gotoxy(126, 41);
		printf("%.2d", personagem[MAQUINA].quantPedra); //formata a saida com dois algarismos
														//atualiza a quantidade de pedras no monte
		gotoxy(131, 2);
		printf("%.2d", monte); //formata a saida com dois algarismos
							   /*
							   //mostra os pontos
							   gotoxy(strlen(personagem[MAQUINA].nome)+12,2);
							   printf(": %.2d", jogaPontos[MAQUINA].pontos); //formata a saida com dois algarismos
							   gotoxy(14,3);
							   printf(" %.2d", jogaPontos[HUMANO].pontos);
							   */
		if(turno == HUMANO){
			ret = 1;
			pesca = 1; //habilita a pesca de pedras
			while(ret) //executa enquanto ret valer 1
			{
				//limpa os menus
				limpaMenus(0, 1, 0); //limpaMenus(0,1,0) -> limpaMenus(msg,mnu,lst)
									 //imprime o menu seletivo
				if((pesca == 1) && (monte>0)) //habilitar essa opcao apenas se houver pedras no monte ou se nao pescou nesse turno
				{   //so sera permitido pescar se ainda nao pescou ou se tem pedras no monte
					gotoxy(2, 44);
					puts("C. Comprar");
				}
				else{   //so sera permitido passar a vez se pescar antes ou se nao houver pedras a pescar
					gotoxy(2, 44);
					puts("P. Passar");
				}
				gotoxy(2, 46);
				puts("J. Jogar");
				gotoxy(2, 48);
				puts("A. Abandonar");
				imprimePedras(personagem[HUMANO]);
				gotoxy(2, 41);
				printf("O que deseja fazer? ");
				opc = toupper(_getche());
				if((pesca == 1) && (monte>0)) //habilitar essa opcao apenas se houver pedras no monte e se nao pescou nesse turno
				{                         //ou seja enquanto for permitido pescar
					switch(opc)           //Nesse caso eh impossivel passar a vez
					{
						case 'C':
							while(pesca) //executa enquanto nao pescar uma pedra
							{
								pesca = pescaPedra(&monte, turno, personagem, pedraMte); //se pesca valer 0, realizou a pesca
							}
							//atualiza a qunatidade de pedras no monte
							gotoxy(131, 2);
							printf("%.2d", monte); //formata a saida com dois algarismos
							break;
						case 'J':
							limpaMenus(0, 1, 0); //testar: limpaMenus(1,1,0) -> limpaMenus(msg,mnu,lst)
												 //imprimePedras(personagem[HUMANO]); //comentar, caso usar limpaMenus(1,1,0)
												 //se conseguir realizar a jogada ret sera 0
							ret = deitaPedra(&direc_E, &direc_D, HUMANO, &ptaJogo, personagem);
							if(personagem[HUMANO].quantPedra == 0){
								Sleep(1500);
								acabou = 1;
								ranking(acabou, 'C', personagem, jogaPontos); //calcula os pontos, so grava se alguem atingir FIM
							}
							if(ret == 0) //se a jogada for bem sucedida muda o turno
							{
								turno = MAQUINA;
							}
							break;
						case 'A': //abandona o jogo
							(*cont) = jogarDenovo();
							acabou = 2; //nao passa pelo if no final
							ret = 0; //sai do while do humano
							break;
						default:
							limpaMenus(0, 1, 0); //testar: limpaMenus(1,0,0) -> limpaMenus(msg,mnu,lst)
							gotoxy(20, 45);
							puts("opcao invalida");
							Sleep(1500); //aguarda 1,5seg
							break;
					}
				}
				else //opcoes caso nao seja permitida mais uma pesca/compra
				{
					switch(opc){
						case 'P':
							turno = MAQUINA; //troca o turno e passa a jogada (verificar condicoes permitidas)
							ret = 0; //sai do while do humano
							contaPassa++; //houve uma pesca sem realizar a jogada
							break;
						case 'J':
							limpaMenus(1, 1, 0); //testar: limpaMenus(1,1,0) -> limpaMenus(msg,mnu,lst)
							imprimePedras(personagem[HUMANO]); //comentar, caso usar limpaMenus(1,1,0)
															   //se conseguir realizar a jogada ret sera 0
							ret = deitaPedra(&direc_E, &direc_D, HUMANO, &ptaJogo, personagem);
							if(ret == 0){
								contaPassa = 0; //zera o contador se realizar uma jogada apos comprara a pedra
							}
							if(personagem[HUMANO].quantPedra == 0){
								Sleep(1500);
								acabou = 1;
								ranking(acabou, 'C', personagem, jogaPontos); //calcula os pontos, so grava se alguem atingir FIM
							}
							if(ret == 0) //se a jogada for bem sucedida muda o turno
							{
								turno = MAQUINA;
							}
							break;
						case 'A': //abandona o jogo sem gravar o ranking
							(*cont) = jogarDenovo();
							acabou = 2; //nao passa pelo if no final
							ret = 0; //sai do while do humano
							break;
						default:
							limpaMenus(0, 1, 0); //testar: limpaMenus(1,0,0) -> limpaMenus(msg,mnu,lst)
							gotoxy(20, 45);
							puts("opcao invalida");
							Sleep(1500); //aguarda 1,5seg
							break;
					}
				}
			}
		}
		else{
			ret = 1;
			pesca = 1; //habilita a pesca de pedras
			if(turno == MAQUINA){
				//limpa os menus
				limpaMenus(0, 1, 1); //testar: limpaMenus(0,1,1) -> limpaMenus(msg,mnu,lst)
									 //verificar se tem uma pedra para jogar
									 //se o PC nao tiver uma pedra, devera pescar uma, verificar se e' valida e jogar ou passar
				while(ret == 1){
					//se conseguir realizar a jogada ret sera 0
					ret = deitaPedra(&direc_E, &direc_D, MAQUINA, &ptaJogo, personagem);
					if(ret == 0){
						contaPassa = 0; //zera o contador se realizar uma jogada
					}
					if(((monte == 0) || (pesca == 0)) && (ret == -1)) //pescou e nao fez a jogada -> passa a vez
					{
						gotoxy(6, 48); //pode ser 50,2 ?
						printf("%s passou a vez", personagem[MAQUINA].nome);
						Sleep(1500);
						turno = HUMANO;
						contaPassa++; //incrementa o contador se comprar e nao jogar
						break; //sai do while da maquina
					}
					else //ainda nao comprou uma pedra ou realizou a jogada
					{
						if(ret == -1) //nao fez a jogada e ainda nao pescou
						{
							ret = 1;
							//a maquina compra uma pedra. Se chegou aqui tem pelo menos uma pedra no monte
							gotoxy(2, 46);
							printf("%s esta comprando uma pedra", personagem[MAQUINA].nome);
							Sleep(1500);
							while(pesca) //executa enquanto nao pescar uma pedra
							{
								pesca = pescaPedra(&monte, turno, personagem, pedraMte); //se pesca valer 0, realizou a pesca
							}
							//atualiza a qunatidade de pedras no monte
							gotoxy(131, 2);
							printf("%.2d", monte); //formata a saida com dois algarismos
							gotoxy(126, 41); //depende do nome do oponente
							printf("%.2d", personagem[MAQUINA].quantPedra); //formata a saida com dois algarismos
						}
						else //realizou a jogada, mas pode ter pescado ou nao
						{
							if(ret == 0){
								turno = HUMANO;
							}
						}
					}
				}
				if(personagem[MAQUINA].quantPedra == 0){
					Sleep(1500);
					acabou = 1;
					ranking(acabou, 'C', personagem, jogaPontos); //calcula os pontos, so grava se alguem atingir FIM
				}
			}
			else{
				puts("DEU MERDA.Turno indefinido!");
			}
		}
		if((contaPassa>3) && (monte == 0)) //se os dois jogadores passarem a vez
		{                                //pelo menos uma vez cada e nao houver pedra no monte

			Sleep(2000);
			telaBase();
			gotoxy(10, 30);
			printf("Nao ha mais jogadas possiveis!");
			Sleep(1000);
			gotoxy(15, 35);
			printf("Verificando a pontuacao dos jogadores...");
			Sleep(2000);
			acabou = 1;
			ranking(acabou, 'C', personagem, jogaPontos); //calcula os pontos, so grava se alguem atingir FIM
		}
	}
	return(acabou);
} //fim da funcao jogo

  //cria o historico de jogadas
void ranking(int controle, char cont, struct jogador perdedor[PLAY], RECORDE jogaPontos[PLAY]){
	FILE *grava;
	int i, somaH, somaM;
	somaH = somaM = 0; //inicializa as variaveis

					   //abre o arquivo para adicionar ao final
	grava = fopen("Ranking.dom", "ab");
	if(grava == NULL){
		printf("\n Erro ao abrir o arquivo! Verifique suas permissoes.");
		_getch();
		exit(1);
	}
	else //conseguiu abrir o arquivo
	{
		//caso o humano queira parar de jogar, apos acabar a partida, sem ninguem atingir FIM
		if(cont == '0'){
			if(controle == 2) //humano abandonou a partida antes de acabar e nao vai continuar o jogo
			{
				system("cls");
				gotoxy(45, 20);
				puts("Que feio!!   Nao tem capacidade de jogar ate o fim????");
				Sleep(1000);
				gotoxy(40, 35);
				puts("Gravando os pontos no Hall da Fama ... Aguarde...");
				fwrite(&jogaPontos[HUMANO], sizeof(RECORDE), 1, grava);
				fwrite(&jogaPontos[MAQUINA], sizeof(RECORDE), 1, grava);
				Sleep(2000);
			}
			else //controle == 1 a partida acabou naturalmente
			{
				//grava no arquivo apenas quem tiver pontos (exclui-se 0 pontos)
				if(jogaPontos[HUMANO].pontos != 0){
					fwrite(&jogaPontos[HUMANO], sizeof(RECORDE), 1, grava);
				}
				if(jogaPontos[MAQUINA].pontos != 0){
					fwrite(&jogaPontos[MAQUINA], sizeof(RECORDE), 1, grava);
				}
			}
		}
		else //a partida continuara
		{
			//calcula os pontos
			if(perdedor[HUMANO].quantPedra != 0) //esse jogador morreu com pedras na mao
			{
				for(i = 0; i<perdedor[HUMANO].quantPedra; i++){
					somaH = somaH + perdedor[HUMANO].minhas[i].ladoE + perdedor[HUMANO].minhas[i].ladoD; //soma as pontas das pedras restantes
				}
				jogaPontos[HUMANO].pontos += somaH;
			}
			if(perdedor[MAQUINA].quantPedra != 0) //esse jogador morreu com pedras na mao
			{
				for(i = 0; i<perdedor[MAQUINA].quantPedra; i++){
					somaM = somaM + perdedor[MAQUINA].minhas[i].ladoE + perdedor[MAQUINA].minhas[i].ladoD; //soma as pontas das pedras restantes
				}
				jogaPontos[MAQUINA].pontos += somaM;
			}
			if(cont == 'C'&& controle == 1) //acabou a partida naturalmente
			{

				if((perdedor[MAQUINA].quantPedra != 0) && (perdedor[HUMANO].quantPedra != 0)) //ninguem consegue mais pescar
				{
					telaBase();
					//mostra os pontos e o nome da maquina
					gotoxy(strlen(perdedor[MAQUINA].nome) + 12, 2);
					printf(": %.2d", jogaPontos[MAQUINA].pontos); //formata a saida com dois algarismos
					gotoxy(14, 3);
					printf(" %.2d", jogaPontos[HUMANO].pontos);
					//mensagem
					gotoxy(72, 10);
					printf("O jogo ficou travado! Preste mais a atencao no jogo");
					Sleep(1000);
					gotoxy(45, 23);
					printf("No entanto....");
					Sleep(1000);
				}
				if((jogaPontos[HUMANO].pontos<FIM) && (jogaPontos[MAQUINA].pontos<FIM)) //a partida acabou mas o jogo continua
				{
					if(somaM>somaH) //humano vence
					{
						//mostra os pontos e o nome da maquina
						gotoxy(strlen(perdedor[MAQUINA].nome) + 12, 2);
						printf(": %.2d", jogaPontos[MAQUINA].pontos); //formata a saida com dois algarismos
						gotoxy(14, 3);
						printf(" %.2d", jogaPontos[HUMANO].pontos);
						gotoxy(50, 25);
						puts("Parabens! ");
						Sleep(1000);
						gotoxy(72, 27);
						puts("Voce venceu esta partida! Vamos ver se consegue ganhar o jogo.");
						Sleep(2000);
						gotoxy(45, 30);
						puts("Jogue mais uma partida, se tiver coragem!");
						Sleep(2000);
						Sleep(2000);
					}
					else{
						if(somaH>somaM) //maquina vence
						{
							//mostra os pontos e o nome da maquina
							gotoxy(strlen(perdedor[MAQUINA].nome) + 12, 2);
							printf(": %.2d", jogaPontos[MAQUINA].pontos); //formata a saida com dois algarismos
							gotoxy(14, 3);
							printf(" %.2d", jogaPontos[HUMANO].pontos);
							gotoxy(50, 25);
							puts("Que pena! ");
							Sleep(1000);
							gotoxy(40, 27);
							puts("Essa partida voce perdeu! Nao desanime, ainda pode ganhar o jogo.");
							Sleep(2000);
							gotoxy(72, 30);
							puts("Jogue mais uma partida e mostre quem e' mais esperto!");
							Sleep(2000);
							Sleep(2000);
						}
						else  //houve empate
						{
							gotoxy(50, 25);
							puts("I N C R I V E L ! ");
							Sleep(1000);
							gotoxy(40, 27);
							puts("Voce conseguiu empatar ! ");
							Sleep(2000);
							gotoxy(72, 30);
							puts("Jogue mais uma partida e mostre quem voce e' melhor!");
							Sleep(2000);
							Sleep(2000);
						}
					}
				}
				else //ou o humano ou a maquina ou os dois atingiram FIM pontos
				{
					if(jogaPontos[HUMANO].pontos>jogaPontos[MAQUINA].pontos) //humano perdeu o jogo
					{
						//grava a pontuacao do vencedor no arquivo
						//mostra os pontos e o nome da maquina
						gotoxy(strlen(perdedor[MAQUINA].nome) + 12, 2);
						printf(": %.2d", jogaPontos[MAQUINA].pontos); //formata a saida com dois algarismos
						gotoxy(14, 3);
						printf(" %.2d", jogaPontos[HUMANO].pontos);
						fwrite(&jogaPontos[MAQUINA], sizeof(RECORDE), 1, grava); //grava no arquivo
						gotoxy(50, 25);
						puts("Que pena! ");
						Sleep(1000);
						gotoxy(40, 27);
						puts("Voce perdeu o jogo! Vamos ver se da proxima vez voce aprende a jogar.");
						Sleep(2000);
						gotoxy(72, 30);
						puts("Comece outro jogo e mostre quem e' mais esperto!");
						Sleep(2000);
						Sleep(2000);
					}
					else{
						if(jogaPontos[HUMANO].pontos<jogaPontos[MAQUINA].pontos) //maquina perdeu o jogo
						{
							//grava a pontuacao do vencedor no arquivo
							fwrite(&jogaPontos[HUMANO], sizeof(RECORDE), 1, grava);
							//mostra os pontos e o nome da maquina
							gotoxy(strlen(perdedor[MAQUINA].nome) + 12, 2);
							printf(": %.2d", jogaPontos[MAQUINA].pontos); //formata a saida com dois algarismos
							gotoxy(14, 3);
							printf(" %.2d", jogaPontos[HUMANO].pontos);
							gotoxy(50, 25);
							puts("Parabens! ");
							Sleep(1000);
							gotoxy(72, 27);
							puts("Voce venceu o jogo! Vamos ver se a sua sorte continua.");
							Sleep(2000);
							gotoxy(45, 30);
							puts("Comece outro jogo, se tiver coragem!");
							Sleep(2000);
							Sleep(2000);
						}
						else{
							//mostra os pontos e o nome da maquina
							gotoxy(strlen(perdedor[MAQUINA].nome) + 12, 2);
							printf(": %.2d", jogaPontos[MAQUINA].pontos); //formata a saida com dois algarismos
							gotoxy(14, 3);
							printf(" %.2d", jogaPontos[HUMANO].pontos);
							gotoxy(50, 25);
							puts("Quem disse que era impossivel empatar o jogo????");
							Sleep(2000);
						}
					}
				}
			}
			if(controle == 2 && cont == 'S') //humano abandonou a partida antes de acabar e vai continuar o jogo
			{
				gotoxy(50, 25);
				puts("Vai dizer que nao teve sorte no sorteio!? ");
				Sleep(1000);
				gotoxy(45, 27);
				puts("Eu acho que o problema foi falta de estrategia!! ");
				Sleep(2000);
				jogaPontos[MAQUINA].pontos -= somaM; //nao conta os pontos para a maquina
				if(jogaPontos[HUMANO].pontos >= FIM) //humano perdeu o jogo
				{
					//grava a pontuacao do vencedor no arquivo
					fwrite(&jogaPontos[MAQUINA], sizeof(RECORDE), 1, grava); //grava no arquivo
					gotoxy(40, 29);
					puts("Que pena! ");
					Sleep(1000);
					gotoxy(30, 32);
					puts("Voce perdeu o jogo! Vamos ver se da proxima vez voce aprende a jogar.");
					Sleep(2000);
					gotoxy(52, 34);
					puts("Comece outro jogo e mostre quem e' mais esperto!");
					Sleep(2000);
					Sleep(2000);
				}
			}

		}
	}
	fclose(grava);
} //fim da funcao ranking