/*
*   Ultima alteracao: 24-08 15h
*
*   Jogo de dominó em modo console
*
*   Autor: Gustavo Luiz Thomann
*
*
*/

/****** DEFINITION OF ALL FUNCTIONS RELATED TO THE GAME FILE ACCESS ******/

#include<stdlib.h>
#include<stdio.h>
#include<windows.h> //para usar meu gotoxy, SetConsoleTextAttribute() e Sleep()

#include "..\Header\Prototypes.h"

void showRanking(){
	//TODO rever a forma de pegar os historicos
	int i, j;
	int blocos = 0;

	//o arquivo tera no maximo 20 pontuacoes
	RECORDE topDez[20], aux; //cria um array para ate 20 pontuacoes
							 //define um ponteiro para o arquivo
	FILE *leitura;
	//abre o arquivo para leitura binaria
	leitura = fopen("Ranking.dom", "rb");
	if(leitura == NULL){
		gotoxy(40, 25);
		printf("Ainda nao ha informacoes sobre isso. Jogue uma partida primeiro!");
		Sleep(2000); //aguarda 2 seg.
	}
	else{
		//copia os parametros do arquivo para os arrays
		printf("\nLendo o ranking do arquivo... \n");
		Sleep(1500);
		j = 0; //primeiro indice
		blocos = fread(&topDez[j], sizeof(RECORDE), 1, leitura); //le um bloco de cada vez
		while(!feof(leitura)){   //lendo um por um
			j = blocos;
			blocos += fread(&topDez[j], sizeof(RECORDE), 1, leitura); //le um bloco de cada vez e incrementa blocos
			if(j == 20) //limite do array
			{
				break;
			}
		}
		fclose(leitura);
	}

	if(blocos > 0){
		//reorganizando em ordem crescente
		//ordenando
		for(i = 0; i<blocos; i++){
			for(j = i + 1; j<blocos; j++){
				if(topDez[i].pontos>topDez[j].pontos){
					//trocando toda a struct de posicao
					aux = topDez[i];
					topDez[i] = topDez[j];
					topDez[j] = aux;
				}
			}
		}
		//mostrando o ranking
		system("cls");
		printf("\nOs dez melhores neste jogo... \n\n");
		if(blocos <= 10){
			for(i = 0; i<blocos; i++){
				printf("%15s....%.2d\n", topDez[i].nome, topDez[i].pontos);
			}
		}
		else //mostra apenas os 10 melhores
		{
			for(i = 0; i<blocos; i++){
				printf("%15s....%.2d\n", topDez[i].nome, topDez[i].pontos);
			}
			//regrava o arquivo com apenas 10 pontuacoes
			leitura = fopen("Ranking.dom", "wb"); //abre para gravacao sobrescrevendo o antigo
			if(leitura == NULL){
				gotoxy(40, 25);
				printf("Erro na gravacao do arquivo, verifique suas permissoes");
				exit(1);
				//break;
			}
			else{
				fwrite(&topDez, sizeof(RECORDE), 10, leitura);
			}
			fclose(leitura);
		}
	}
	

	printf("\n\n");
	system("pause");
}