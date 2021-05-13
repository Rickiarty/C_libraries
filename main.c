#include <stdlib.h>
#include <stdio.h>

//#include "test.h"
#include "strman.h"

int main() 
{
    //printf("%d\n", test(3));
    char *str1 = "Hello! Hello...";
    char *str2 = (char*)malloc(sizeof(char) * 1);

    int length = replace(str1, 16, "ello", 4, "i", 1, str2);
    printf("%s\n(length: %d)\n", str2, length);
    
    return 0;
}
