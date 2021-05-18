#include "strman.h"

int main(int argc, char** args) 
{
    struct String str, symbols, s1, s2;
    struct String *str_arr;
    
    str.charray = "Hi, this is C.";
    str.length = 15;
    s1.charray = (char*)malloc(sizeof(char) * 1);
    s1.length = 0;
    s2.charray = (char*)malloc(sizeof(char) * 1);
    s2.length = 0;
    symbols.charray = " ";
    symbols.length = 1;

    printf("main.c: original string: %s\n\n", str.charray);
    struct String old, new, amended;
    old.charray = "i,";
    old.length = 2;
    new.charray = "ello,";
    new.length = 5;
    amended.charray = (char*)malloc(sizeof(char) * 1);
    amended.length = 1;
    replace(str, old, new, &amended);
    printf("main.c: amended string: %s\n\n", amended.charray);

    split_to_two_strings(str, 3, &s1, &s2);
    printf("main.c:\n\tstr: %s\n\ts1: %s\n\ts2: %s\n\n", str.charray, s1.charray, s2.charray);
    concatenate(s1, s2, &amended);
    printf("main.c: concatenated string: %s\n\n", amended.charray);

    // First, we test how many characters length of an array shall be before split a string into it. 
    int count = test_length_of_array_before_split_string(str, symbols);
    
    // init: manually allocate memory outside of function in C-lang
    str_arr = (struct String *)malloc(sizeof(struct String) * count);
    for (int i=0; i<count; i++)
    {
        (str_arr+i)->charray = malloc(sizeof(char) * 1);
        (str_arr+i)->length = 1;
    }

    // split a string into an array of strings with a given sub-string
    count = split_into_string_array(str, symbols, str_arr);

    // print on CLI
    for (int i=0; i<count; i++) 
    {
        printf("main.c: %d: %s\n", i, (str_arr + i)->charray);
    }

    // must de-allocate memory manually
    for (int i=0; i<count; i++) 
    {
        free((str_arr + i)->charray);
    }
    free(str_arr);

    return 0; // exit code
}
