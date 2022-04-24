#include <stdlib.h>
#include <string.h>
#include "c_string.h"

/* Prototype */
typedef struct hidden_C_String hidden_C_String;

/* Private */



/* ---------------------------------------------------------------------------------------- */


/* full and hidden C_String class = C_String (public in header) + pri_C_String (private in source) */
struct hidden_C_String {
    /* Highly Note: Public must be at first element to leverage the struct memory alignment \
        because the hidden_C_String address returned by calloc() \
        is also the C_String address which will be passed to Deconstructor to free() */
    
    /* Public */
    C_String pub_C_String;

    /* Private */
    
};


/* ---------------------------------------------------------------------------------------- */


/* Private member functions */


/* Public member functions */
static char *C_String_init(const char *str) {
    
    int length = strlen(str);
    char *p_str = (char *)malloc((length + 1)*sizeof(char));
    strcpy(p_str, str);
    p_str[length] = '\0';

    return p_str;
}

static void C_String_replace(char *origin, const char *replace){

    int replaceLength = strlen(replace);
    origin = (char *)realloc(origin, sizeof(char)*(replaceLength + 1));
    strcpy(origin, replace);
    origin[replaceLength] = '\0';
}

static void C_String_concatenate(char *first, const char *followed){

    int firstLength = strlen(first);
    int followedLength = strlen(followed);

    first = (char *)realloc(first, (firstLength + followedLength + 1)*sizeof(char));
    strcat(first, followed);
    first[strlen(first)] = '\0';
}

/*  indexs:      01234567
    string:     "abcdefgh"
    subString:   "bcdefg"
    => parameters: from=1,to=6
*/
static void C_String_truncate(char *string, int fromIndex, int toIndex) {

    int subStringlength = toIndex - fromIndex + 1;
    char *subString = (char *)malloc((subStringlength + 1)*sizeof(char));
    strncpy(subString, string, subStringlength);
    subString[subStringlength] = '\0';
    
    C_String_replace(string, subString);
    free(subString);
}

static int C_String_length(const char *str) {

    return strlen(str);
}

/* Constructor */
C_String *C_String_new() {
    
    /* NEED_TO_FREE */
    hidden_C_String *p_hiddenCString = (hidden_C_String *)malloc(sizeof(hidden_C_String));
    
    p_hiddenCString->pub_C_String.init = C_String_init;
    p_hiddenCString->pub_C_String.replace = C_String_replace;
    p_hiddenCString->pub_C_String.concatenate = C_String_concatenate;
    p_hiddenCString->pub_C_String.truncate = C_String_truncate;
    p_hiddenCString->pub_C_String.length = C_String_length;

    return (C_String *)p_hiddenCString;
}

/* Deconstructor */
void C_String_delete(C_String *cString) {
    
    free((hidden_C_String *)cString);
}