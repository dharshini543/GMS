#ifndef USER_H
#define USER_H

#define MAX_USERNAME_LENGTH 30
#define MAX_PASSWORD_LENGTH 30

typedef struct User
{
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int isLoggedIn;
} User;

void initializeUser(User *user, const char *username, const char *password);
int loginUser(User *user, const char *username, const char *password);
void logoutUser(User *user);
void displayLoginScreen(User *user);

#endif // USER_H








