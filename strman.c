#include "strman.h"

int replace(char *src, int len, char *old, int len0, char *new, int len1, char *dest)
{
    int index=0, i=0;
    int count = 0;

    for(i=0; i<len; i++)
    {
        int i1 = 0;
        bool found = true;
        while(*(src+i+i1) == *(old+i1))
        {
            i1++;
        }
        if(i1 == len0)
        {
            count++;
            i += len0 - 1;
        }
    }

    int length = len + count * (len1 - len0) + 1;
    dest = (char*)realloc(dest, length);

    for(index=0, i=0; index<length-1; index++, i++)
    {
        int i1 = 0;
        bool found = true;
        while(*(src+i+i1) == *(old+i1))
        {
            i1++;
        }
        if(i1 == len0)
        {
            for(int j=0; j<len1; j++)
            {
                *(dest+index+j) = *(new+j);
            }
            index += len1 - 1;
            i += len0 - 1;
        }
        else 
        {
            *(dest+index) = *(src+i);
        }
    }

    *(dest+length-1) = '\0';
    return length;
}
