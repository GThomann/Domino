/*
*   Ultima alteracao: 24-08 15h
*
*   Jogo de dominó em modo console
*
*   Autor: Gustavo Luiz Thomann
*   RA: 0040961323019
*
*/

#include<stdlib.h>
#include<stdio.h>
#include<conio.h> // para usar getch()
//#include<string.h>
#include<time.h> //para usar a funcao rand() e srand()
#include<windows.h> //para usar meu gotoxy e SetConsoleTextAttribute()

#include "..\Header\Prototypes.h"


int main()
{
    system("MODE 140,49"); //redimensiona a janela do prompt para largura=140 e altura=49
    system("TITLE DOMINÓ SIMPLES"); //titulo da janela
    //system("color 8F"); //cor da tela (8F) (fundo cinza com caracteres brancos)
    //a linha abaixo faz a mesma coisa que a de cima, porem com mais profissionalismo
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 63); //128 (fundo cinza) + 15(F) do texto branco =143

    struct pedra pedraMonte[PEC]; //cria um array da struct pedra para cadastrar as pecas [28pc]
                                     //exemplo: peca[1] (pedra 1, tem ladoE e ladoD)

    struct jogador personagem[PLAY]; //declaracao dos jogadores
    //declaracao das variaveis de uso comum
    struct pedra ptaJogo; //valores das pontas
    RECORDE pontos[PLAY]; //guarda os pontos dos jogadores
    char  continua, escolha;
    int pedraInicio, pedraH, pedraM, ret, acabou;
    int monte; //numero de pedras restantes no monte
    int turno; //turno =1 ->humano ; turno=0 ->Maquina

    continua='0';
    while(continua=='0')
    {
		mainMenu();
        escolha=toupper(_getche());
        switch(escolha)
        {
        case 'J':
            {
                system("cls");
                gotoxy(60,25);
                puts("B o a  s o r t e !");
                Sleep(2000);
                fflush(stdin);
                continua='S'; //comeca o jogo
                #ifdef _TESTE
                //inicializa pc
                strcpy(personagem[0].nome, "Domino");
                personagem[MAQUINA].idade=36;
                personagem[MAQUINA].quantPedra=0;
                //inicializa o humano
                strcpy(personagem[1].nome, "Humano");
                personagem[HUMANO].idade=30;
                personagem[HUMANO].quantPedra=0;
                //inicializa a pontuacao dos jogadores
                for(ret=0; ret<PLAY; re++)
                {
                    pontos[ret].pontos=0;
                    strcpy(pontos[ret].nome, personagem[ret].nome);
                }
                #else
                //inicializa pc
                criaJogador(MAQUINA,personagem);
                //inicializa o humano
                Sleep(500); //retarda em 500 milisegundos
                criaJogador(HUMANO,personagem);
                //inicializa a pontuacao dos jogadores
                for(ret=0; ret<PLAY; ret++)
                {
                    pontos[ret].pontos=0;
                    strcpy(pontos[ret].nome, personagem[ret].nome);
                }
                #endif // _TESTE
                break;
            } //fim case 'J'
        case 'R':
            {
                //colocar tudo isso num arquivo
                system("cls");
                gotoxy(60,2);
                puts("R E G R A S   D O   J O G O ");
                puts("\n01-) Cada jogagdor recebe 7 pedras sortedas aleatoriamente.");
                puts("\n02-) Comeca o jogo quem possuir a maior pedra com os dois lados iguais (dupla).");
                puts("\n03-) Se ninguem possuir uma dupla, serao realizadas compras sucessivas ate que alguem tenha uma.");
                puts("\n04-) As jogadas deverao se feitas de forma a combinar com os numeros das pontas que estao na mesa.");
                puts("\n05-) Se o jogador da vez nao possuir uma pedra que combine, devera comprar uma. So sera permitida uma compra por turno.");
                puts("\n06-) Se apos realizada a compra o jogador ainda nao possuir uma pedra que combine, este devera passar a vez.");
                puts("\n07-) Caso nao haja mais pedras disponiveis para compra, sera permitido passar a vez.");
                puts("\n08-) Ganha a partida aquele que conseguir colocar todas as pedras na mesa primeiro.");
                puts("\n09-) A pontuacao sera a soma das pontas de todas as pedras restantes na mao do perdedor. Ao ganhador sera atribuido 0 pontos.");
                puts("\n10-) Caso nao tenha mais pedras no monte e ninguem possua uma pedra compativel, a partida sera encerrada e os pontos somados para ambos.");
                printf("\n11-) Perde o jogo aquele que atingir %d pontos nas partidas disputadas", FIM);
                puts("\n\n\n");
                system("pause");
                break;
            } //fim case 'R'
        case 'H':
            {
                system("cls");
				showRanking();
                break;
            } //fim case 'H'
        case 'S':
            {
                system("cls");
                gotoxy(60,25);
                puts("A T E   A   P R O X I M A  !");
                Sleep(2000);
                continua='N';
                break;
            }
        default:
            {
                system("cls");
                gotoxy(60,25);
                printf("Opcao invalida, tente novamente!");
                Sleep(1000);
                break;
            }
        } //switch

		//TODO criar uma ou mais funcoes para essa logica
        while(continua=='S') // continua a jogar
        {
            system("cls");
            //inicializacao das variaveis de jogo
            turno=HUMANO; //comeca a distribuicao das pedras com o humano
            monte=0; //nenhuma pedra no monte ainda
            pedraInicio= EMPTY; //valor padrao para falta da pedra

            personagem[MAQUINA].quantPedra=0;
            personagem[HUMANO].quantPedra=0;
             //iniciando a pedra central verificar como automatizar
            ptaJogo.ladoD= EMPTY; //valor padrao para ausencia
            ptaJogo.ladoE= EMPTY; //valor padrao para ausencia

            //inicializa as pedras do jogo
            criaPedra(&monte, pedraMonte);

            //inicia as pedras dos jogadores
            iniciaPedras(MAQUINA, personagem);
            iniciaPedras(HUMANO, personagem);
            //embaralha as pedras no monte
            embaralhar(pedraMonte);

            //sera necessario pedir para o humano escolher as suas pedras? Fica como opcao para uma outra versao

            //funcao para sortear as pedras
            sortear(&turno, &monte, pedraMonte, personagem);
            //bloco para determinar a primeira pedra a ser jogada
            //verificar quem possui a maior pedra dupla
            pedraH=maiorDuplo(personagem[HUMANO]);
            pedraM=maiorDuplo(personagem[MAQUINA]);
            if(personagem[HUMANO].minhas[pedraH].ladoE!= EMPTY) //garante que o humano tem uma dupla
            {
                //a maquina nao tem uma pedra dupla ou
                //apedra eh menor que a do humano
                if((personagem[MAQUINA].minhas[pedraM].ladoE== EMPTY) ||
                    (personagem[HUMANO].minhas[pedraH].ladoE>personagem[MAQUINA].minhas[pedraM].ladoE))
                {
                    pedraInicio=pedraH;
                    turno=HUMANO;
                }
                else //amaquina tem uma dupla pedra e eh maior que a do humano
                {
                    if(personagem[MAQUINA].minhas[pedraM].ladoE>personagem[HUMANO].minhas[pedraH].ladoE)
                    {
                        pedraInicio=pedraM;
                        turno=MAQUINA;
                    }
                }
            }
            else
            {
                //o humano nao tem uma pedra dupla
                if(personagem[MAQUINA].minhas[pedraM].ladoE!= EMPTY) //guarante que a maquina tem uma dupla
                {
                    pedraInicio=pedraM;
                    turno=MAQUINA;
                }
            }

            //codigo para pescar uma pedra caso ninguem possua uma dupla
            if(pedraInicio== EMPTY)
            {
                printf("\nNinguem possui uma dupla. ");
            }
            ret=1;
            while(pedraInicio== EMPTY)
            {
                printf("\nRealizando compra ate alguem possuir uma...");
                Sleep(300); //retarda em 100 milisegundos
                if(turno==HUMANO)
                {
                    ret=pescaPedra(&monte,HUMANO, personagem, pedraMonte); //pesca uma pedra para o humano
                    if(ret==0) //pescou uma pedra
                    {
                        pedraInicio=maiorDuplo(personagem[HUMANO]); //testa se a pedra pescada eh uma dupla
                        if(pedraInicio== EMPTY)
                        {
                            turno=MAQUINA;
                        }
                    }
                }
                else
                {
                    if(turno==MAQUINA)
                    {
                        ret=pescaPedra(&monte,MAQUINA, personagem, pedraMonte); //pesca uma pedra para a maquina
                        if(ret==0) //pescou uma pedra
                        {
                            pedraInicio=maiorDuplo(personagem[MAQUINA]); //testa se a pedra pescada eh uma dupla
                            if(pedraInicio== EMPTY)
                            {
                                turno=HUMANO;
                            }
                        }
                    }
                    else
                    {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 207);  //fundo vermelho e text0 branco
                        puts("DEU MERDA. Turno indefinido!");
                    }
                }
            }
            //comeca o jogo
            telaBase();
            gotoxy(115 - strlen(personagem[MAQUINA].nome), 41);
            puts(personagem[MAQUINA].nome);
            gotoxy(12, 2);
            printf(personagem[MAQUINA].nome);
            printf(": %.2d", pontos[MAQUINA].pontos);
            gotoxy(14,3);
            printf(" %.2d", pontos[HUMANO].pontos);
            gotoxy(131,2);
            printf("%.2d", monte); //formata a saida com dois algarismos
            Sleep(2000); //aguarda 2 seg
            gotoxy(30,20);
            puts("Quem possuir a maior pedra dupla comeca a partida!");
            Sleep(2000); //aguarda 2 seg
            gotoxy(30,25);
            puts("Verificando...");
            Sleep(500); //aguarda 1 seg
            gotoxy(25,28);
            if(turno==HUMANO)
            {
                printf("\tParabens, %s!\tVoce inicia a partida!", personagem[turno].nome);
            }
            else
            {
                printf("%s comeca a partida. \tBoa sorte!", personagem[turno].nome);
            }
            //fim do bloco para determinar a primeira pedra a ser jogada
            Sleep(2000); //aguarda 2 seg
            telaBase();
            gotoxy(115 - strlen(personagem[MAQUINA].nome), 41);
            printf(personagem[MAQUINA].nome);
            gotoxy(12, 2);
            printf(personagem[MAQUINA].nome);
            printf(": %.2d", pontos[MAQUINA].pontos);
            gotoxy(14,3);
            printf(" %.2d", pontos[HUMANO].pontos);
            gotoxy(131,2);
            printf("%.2d", monte); //formata a saida com dois algarismos
            //jogada inicial
            ptaJogo=personagem[turno].minhas[pedraInicio];
            personagem[turno].minhas[pedraInicio].ladoE=29; //elimina essa pedra do jogador
            personagem[turno].minhas[pedraInicio].ladoD=29; //porque a jogada sera automatica
            personagem[turno].quantPedra--; //remove a pedra do estoque do jogador
            //as coordenadas de inicio (centro da tela a meia altura)
            ptaJogo.ladoEx=62;
            ptaJogo.ladoEy=5;
            ptaJogo.ladoDx=78;
            ptaJogo.ladoDy=5;
            //troca o turno pois quem tem a maior dupla faz a jogada inicial automaticamente
            if(turno==HUMANO)
            {
                turno=MAQUINA;
            }
            else
            {
                if(turno==MAQUINA)
                {
                    turno=HUMANO;
                }
                else
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 207);  //fundo vermelho e text0 branco
                    puts("DEU MERDA! Turno indefinido");
                }
            }
            Sleep(800); //aguarda 0,8 seg
            //desenha a pedra inicial. Devera ser o maior duplo do jogo N=normal, I=invertido
            desenhaPedra('N', ptaJogo,ptaJogo.ladoEx,ptaJogo.ladoEy);
            Sleep(1000); //aguarda 1 seg
            //executa enquanto ambos estiverem com pelo menos 1 pedra
            acabou=jogo(&continua, monte, turno, ptaJogo, personagem, pedraMonte, pontos);
            //verifica se comeca novo jogo
            if(acabou==1)
            {
                if((pontos[HUMANO].pontos<FIM) && (pontos[MAQUINA].pontos<FIM)) //ainda ninguem atingiu FIM pontos
                {
                    continua=jogarDenovo();
                    if(continua=='0') //humano nao quer jogar nova partida e retorna ao menu principal
                    {
                        ranking(acabou, continua, personagem, pontos); //grava a pontuacao
                    }
                }
                else //alguem atingiu FIM
                {
                    continua='0'; //retorna ao menu principal
                }
            }
            else
            {
                if(acabou==2) //humano abandonou a partida
                {
                    ranking(acabou, continua, personagem, pontos); //grava a pontuacao atual
                    if((pontos[HUMANO].pontos>=FIM))
                    {
                        continua='0'; //volta ao menu principal
                    }
                }
                else
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 207);  //fundo vermelho e text0 branco
                    puts("DEU MERDA! Final indefinido");
                }
            }
        }
    }
    return(0);
} // fim da funcao main()
