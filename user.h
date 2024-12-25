#ifndef USER_H
#define USER_H

#define MAX_USERNAME_LENGTH 30
#define MAX_PASSWORD_LENGTH 30

// User structure
typedef struct User {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int isAdmin;  // 1 for admin, 0 for normal user
    struct User* next;  // Pointer to the next user in the linked list
} User;

// Global variable to hold the currently logged-in user
extern User* currentUser;
extern FILE* userFile;  // Global file pointer

// Function prototypes for user operations
User* createUser(User* head, int isAdmin);
User* setAdmin(User* head);
void login(User* head);
User* changePassword(User* head);
void freeList(User* head);

// Function to check if the logged-in user is an admin
int isAdminLoggedIn();

// Load and save users from/to file
User* loadUsersFromFile();
void saveUsersToFile(User* head);

#endif // USER_H
