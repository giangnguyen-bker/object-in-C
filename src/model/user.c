#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "user.h"

#include "c_string.h"

#define KEY_HASH "encoded"
#define LENGTH_KEY_HASH 7

/* Prototype */
typedef struct hidden_User hidden_User;

/* Private: */
typedef struct pri_User
{
    char *password;
    char *(*encodePassword)(hidden_User *p_hiddenUser, char *password);
    char *(*decodePassword)(hidden_User *p_hiddenUser);
} pri_User;


/* ---------------------------------------------------------------------------------------- */


/* full and hidden User class = User (public in header) + pri_User (private in source) */
struct hidden_User 
{
    /* Highly Note: Public must be at first element to leverage the struct memory alignment \
        because the hidden_User address returned by calloc() \
        is also the User address which will be passed to Deconstructor to free() */

    /* Public */ 
    User pub_User;

    /* Private */
    pri_User pri_User;
};


/* ---------------------------------------------------------------------------------------- */


/* Private member functions */
static char *User_Password_encode(hidden_User *p_hiddenUser, char *password) {

    char *p_password = password;
    p_hiddenUser->pub_User.string->concatenate(p_password, KEY_HASH);
    
    return p_password;
}

static char *User_Password_decode(hidden_User *p_hiddenUser) {

    char *p_password = p_hiddenUser->pri_User.password;
    int length = strlen(p_password);
    int fromIndex = 0;
    int toIndex = length - LENGTH_KEY_HASH - 1;
    
    p_hiddenUser->pub_User.string->truncate(p_password, fromIndex, toIndex);

    return p_password;
}

/* Public member functions */
char *getPassword(User *p_User) {

    return ((hidden_User *)p_User)->pri_User.decodePassword((hidden_User *)p_User);
}

/* Constructor */
User *User_new(const char *username,const char *password) {
    
    /* NEED_TO_FREE */
    hidden_User *p_hiddenUser = (hidden_User *)malloc(sizeof(hidden_User));
    
    p_hiddenUser->pri_User.encodePassword = User_Password_encode;
    p_hiddenUser->pri_User.decodePassword = User_Password_decode;
    p_hiddenUser->pub_User.getPassword = getPassword;

    /* NEED_TO_FREE */
    p_hiddenUser->pub_User.string = C_String_new();
    /* NEED_TO_FREE */
    p_hiddenUser->pub_User.username =  p_hiddenUser->pub_User.string->init(username);
    /* NEED_TO_FREE */
    p_hiddenUser->pri_User.password = p_hiddenUser->pri_User.encodePassword(p_hiddenUser, \
                                p_hiddenUser->pub_User.string->init(password));
    
    return (User *)p_hiddenUser;
}

/* Deconstructor */
void User_delete(User *p_User) {

    C_String_delete(p_User->string);
    free(p_User->username);
    free(((hidden_User *)p_User)->pri_User.password);
    free((hidden_User *)p_User);
}