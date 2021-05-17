#include "strman.h"

int main(int argc, char** args) 
{
    char *str1 = "Hello! Hello...";
    char *str2 = (char*)malloc(sizeof(char) * 1);

    printf("%s\n(length: %d)\n", str1, 16);
    int length = replace(str1, 16, "ello", 4, "i", 1, str2);
    printf("%s\n(length: %d)\n", str2, length);
    //printf("%d\t%d\n", true, false);

    // must de-allocate memory manually
    free(str2);

    return 0;
}
