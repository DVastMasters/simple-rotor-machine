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

    /* EXECUTION MODE: CIPHER OR DECIPHER */
    char mode = CIPHER;
    int qttRotors;
    rotor rotors[5];
    /* INPUT FILE */
    char* inputFileName;
    /* OUTPUT FILE */
    char* outputFileName;

    if (argc < 8)
    {
        printf("Usage: %s mode n key1 key2 keyn k1 l1 k2 l2 kn ln input output", argv[0]);
        return 1;
    }    

    if (strcmp(argv[1], "D") == 0)
    {
        mode = DECIPHER;        
    }   

    qttRotors = strtol(argv[2], NULL, 10);

    if (qttRotors < 1 || qttRotors > 5)
    {
        printf("The quantity of rotors must be a number between 1 and 5.");
        return 2;
    }

    int currentArg = 3;    
    unsigned int swapAfterQttCipher = 0;
    unsigned char qttPosToRotate = 0;
    for(int i=0; i<qttRotors; i++)
    {
        strncpy(rotors[i].key, argv[currentArg], 256);
        swapAfterQttCipher = strtol(argv[currentArg + qttRotors + i], NULL, 10);
        if(swapAfterQttCipher > pow(10, 9))
        {
            swapAfterQttCipher = pow(10, 9);
        }
        else if(swapAfterQttCipher < 1)
        {
            swapAfterQttCipher = 1;
        }
        rotors[i].swapAfterQttCipher =  swapAfterQttCipher;

        qttPosToRotate = strtol(argv[currentArg + qttRotors + i + 1], NULL, 10);
        if(qttPosToRotate > 255)
        {
            qttPosToRotate = 255;
        }
        else if(qttPosToRotate < 0)
        {
            qttPosToRotate = 0;
        }        
        rotors[i].qttPosToRotate = qttPosToRotate;
        rotors[i].qttPosRotated = 0;

        initializeRotor(rotors[i].currentState);
        permutateRotorToCipher(rotors[i].currentState, rotors[i].key, rotors[i].positionsSwaped);    
        if (mode == DECIPHER)
        {
            permutateRotorToDecipher(rotors[i].currentState, rotors[i].positionsSwaped);
        }
        
        // printf("\n -- ROTOR %d -- ", i+1);
        // printf("\nkey: %s", rotors[i].key);
        // printf("\nk: %d", rotors[i].swapAfterQttCipher);
        // printf("\nl: %d", rotors[i].qttPosToRotate);

        printf("\n\n");    
        printf("%c %d %s %d %d\n", mode, i+1, rotors[i].key, rotors[i].swapAfterQttCipher, rotors[i].qttPosToRotate);
        printRotor(rotors[i].currentState);

        currentArg++;
    } 

    inputFileName = argv[currentArg+(2*qttRotors)];
    outputFileName = argv[currentArg+(2*qttRotors)+1];


    FILE* inputFile = fopen(inputFileName, "rb");
    if(inputFile==NULL)
    {
        printf("\n\nInput file doesn't exists.");
        return 3;
    }
    FILE* outputFile = fopen(outputFileName, "w+b");
    
    int byteRead = fgetc(inputFile);
    unsigned char byteToWrite;
    int qttBytesCiphered = 0;
    while(byteRead!=EOF)
    {
        qttBytesCiphered++;
        //printf("\n\n--- NEW ITERATION TO CIPHER OR DECIPHER THE CHAR: %c (%d) ---", byteRead, byteRead);
        byteToWrite = byteRead;
        if(mode == CIPHER)
        {
            for(int i=0; i<qttRotors; i++)
            {
                byteToWrite = rotors[i].currentState[(byteToWrite + rotors[i].qttPosRotated) % 256];
                //printf("\n Rotor %d (Qtt Pos Rotated: %d; swapAfterQttCipher: %d; intToWrite: %d; charToWrite: %c", i+1, rotors[i].qttPosRotated, rotors[i].swapAfterQttCipher, byteToWrite,  byteToWrite);
                if((qttBytesCiphered % rotors[i].swapAfterQttCipher) == 0)
                {
                    rotors[i].qttPosRotated += rotors[i].qttPosToRotate;
                }
            }
        }
        else
        {
            for(int i=qttRotors-1; i>=0; i--)
            {
                byteToWrite = (rotors[i].currentState[byteToWrite] - rotors[i].qttPosRotated) % 256;
                //printf("\n Rotor %d (Qtt Pos Rotated: %d; swapAfterQttCipher: %d; intToWrite: %d; charToWrite: %c", i+1, rotors[i].qttPosRotated, rotors[i].swapAfterQttCipher, byteToWrite, byteToWrite);
                if((qttBytesCiphered % rotors[i].swapAfterQttCipher) == 0)
                {
                    rotors[i].qttPosRotated += rotors[i].qttPosToRotate;
                }
            }
        }

        fputc(byteToWrite, outputFile);
        byteRead = fgetc(inputFile);
    }

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}