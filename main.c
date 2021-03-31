#include <stdio.h>
#include <stdlib.h>
#include "tasks.h"
#include "functions.h"
#include "pieces.h"

int main(){
    dPiece *pecas, *result = NULL;
    dDescriptor *descriptor;

    int option;

    do {
        menu();

        scanf("%d", &option);

        switch (option) {
            case 1:
                pecas = readFile(&descriptor);
                if(pecas) {
                    printf("Arquivos lidos com sucesso!\n");
                } else {
                    printf("Houve um problema ao ler o arquivo. Verifique a integridade do arquivo e tente novamente!\n\n");
                }
                break;
            case 2:
                result = checkGame(pecas, descriptor);
                if(result != NULL)
                    printf("Hmm, encontrei uma maneira de ganhar esse jogo!\n");
                else
                    printf("Sinto muito, nao ha possibilidade de ganhar com esse jogo...\n");
                break;
            case 3:
                if(result == NULL) {
                    printf("Sem possibilidades de vitoria. Tente montar outro jogo!\n");
                } else {
                    printf("\nPara ganhar esse jogo basta fazer os seguintes movimentos:\n");
                    printf("(* significa que a peca foi rotacionada)\n\n");
                    printPieces(result);
                }
                break;
            case 0:
                printf("Voce selecionou sair\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while(option > 0 && option < 4);

    return 0;
}