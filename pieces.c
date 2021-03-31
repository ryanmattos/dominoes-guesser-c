//
// Created by Ryan on 17/11/2020.
//
#include "pieces.h"
#include <stdio.h>
#include <stdlib.h>

dPiece * createPiece(dPiece **piece, int x, int y, int isRotated){
    *piece = (dPiece *) malloc(sizeof(dPiece));
    (*piece)->x = x;
    (*piece)->y = y;
    (*piece)->rotatedFlag = isRotated;
    (*piece)->next = NULL;
    (*piece)->prev = NULL;
}

