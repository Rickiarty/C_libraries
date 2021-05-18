#include "common_def.h"

struct String {
    int length;
    char *charray;
};

// concatenating
int concatenate_charray(char*, int, char*, int, char*);
int concatenate(struct String, struct String, struct String *);
// replacing
int replace_charray(char*, int, char*, int, char*, int, char*);
int replace(struct String, struct String, struct String, struct String *);
// splitting
int split_to_two_strings(struct String, int, struct String *, struct String *);
int test_length_of_array_before_split_string(struct String, struct String);
int split_into_string_array(struct String, struct String, struct String *);
// padding
int padding_left_charray(char*, int, int, char, char*);
int padding_left(struct String, int, char, struct String *);
int padding_right_charray(char*, int, int, char, char*);
int padding_right(struct String, int, char, struct String *);
// trimming
int trim_left_charray(char*, int, char, char*);
int trim_left(struct String, struct String *);
int trim_right_charray(char*, int, char, char*);
int trim_right(struct String, struct String *);
int trim_charray(char*, int, char, char*);
int trim(struct String, struct String *);
