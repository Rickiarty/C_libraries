#include "common_def.h"

struct String {
    int length;
    char *charray;
};

int replace(char*, int, char*, int, char*, int, char*);
int split_to_two_sstruct(struct String, int, struct String *, struct String *);
int test_length_of_array_before_split_string(struct String, struct String);
int split_into_string_array(struct String, struct String, struct String *);
