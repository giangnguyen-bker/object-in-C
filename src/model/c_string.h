#ifndef C_STRING_H_
#define C_STRING_H_

/* Public: */
typedef struct C_String {

    char *(*init)(const char *str);
    void (*replace)(char *origin, const char *replace);
    void (*concatenate)(char *first, const char *followed);
    void (*truncate)(char *string, int fromIndex, int toIndex);
    int (*length)(const char *str);
} C_String;

/* Constructor */
C_String *C_String_new();

/* Deconstructor */
void C_String_delete(C_String *p_cString);

#endif /* C_STRING_H_ */