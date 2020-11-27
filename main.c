#include <stdio.h>
#include <stdlib.h>
#include "tasks.h"
#include "functions.h"
#include "pieces.h"

int main(){
    dPiece *pecas;

    //mostra o menu do programa
    menu();
    //funcao que faz o processamento da opcao escolhida
    //chooseTask();

    pecas = readFile();
    printPieces(pecas);
    checkGame(pecas);
    return 0;
}