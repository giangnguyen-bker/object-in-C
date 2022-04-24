#ifndef USER_H_
#define USER_H_

/* Inheritance from C_String class */
#include "c_string.h"

/* Public: */
typedef struct User User;

// /* For Inheritance */
// #ifdef USER_INHERITANCE
// typedef struct hidden_User  
// #endif

struct User
{
    char *username;
    char *(*getPassword)(User *p_User);

    /* Inheritance from C_String class */
    C_String *string;
};

/* Constructor */
User *User_new(const char *username, const char *password);

/* Deconstructor */
void User_delete(User *p_User);


#endif  /* USER_H_ */
