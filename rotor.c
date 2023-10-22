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



int main(int argc, char *argv[]){

   
    return 0;
}