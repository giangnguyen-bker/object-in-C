#ifndef USER_H_

#define USER_H_

/* Public: */
typedef struct User User;

struct User
{
    char *username_;
    char *(*getPassword_)(User *p_User);
};

/* API of class User */
/* Constructor */
User *User_new(const char *username, const char *password);

/* Deconstructor */
void User_delete(User *p_User);


#endif  /* USER_H_ */
