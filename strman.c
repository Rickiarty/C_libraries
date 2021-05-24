#include "strman.h"

int copy_str(struct String src, struct String *dest)
{
    dest->length = src.length;
    dest->charray = (char*)realloc(dest->charray, (dest->length + 1) * sizeof(char));
    for (int i=0; i<src.length; i++)
    {
        *(dest->charray + i) = *(src.charray + i);
    }
    *(dest->charray + dest->length) = '\0';
    return dest->length;
}

int bound_string_length_charray(int to_len, char *str, int from_len)
{
    if(to_len > from_len)
    {
        return from_len;
    }
    char *temp = (char*)malloc(sizeof(char) * from_len);
    for (int i=0; i<from_len; i++) 
    {
        *(temp + i) = *(str + i);
    }
    str = (char*)realloc(str, (to_len + 1) * sizeof(char));
    for (int i=0; i<to_len; i++)
    {
        *(str + i) = *(temp + i);
    }
    *(str + to_len) = '\0';
    free(temp);
    return to_len;
}

int bound_string_length(int to_length, struct String *str)
{
    int len = bound_string_length_charray(to_length, str->charray, str->length);
    str->length = len;
    return str->length;
}

int concatenate_charray(char *str0, int len0, char *str1, int len1, char *result)
{
    int length = len0 + len1;
    result = (char*)realloc(result, sizeof(char) * length);
    for (int i=0; i<len0; i++) 
    {
        *(result + i) = *(str0 + i);
    }
    for (int i=0; i<len1; i++) 
    {
        *(result + len0 + i) = *(str1 + i);
    }
    return length;
}

int concatenate(struct String str0, struct String str1, struct String *result)
{
    int length = concatenate_charray(str0.charray, str0.length, str1.charray, str1.length, result->charray);
    result->length = length;
    return result->length;
}

int replace_charray(char *src, int len, char *old, int len0, char *new, int len1, char *dest)
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

    int length = len + count * (len1 - len0);
    dest = (char*)realloc(dest, length * sizeof(char));

    for(index=0, i=0; index<length; index++, i++)
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

    return length;
}

int replace(struct String src, struct String old, struct String new, struct String *dest)
{
    int length = replace_charray(src.charray, src.length, old.charray, old.length, new.charray, new.length, dest->charray);
    dest->length = length;
    return dest->length;
}

int split_to_two_strings(struct String src, int index, struct String *str0, struct String *str1)
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

    //str_array = (struct String *)realloc(str_array, sizeof(struct String) * length);
    //for(int i=0; i<length; i++)
    //{
    //    (str_array+i)->charray = (char*)realloc((str_array+i)->charray, sizeof(char) * 1);
    //    (str_array+i)->length = 1;
    //}
    
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
            split_to_two_strings(str, *(head+i), &s0, str_array+i);
        }
        else
        {
            split_to_two_strings(str, *(head+i), &s0, &s1);
            split_to_two_strings(s1, *(tail+i) - *(head+i), str_array+i, &s2);
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

int padding_left_charray(char *str, int len, int p_len, char p_char, char *result)
{
    int diff = p_len - len;
    if(diff <= 0)
    {
        return len;
    }
    char* padding = (char*)malloc(sizeof(char) * diff);
    for (int i=0; i<diff; i++)
    {
        *(padding + i) = p_char;
    }
    int length = concatenate_charray(padding, diff, str, len, result);
    free(padding);
    return length;
}

int padding_left(struct String str, int p_len, char p_char, struct String *result)
{
    int length = padding_left_charray(str.charray, str.length, p_len, p_char, result->charray);
    result->length = length;
    return result->length;
}

int padding_right_charray(char* str, int len, int p_len, char p_char, char *result)
{
    int diff = p_len - len;
    if(diff <= 0)
    {
        return len;
    }
    char* padding = (char*)malloc(sizeof(char) * diff);
    for (int i=0; i<diff; i++)
    {
        *(padding + i) = p_char;
    }
    int length = concatenate_charray(str, len, padding, diff, result);
    free(padding);
    return length;
}

int padding_right(struct String str, int p_len, char p_char, struct String *result)
{
    int length = padding_right_charray(str.charray, str.length, p_len, p_char, result->charray);
    result->length = length;
    return result->length;
}

int trim_left_charray(char *origin, int len, char t_char, char *amended)
{
    int count = 0;
    while (*(origin + count) == t_char)
    {
        count++;
    }
    if(!count) // == 0
    {
        return len;
    }
    int length = len - count;
    amended = (char*)realloc(amended, sizeof(char) * length);
    for (int i=0; i<length; i++)
    {
        *(amended + i) = *(origin + count + i);
    }
    return length;
}

int trim_left(struct String origin, struct String *amended)
{
    int length = trim_left_charray(origin.charray, origin.length, ' ', amended->charray);
    amended->length = length;
    return amended->length;
}

int trim_right_charray(char *origin, int len, char t_char, char *amended)
{
    int count = 0;
    while (*(origin + len - 1 - count) == t_char)
    {
        count++;
    }
    if(!count) // == 0
    {
        return len;
    }
    int length = len - count;
    amended = (char*)realloc(amended, sizeof(char) * length);
    for (int i=0; i<length; i++)
    {
        *(amended + i) = *(origin + i);
    }
    return length;
}

int trim_right(struct String origin, struct String *amended)
{
    int length = trim_right_charray(origin.charray, origin.length, ' ', amended->charray);
    amended->length = length;
    return amended->length;
}

int trim_charray(char *origin, int len, char t_char, char *amended)
{
    char *temp = (char*)malloc(sizeof(char) * 1);
    int length = trim_right_charray(origin, len, ' ', temp);
    length = trim_left_charray(temp, length, ' ', amended);
    free(temp);
    return length;
}

int trim(struct String origin, struct String *amended)
{
    int length = trim_charray(origin.charray, origin.length, ' ', amended->charray);
    amended->length = length;
    return amended->length;
}
