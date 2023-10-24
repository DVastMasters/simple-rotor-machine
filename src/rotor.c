#include "headers/rotor.h"

void initializeRotor(unsigned char* s)
{
    for(int i=0; i < 256; i++)
    {
        s[i] = i;
    }    
}

void permutateRotorToCipher(unsigned char* currentState, unsigned char* key, unsigned char* positionsSwaped)
{
    int swapPosition = 0;
    for (int i=0; i<256; i++)
    {
        swapPosition = (swapPosition +
        currentState[i] +  key[i % strlen((char *)key)]) % 256;
        positionsSwaped[i] = swapPosition;
        swap(&currentState[i], &currentState[swapPosition]);
    }
}

void permutateRotorToDecipher(unsigned char* currentState, unsigned char* positionsSwaped)
{
    initializeRotor(currentState);
    int positionToSwap;
    for (int i=255; i>=0; i--)
    {
        positionToSwap = positionsSwaped[i];
        swap(&currentState[i], &currentState[positionToSwap]);
    }
}

