#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define CIPHER 'C'
#define DECIPHER 'D'
 

void initializeRotor(unsigned char* s)
{
    for(int i=0; i < 256; i++)
    {
        s[i] = i;
    }    
}

void swap(unsigned char* firstElement, unsigned char* secondElement)
{
    unsigned char tmp = *firstElement;
    *firstElement = *secondElement;
    *secondElement = tmp;
}

void printRotor(unsigned char* arr)
{
    for (int i=0; i<256; i++)
    {
        if(i%16==0 && i!=0)
        {
            printf("\n");
        }
        printf("%03d ", arr[i]);        
    }
}

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

void permutateRotorToCipher(unsigned char* currentState, unsigned char* key, unsigned char* positionsSwaped)
{
    int swapPosition = 0;
    for (int i=0; i<256; i++)
    {
        swapPosition = (swapPosition +
        currentState[i] +  key[i % strlen(key)]) % 256;
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



int main(int argc, char *argv[]){


    return 0;
}