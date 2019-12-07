/*
          TRABALHO PRATICO
 CURSO: 		       CIÊNCIA DA COMPUTAÇÃO
 OBJETIVO: 		       CAMPO MINADO DESENVOLVIDO NA LINGUAGEM C
 DISCIPLINA:		   INTROCUÇÃO A PROGRAMAÇÃO
 PROFESSORES: 		   TULIO ANGELO MACHADO TOFFOLO E PUCA HUACHI VAZ PENNA
 DESENVOLVIDO POR:     ENYA LUÍSA GOMES DO SANTOS
 PERIODO:              1º PERIODO
*/

#include "campoMinado.h"

int main(int argc, char *argv[])
{
    Campo jogo;    
    char acao[20];
    char jogarN;
    int linha, coluna;                                  //Variaveis que irão receber a coordenada digitada pelo úsuario
              
    if(confereArgumento(argc, argv) == 1){
        printf(RED("Erro -  Extensão do arquivo invalida. Tente novamente")"\n\a");
        return 1;
    }
    mensagemInicial();
    system("clear");
    do{
        jogo.pontos = 0 ;
        if(argc == 2){
            abreArquivo(argv[1], &jogo);
            preencheSaida(&jogo);
            
        }else if(argc == 3){
            abreSalvo(argc, argv, &jogo);
            //Inicia as variaveis linha e coluna com alguem valor que não inferfira no jogo salvo
            do{
                linha = rand() % jogo.linhas;
                coluna = rand() % jogo.colunas;
            }while(jogo.entrada[linha][coluna] == '-' || jogo.entrada[linha][coluna] == '*');
        }else if(argc == 1){ 
            defineDificuldade(&jogo);
            preencheSaida(&jogo);
            geraAleatorio(&jogo);
            system("clear");
        }
        do{
            menuJogada();
            imprimeCampo(jogo);
            center(jogo.colunas);
            printf("PONTUAÇÃO: %d   ", jogo.pontos);
            if(jogo.bandeiras <= 0){
                printf("BANDEIRAS: ");
                printf(RED("**Sem bandeiras") "\n");
            }else
                printf("BANDEIRAS: %d\n", jogo.bandeiras);
            if(argc != 3){
                jogada(acao, &jogo, &linha, &coluna);
                system("clear");
            }
            //Confere se o jogador ganhou o jogo
            if(jogo.pontos == ((jogo.linhas * jogo.colunas) - jogo.bombas) && strcmp(acao, "resolver") != 0){  //Confere se o úsuario ganhou o jogo
                system("clear");
                win();
                imprimeCampo(jogo);
                break;
            }
            //Confere se o jogador escolheu o comado resolver
            if(strcmp(acao, "resolver") == 0){
                imprimeCampo(jogo);
                break;
            }
            //Confere se o jogador perdeu o jogo
            if(jogo.entrada[linha][coluna] == 'x' && strcmp(acao, "x") != 0 && strcmp(acao, "salvar") != 0){
                system("clear");
                gameover();
                imprimeCampo(jogo);
                break;
            }
            if(argc == 3){
                jogada(acao, &jogo, &linha, &coluna);
                system("clear");
            }
        }while(strcmp(acao, "sair") != 0);
        if(strcmp(acao, "sair") == 0)
            return 1;
        desalocaMatrizes(&jogo);
        printf("\n");
        center(jogo.colunas);
        jogarNovamente(&jogarN);
        system("clear");
    }while(jogarN == 'S');
    return 0;
}
