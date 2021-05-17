#include "strman.h"

int replace(char *src, int len, char *old, int len0, char *new, int len1, char *dest)
{
    int index=0, i=0;
    int count = 0;

    for(i=0; i<len; i++)
    {
        int i1 = 0;
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
    //return length - 1;
    return length;
}

int split_to_two_sstruct(struct String src, int index, struct String *str0, struct String *str1)
{
    //printf("strman.c:\n\tsrc: %s\n\tstr0: %s\n\tstr1: %s\n\n", src.charray, str0->charray, str1->charray); // DEBUG
    if (index > src.length)
    {
        return -1;
    }

    str0->charray = (char*)realloc(str0->charray, sizeof(char) * index);
    str0->length = index;
    str1->charray = (char*)realloc(str1->charray, sizeof(char) * (src.length - index));
    str1->length = src.length - index;

    for (int i=0; i < str0->length; i++) 
    {
        *(str0->charray + i) = *(src.charray + i);
    }

    for (int i=0; i < str1->length; i++) 
    {
        *(str1->charray + i) = *(src.charray + index + i);
    }
    
    //printf("strman.c:\n\tsrc: %s\n\tstr0: %s\n\tstr1: %s\n\n", src.charray, str0->charray, str1->charray); // DEBUG
    return index;
}

int test_length_of_array_before_split_string(struct String str, struct String symbols)
{
    int count = 0;
    
    for(int i=0; i<str.length; i++)
    {
        int i1 = 0;
        while(*(str.charray+i+i1) == *(symbols.charray+i1))
        {
            i1++;
        }
        if(i1 == symbols.length)
        {
            count++;
            i += symbols.length - 1;
        }
    }

    return count + 1;
}

int split_into_string_array(struct String str, struct String symbols, struct String *str_array)
{
    int length = test_length_of_array_before_split_string(str, symbols);
    
    int *head = (int*)malloc(sizeof(int) * length);
    int *tail = (int*)malloc(sizeof(int) * length);
    *(head) = 0;
    *(tail+length-1) = str.length;
    
    int count = 0;
    for(int i=0; i<str.length; i++)
    {
        int i1 = 0;
        while(*(str.charray+i+i1) == *(symbols.charray+i1))
        {
            i1++;
        }
        if(i1 == symbols.length)
        {
            count++;
            *(tail+count-1) = i;
            *(head+count) = i + i1;
            //printf("%d\t%d\n", *(head+count-1), *(tail+count-1)); // DEBUG
            i += symbols.length - 1;
        }
    }
    //printf("%d\t%d\n", *(head+length-1), *(tail+length-1)); // DEBUG

    str_array = (struct String *)realloc(str_array, sizeof(struct String) * length);
    for(int i=0; i<length; i++)
    {
        (str_array+i)->charray = (char*)realloc((str_array+i)->charray, sizeof(char) * 1);
        (str_array+i)->length = 1;
    }
    
    struct String s0, s1, s2;
    s0.charray = (char*)malloc(sizeof(char) * 1);
    s0.length = 1;
    s1.charray = (char*)malloc(sizeof(char) * 1);
    s1.length = 1;
    s2.charray = (char*)malloc(sizeof(char) * 1);
    s2.length = 1;
    for (int i=0; i<length; i++)
    {
        if(i == length - 1)
        {
            split_to_two_sstruct(str, *(head+i), &s0, str_array+i);
        }
        else
        {
            split_to_two_sstruct(str, *(head+i), &s0, &s1);
            split_to_two_sstruct(s1, *(tail+i) - *(head+i), str_array+i, &s2);
        }
    }

    free(s0.charray);
    free(s1.charray);
    free(s2.charray);
    
    free(head);
    free(tail);
    
    //for (int i=0; i<length; i++) printf("strman.c: %d: %s\n", i, (str_array + i)->charray); // DEBUG
    return length;
}
