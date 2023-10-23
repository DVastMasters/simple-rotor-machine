#include "headers/rotor.h"

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
        strncpy((char *)rotors[i].key, argv[currentArg], 256);
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
