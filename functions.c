//
// Created by Ryan on 17/11/2020.
//
#include "functions.h"
#include "pieces.h"
#include <stdio.h>
#include <stdlib.h>

dPiece * readFile(dDescriptor **descriptor){
    FILE *fp;
    dPiece *pieces;
    pieces = NULL;

    //cria um descritor e seta ele como nulo
    *descriptor = (dDescriptor *) malloc(sizeof(dDescriptor));
    (*descriptor)->beg = (*descriptor)->end = NULL;

    int n, i = 0;

    //abre o arquivo do jogo
    fp = fopen("jogo.txt", "r");

    if (fp == NULL) {
        printf("Cannot open file \n");
        exit(0);
    }

    //pula a primeira linha (numero de pecas)
    fscanf(fp, "%d\n", &n);

    while (!feof(fp)) {
        //cria um nó para cada peca no arquivo
        dPiece *peca;
        peca = (dPiece *) malloc(sizeof(dPiece));
        fscanf(fp, "%d\t%d", &peca->x, &peca->y);

        (*descriptor)->beg = peca;
        if((*descriptor)->end == NULL)
            (*descriptor)->end = peca;

        //cria uma flag para dizer se a peca esta rotacionada
        peca->rotatedFlag = 0;

        //adiciona a peca no final
        peca->next = pieces;
        if(peca->next)
            peca->next->prev = peca;
        peca->prev = NULL;
        pieces = peca;
        i++;
    }

    (*descriptor)->size = i;

    return pieces;
}

void printPieces(dPiece *pieces){
    dPiece *temp = pieces;

    while(temp != NULL){
        if(!temp->rotatedFlag)
            printf("%d|%d ", temp->x, temp->y);
        //se a peca estiver invertida, imprime ela invertida e insere um * no final
        else {
            printf("%d|%d* ", temp->y, temp->x);
        }
        temp = temp->next;
        if(temp != NULL)
            printf("-> ");
    }

    printf("\n");
}

