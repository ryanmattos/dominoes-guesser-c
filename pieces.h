//
// Created by Ryan on 17/11/2020.
//

#ifndef PIECES_H
#define PIECES_H

typedef struct piece {
    int x, y;
    struct piece *prox;
} dPiece;

typedef struct {
    int size;
    dPiece *beg;
    dPiece *end;
} dDescriptor;

#endif //PIECES_H
