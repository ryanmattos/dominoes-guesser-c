//
// Created by Ryan on 17/11/2020.
//

#ifndef PIECES_H
#define PIECES_H

typedef struct piece {
    int x, y;
    int rotatedFlag;
    struct piece *prev;
    struct piece *next;
} dPiece;

typedef struct {
    int size;
    dPiece *beg;
    dPiece *end;
} dDescriptor;

dPiece * createPiece(dPiece **piece, int x, int y, int isRotated);

#endif //PIECES_H
