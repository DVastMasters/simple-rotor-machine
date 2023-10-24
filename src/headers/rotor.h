#ifndef ROTOR_H
#define ROTOR_H
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"
#define CIPHER 'C'
#define DECIPHER 'D'

typedef struct
{
    /* STORE THE CURRENT PERMUTATION OF THE ROTOR */
    unsigned char currentState[256];
    /* STORE THE KEY TO INITIALIZE THE ROTOR (0-255) */
    unsigned char key[256];
    /* k = THE NUMBER OF CIPHERS NECESSARY TO ROTATE THIS ROTOR (1-4,294,967,295) */
    unsigned int swapAfterQttCipher;
    /* l = THE NUMBER OF ROTATIONS MADE AT EVERY ROTATION (0-255) */
    unsigned char qttPosToRotate;
    /* STORE THE CURRENT NUMBER OF ROTATIONS */
    int qttPosRotated;
    /* STORE ALL POSITIONS SWAPED AT FIRST PERMUTATION */
    unsigned char positionsSwaped[256];
} rotor;

void initializeRotor(unsigned char* s);
void permutateRotorToCipher(unsigned char* currentState, unsigned char* key, unsigned char* positionsSwaped);
void permutateRotorToDecipher(unsigned char* currentState, unsigned char* positionsSwaped);

#endif
