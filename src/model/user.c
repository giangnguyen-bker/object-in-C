#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"
#define KEY_HASH "encoded"
#define LENGTH_KEY_HASH 7

/* Prototype */
typedef struct hidden_User hidden_User;

/* Private: */
typedef struct pri_User
{
    char *password_;
    char *(*encodePassword_)(hidden_User *p_hiddenUser, const char *password);
    char *(*decodePassword_)(hidden_User *p_hiddenUser);
    char *(*stringNew_)(const char *string);
} pri_User;


/* ---------------------------------------------------------------------------------------- */


/* full and hidden User class = User (public in header) + pri_User (private in source) */
struct hidden_User 
{
    /* Highly Note: Public must be at first element to leverage the struct memory alignment \
        because the hidden_User address returned by calloc() \
        is also the User address which will be passed to Deconstructor to free() */

    /* Public */ 
    User pub_User_;

    /* Private */
    pri_User pri_User_;
};


/* ---------------------------------------------------------------------------------------- */


/* Private member functions */
static char *User_Password_encode(hidden_User *p_hiddenUser, const char *password) {

    char *e_password = p_hiddenUser->pri_User_.stringNew_(password);
    int length_ = strlen(password);

    e_password = (char *)realloc(e_password, length_ + LENGTH_KEY_HASH + 1);
    strcat(e_password, KEY_HASH);
    e_password[strlen(e_password)] = '\0';
    
    return e_password;
}

static char *User_Password_decode(hidden_User *p_hiddenUser) {

    char *password = p_hiddenUser->pri_User_.password_;
    int length_ = strlen(password);

    password = (char *)realloc(password, (length_ - LENGTH_KEY_HASH + 1)*sizeof(char));
    
    password[length_ - LENGTH_KEY_HASH] = '\0';

    return password;
}

static char *User_String_new(const char *string) {

    int length = strlen(string);
    
    char *p_string = (char *)malloc((length + 1)*sizeof(char));
    strcpy(p_string, string);
    p_string[length] = '\0';

    return p_string;
}

/* Public member functions */
char *getPassword(User *p_User) {

    return ((hidden_User *)p_User)->pri_User_.decodePassword_((hidden_User *)p_User);
}


/* ---------------------------------------------------------------------------------------- */


/* Methods definations */
/* Constructor */
User *User_new(const char *username,const char *password) {
    
    hidden_User *p_hiddenUser = (hidden_User *)calloc(1, sizeof(hidden_User));
    
    p_hiddenUser->pri_User_.encodePassword_ = User_Password_encode;
    p_hiddenUser->pri_User_.decodePassword_ = User_Password_decode;
    p_hiddenUser->pri_User_.stringNew_ = User_String_new;
    p_hiddenUser->pub_User_.getPassword_ = getPassword;

    p_hiddenUser->pub_User_.username_ = p_hiddenUser->pri_User_.stringNew_(username);
    p_hiddenUser->pri_User_.password_ = p_hiddenUser->pri_User_.encodePassword_( \
                                    p_hiddenUser ,password);
        
    return (User *)p_hiddenUser;
}

/* Deconstructor */
void User_delete(User *p_User) {

    free(((hidden_User *)p_User)->pri_User_.password_);
    free(((hidden_User *)p_User)->pub_User_.username_);
    free((hidden_User *)p_User);
}