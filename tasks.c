//
// Created by Ryan on 17/11/2020.
//
#include "tasks.h"
#include "functions.h"
#include <stdio.h>

void menu(){
    printf("------------------MENU------------------\n");
    printf("1 - Ler os dados\n2 - Verificar resultado\n3 - Imprimir resultado\n");
    printf("0 - Sair\nEscolha uma opcao\n");
    printf("----------------------------------------\n");
}

void chooseTask() {
    int option;

    scanf("%d", &option);

    while(option < 0 || option > 3){
        printf("Voce nao selecionou uma opcao valida\n");
        scanf("%d", &option);
    }

    switch (option) {
        case 1:
            printf("Voce selecionou ler os dados\n");
            readFile();
            break;
        case 2:
            printf("Voce selecionou verificar resultado\n");
            break;
        case 3:
            printf("Voce selecionou imprimir resultado\n");
            break;
        case 0:
            printf("Voce selecionou sair\n");
            break;
    }
}