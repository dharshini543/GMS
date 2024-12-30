#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"

// Global variable to hold the current logged-in user
User* currentUser = NULL;
FILE* userFile = NULL;  // Global file pointer for users file

// Function to load users from file
User* loadUsersFromFile() {
    userFile = fopen("users.txt", "r+");  // Open file for reading and writing (update mode)
    if (!userFile) {
        return NULL;  // File does not exist or cannot be opened
    }

    User* head = NULL;
    User* temp;

    // Read users from file
    while (!feof(userFile)) {
        temp = (User*)malloc(sizeof(User));
        if (fscanf(userFile, "%s %s %d", temp->username, temp->password, &temp->isAdmin) != 3) {
            free(temp);
            break;
        }
        temp->next = head;
        head = temp;
    }

    return head;
}

// Function to save users to file (only the updates to the file)
void saveUsersToFile(User* head) {
    // We need to rewrite the file with the updated list of users.
    // To avoid opening/closing the file repeatedly, we'll use the global file pointer.
    if (userFile == NULL) {
        return;
    }

    // Move the file pointer back to the beginning
    rewind(userFile);

    // Save each user to the file
    User* temp = head;
    while (temp != NULL) {
        fprintf(userFile, "%s %s %d\n", temp->username, temp->password, temp->isAdmin);
        temp = temp->next;
    }

    // Ensure the file is properly flushed and updated
    fflush(userFile);
}

// Function to create a new user
User* createUser(User* head, int isAdmin) {
    User* newUser = (User*)malloc(sizeof(User));
    if (newUser == NULL) {
        printf("Memory allocation failed!\n");
        return head;
    }

    printf("Enter username: ");
    scanf("%s", newUser->username);
    printf("Enter password: ");
    scanf("%s", newUser->password);
    newUser->isAdmin = isAdmin;  // Set admin status (isAdmin passed as argument)

    newUser->next = head;  // Add the new user at the beginning of the list
    head = newUser;

    printf("User created successfully.\n");
    return head;
}

User* setAdmin(User* head) {
    char username[MAX_USERNAME_LENGTH];
    printf("Enter the username of the user you want to make an admin: ");
    scanf("%s", username);

    User* current = head;
    while (current != NULL) {
        if (strcmp(current->username, username) == 0) {
            current->isAdmin = 1;  // Set the user's admin status
            printf("User %s is now an admin.\n", current->username);
            return head;
        }
        current = current->next;
    }

    printf("User not found!\n");
    return head;
}

// Function to login and handle user operations
void login(User* head) {
    char username[MAX_USERNAME_LENGTH], password[MAX_PASSWORD_LENGTH];
    int found = 0;

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    // Search for the user and check the credentials
    User* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->username, username) == 0 && strcmp(temp->password, password) == 0) {
            found = 1;
            printf("Login successful\n\n");

            currentUser = temp;  // Set the logged-in user

            if (temp->isAdmin) {
                // Perform admin operations here
            } else {
                // Perform normal user operations here
            }
            break;
        }
        temp = temp->next;
    }

    if (!found) {
        printf("Invalid username or password.\n");
    }
}

// Function to check if the logged-in user is an admin
int isAdminLoggedIn() {
    if (currentUser != NULL && currentUser->isAdmin) {
        return 1;  // User is an admin
    }
    return 0;  // User is not an admin
}

// Function to change password
User* changePassword(User* head) {
    char username[MAX_USERNAME_LENGTH], password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    scanf("%s", username);

    // Find the user in the list
    User* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->username, username) == 0) {
            printf("Enter new password: ");
            scanf("%s", password);
            strcpy(temp->password, password);
            printf("Password updated successfully.\n");

            // Save the updated list to the file immediately
            saveUsersToFile(head);
            return head;
        }
        temp = temp->next;
    }

    printf("User not found.\n");
    return head;
}

// Function to free the linked list memory
void freeList(User* head) {
    User* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// Function to close the file when exiting the program
/*void closeFile() {
    if (userFile != NULL) {
        fclose(userFile);
        userFile = NULL;  // Reset the file pointer
    }
}*/
