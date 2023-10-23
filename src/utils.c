#include "headers/utils.h"

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
