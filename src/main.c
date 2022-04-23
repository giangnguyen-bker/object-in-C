#include <stdio.h>

#include "./model/user.h"

int main() {

    char *username1 = "Giang";
    char *password1 = "123";
    char *username2 = "Giangnguyentbk";
    char *password2 = "giangtanhung3";
    char *username3 = "cter";
    char *password3 = "c7n";

    User *p_userA = User_new(username1, password1);
    User *p_userB = User_new(username2, password2);
    User *p_userC = User_new(username3, password3);
    
    printf("A's username: %s\n", p_userA->username_);
    printf("A's password: %s\n", p_userA->getPassword_(p_userA));
    printf("B's username: %s\n", p_userB->username_);
    printf("B's password: %s\n", p_userB->getPassword_(p_userB));
    printf("C's username: %s\n", p_userC->username_);
    printf("C's password: %s\n", p_userC->getPassword_(p_userC));

    User_delete(p_userA);
    return 0;
}