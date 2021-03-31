//
// Created by Ryan on 17/11/2020.
//

#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "pieces.h"

dPiece * readFile(dDescriptor **descriptor);

void printPieces(dPiece *pieces);

dPiece * checkGame(dPiece *pieces, dDescriptor *descriptor);

void clearList(dPiece **list);

void clearDescriptor(dDescriptor **desc);

int foundOnList(dPiece *piece, dPiece *list);

void addToList(dPiece *currentPiece, dPiece **list, dDescriptor **listDescriptor);

#endif //FUNCTIONS_H
