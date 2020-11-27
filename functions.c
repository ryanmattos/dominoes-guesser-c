//
// Created by Ryan on 17/11/2020.
//
#include "functions.h"
#include "pieces.h"
#include <stdio.h>
#include <stdlib.h>

dPiece * readFile(){
    FILE *fp;
    dPiece *pieces;
    dDescriptor *descriptor;
    pieces = NULL;

    descriptor = (dDescriptor *) malloc(sizeof(dDescriptor));
    descriptor->beg = descriptor->end = NULL;

    int n, i = 0;

    fp = fopen("C:\\Users\\Ryan\\Desktop\\jogo.txt", "r");

    if (fp == NULL) {
        printf("Cannot open file \n");
        exit(0);
    }

    fscanf(fp, "%d\n", &n);

    while (!feof(fp)) {
        dPiece *peca;
        peca = (dPiece *) malloc(sizeof(dPiece));
        fscanf(fp, "%d\t%d", &peca->x, &peca->y);

        descriptor->beg = peca;
        if(descriptor->end == NULL)
            descriptor->end = peca;

        peca->prox = pieces;
        pieces = peca;
        i++;
    }

    descriptor->size = i;

    printf("Pieces ready to be used!\n");

    return pieces;

    //printf("numero de pecas: %d\n", n);

    //for(i = 0; i < n; i++) {
        //printf("peca #%d: %d %d\n", i+1, pecas[i].x, pecas[i].y);
    //}
}

void printPieces(dPiece *pieces){
    dPiece *temp = pieces;

    while(temp != NULL){
        printf("%d %d\n", temp->x, temp->y);
        temp = temp->prox;
    }
}

dPiece * checkGame(dPiece *pieces){
    dPiece *result;
    dPiece *temp = pieces;

    if(temp != NULL && temp->prox != NULL) {
       if(temp->x == temp->prox->y || temp->x == temp->prox->x){
           printf("%d|%d %d|%d\n", temp->x, temp->y, temp->prox->x, temp->prox->y);
       }
       temp = temp->prox;
       return checkGame(temp);
    } else {
        return 0;
    }
}