dPiece * checkGame(dPiece *pieces, dDescriptor *descriptor){
    //cria as variaveis necessarias;
    //currentPiece - armazena os dados da peca atual para inseri-la na lista de resultado
    //firstPiece - armazena a primeira peca da tentativa, caso a tentativa nao for valida
    //blacklist - lista que recebe as primeiras pecas de tentativas falhas

    dPiece *result = NULL,  *currentPiece = NULL, *firstPiece = NULL;
    dPiece *blackList = NULL;
    dDescriptor *resultDescriptor = NULL;
    dDescriptor *blackListDescriptor = NULL;
    dPiece *temp = pieces;

    //lastPiece - armazena o ultimo lado da peca no jogo
    //wasRotated - flag pra verificar se a primeira peca foi tentada dos dois lados
    //skipped - flag para pular caso uma peca ja foi usada no comeco, ou ja foi utilizada na tentativa atual
    int lastPiece = 0, wasRotated = 0, skipped;
    int currentPieceX = 0, currentPieceY = 0;

    //zera os descritores
    clearDescriptor(&resultDescriptor);
    clearDescriptor(&blackListDescriptor);

    //enquanto a lista de resultado for menor que a lista de pedras
    while(resultDescriptor->size < descriptor->size) {
        skipped = 0;
        //verifica se eh a primeira peca a ser usada na tentativa atual, se sim, executa o codigo
        if(!result){
            //se a peca nao foi achada na black list
            if(!foundOnList(temp, blackList)){
                //testa as duas posicoes da primeira peca
                //se a peca nao foi rotacionada ainda, executa o codigo
                if(!wasRotated){
                    currentPieceX = temp->x;
                    currentPieceY = temp->y;
                    lastPiece = temp->y;
                    createPiece(&currentPiece, currentPieceX, currentPieceY, 0);
                    firstPiece = currentPiece;
                    //adiciona a nova peça à lista resultado
                    addToList(currentPiece, &result, &resultDescriptor);
                    //printf("primeira peca: %d|%d\n", currentPieceX, currentPieceY);
                } else {
                    currentPieceX = temp->x;
                    currentPieceY = temp->y;
                    lastPiece = temp->x;
                    createPiece(&currentPiece, currentPieceX, currentPieceY, 1);
                    firstPiece = currentPiece;
                    //adiciona a nova peça à lista resultado
                    addToList(currentPiece, &result, &resultDescriptor);
                    //printf("primeira peca: %d|%d\n", currentPieceY, currentPieceX);
                }
            //se a peca foi achada na black list, pula para a proxima
            } else {
                skipped = 1;
                //printf("peca %d|%d encontrada na blacklist\n", temp->x, temp->y);
                temp = temp->next;
            }
        //verifica se a peca ja foi usada na tentativa atual
        } else if(!foundOnList(temp, result)) {
            //testa ambos os lados da peca
            if (temp->x == lastPiece){
                currentPieceX = temp->x;
                currentPieceY = temp->y;
                lastPiece = temp->y;
                createPiece(&currentPiece, currentPieceX, currentPieceY, 0);
                //adiciona a nova peça à lista resultado
                addToList(currentPiece, &result, &resultDescriptor);
                //printf("valor x igual: %d|%d\n", currentPieceX, currentPieceY);
            } else if (temp->y == lastPiece) {
                currentPieceX = temp->x;
                currentPieceY = temp->y;
                lastPiece = temp->x;
                createPiece(&currentPiece, currentPieceX, currentPieceY, 1);
                //adiciona a nova peça à lista resultado
                addToList(currentPiece, &result, &resultDescriptor);
                //printf("valor y igual: %d|%d\n", currentPieceY, currentPieceX);
            //se a peca nao se encaixar, pula para a proxima
            } else {
                skipped = 1;
                //printf("peca %d|%d nao se encaixa\n", temp->x, temp->y);
                temp = temp->next;
            }
        //se a peca ja tiver sido utilizada ou estiver na black list, pula para a proxima
        } else {
            skipped = 1;
            temp = temp->next;
        }

        //se a flag skipped nao existir, volta para o comeco da lista
        if(!skipped){
            temp = descriptor->beg;
        }

        //se a blacklist tiver todos os elementos da lista principal
        if(blackListDescriptor->size == descriptor->size) {
            return NULL;
        }

        //se for o ultimo item da lista e ainda nao tiver um resultado
        if(temp == NULL && resultDescriptor->size < descriptor->size) {
            //se a peca ja foi rotacionada, adiciona primeira peca a blacklist
            if(wasRotated){
                //printf("Peca testada em todas as posicoes\nAdicionando a blacklist...\n");
                wasRotated = 0;
                currentPieceX = firstPiece->x;
                currentPieceY = firstPiece->y;
                createPiece(&currentPiece, currentPieceX, currentPieceY, 1);
                addToList(currentPiece, &blackList, &blackListDescriptor);
            } else {
                //printf("rotacionando a peca e testando novamente...\n");
                wasRotated = 1;
            }

            //volta para o inicio da lista e limpa os descritores
            temp = descriptor->beg;
            clearDescriptor(&resultDescriptor);
            clearList(&result);
        }
    }

    //printf("Loop finalizado!\n");
    return result;
}

void clearList(dPiece **list){
    dPiece *t;

    //limpa uma lista passada
    while(*list != NULL) {
        t = (*list)->next;
        free(*list);
        *list = t;
    }

    *list = NULL;
}

void clearDescriptor(dDescriptor **desc){
    //se o descritor ja tiver sido criado, apenas modifica os valores
    if(*desc == NULL)
        *desc = (dDescriptor *) malloc(sizeof(dDescriptor));

    (*desc)->size = 0;
    (*desc)->beg = NULL;
    (*desc)->end = NULL;
}

int foundOnList(dPiece *piece, dPiece *list) {
    dPiece *t;
    t = list;

    //retorna 1 se achar a peca dada em uma lista
    while(t != NULL) {
        if(piece->x == t->x && piece->y == t->y)
            return 1;
        t = t->next;
    }

    return 0;
}

void addToList(dPiece *currentPiece, dPiece **list, dDescriptor **listDescriptor) {
    //se for o primeiro item da lista adiciona direto, se nao vai até o ultimo item da lista
    //e seta o proximo com o item criado
    if(*list == NULL){
        *list = currentPiece;
    } else {
        while((*list)->next != NULL)
            *list = (*list)->next;
        (*list)->next = currentPiece;

        //vai para o começo da lista
        *list = (*listDescriptor)->beg;
    }

    (*listDescriptor)->size++;
    (*listDescriptor)->end = currentPiece;

    //se o começo do descritor estiver vazio (nenhum item na lista) seta o primeiro item
    if((*listDescriptor)->beg == NULL)
        (*listDescriptor)->beg = currentPiece;
}
