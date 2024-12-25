#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_operations.h"
#include "inventory.h"
#include "enum.h"

// Global file pointer
FILE *inventoryFile = NULL;

// Open files for both inventory and report
void openFilesForReadingWriting() {
    inventoryFile = fopen("GroceryInventory.txt", "w+");
    if (inventoryFile == NULL) {
        printf("Error opening inventory file.\n");
        exit(1);
    }
}

// Close both files when exiting the program
void closeFiles() {
    if (inventoryFile != NULL) {
        fclose(inventoryFile);
    }
}

// Load inventory data from the file
void loadInventoryFromFile(Inventory *inventory) {
    InventoryItem tempItem;
    while (fscanf(inventoryFile, "%d,%s,%s,%f,%f,%s,%s\n", &tempItem.itemID, tempItem.name, tempItem.brand,
                  &tempItem.price, &tempItem.quantity, tempItem.department, tempItem.expiryDate) != EOF) {
        InventoryItem *newItem = (InventoryItem*)malloc(sizeof(InventoryItem));
        *newItem = tempItem;
        newItem->next = inventory->head;
        inventory->head = newItem;
        inventory->itemCount++;
    }
}


// Save the updated inventory data to the file
void saveInventoryToFile(Inventory *inventory) {
    // We will seek back to the beginning and write the updated inventory
    fseek(inventoryFile, 0, SEEK_SET);  // Seek to the beginning of the file

    InventoryItem *temp = inventory->head;
    while (temp != NULL) {
        fprintf(inventoryFile, "%d,%s,%s,%.2f,%.2f,%s,%s\n", temp->itemID, temp->name, temp->brand,
                temp->price, temp->quantity, temp->department, temp->expiryDate);
        temp = temp->next;
    }

    fflush(inventoryFile); // Ensure immediate write to file
}


void addInventoryItem(Inventory *inventory, InventoryItem newItem)
{
    /*InventoryItem *item = (InventoryItem *)malloc(sizeof(InventoryItem));
    *item = newItem;
    item->next = inventory->head;
    inventory->head = item;
    //inventory->itemCount++;*/

    fseek(inventoryFile, 0, SEEK_END);
    fprintf(inventoryFile, "%d,%s,%s,%.2f,%.2f,%s,%s\n", newItem.itemID, newItem.name, newItem.brand,
                            newItem.price, newItem.quantity, newItem.department, newItem.expiryDate);


    fflush(inventoryFile);  // Ensure the change is saved to the file
}

/*void deleteInventoryItem(Inventory *inventory, int itemID) {
    InventoryItem *prev = NULL;
    InventoryItem *current = inventory->head;

    // Find the item to delete in the linked list
    while (current != NULL && current->itemID != itemID) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) {
        printf("Item with ID %d not found.\n", itemID);
        return;
    }

    // Remove the item from the linked list
    if (prev == NULL) {
        inventory->head = current->next;
    } else {
        prev->next = current->next;
    }
    free(current);
    inventory->itemCount--;

    // Rewrite the file to reflect the deletion
    fseek(inventoryFile, 0, SEEK_SET);  // Move to the beginning of the file
    InventoryItem *temp = inventory->head;
    freopen("GroceryInventory.txt", "w", inventoryFile);  // Clear the file content and prepare for writing

    while (temp != NULL) {
        fprintf(inventoryFile, "%d,%s,%s,%.2f,%.2f,%s,%s\n", temp->itemID, temp->name, temp->brand,
                temp->price, temp->quantity, temp->department, temp->expiryDate);
        temp = temp->next;
    }
    fflush(inventoryFile);  // Ensure the changes are saved to the file
}*/

void deleteInventoryItem(Inventory *inventory, int itemID) {
    InventoryItem *prev = NULL;
    InventoryItem *current = inventory->head;

    // Find the item to delete
    while (current != NULL && current->itemID != itemID) {
        prev = current;
        current = current->next;
    }

    // If the item is not found
    if (current == NULL) {
        printf("Item with ID %d not found.\n", itemID);
        return;
    }

    // Remove from linked list
    if (prev == NULL) {
        inventory->head = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
    inventory->itemCount--;
    printf("Item with ID %d deleted from memory.\n", itemID);

    // Clear and rewrite the file
    ftruncate(fileno(inventoryFile), 0); // Truncate the file
    fseek(inventoryFile, 0, SEEK_SET);   // Move to the start of the file

    InventoryItem *temp = inventory->head;
    while (temp != NULL) {
        fprintf(inventoryFile, "%d,%s,%s,%.2f,%.2f,%s,%s\n", temp->itemID, temp->name, temp->brand,
                temp->price, temp->quantity, temp->department, temp->expiryDate);
        temp = temp->next;
    }

    fflush(inventoryFile); // Ensure the file is updated
    printf("File updated successfully.\n");
}

void updateInventoryItemField(Inventory *inventory, int itemID, int field, void *newValue)
{
    InventoryItem *temp = inventory->head;

    // Locate the item in the linked list
    while (temp != NULL && temp->itemID != itemID) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Item not found.\n");
        return;
    }

    // Update the field
    switch (field) {
    case Name:
        strncpy(temp->name, (char *)newValue, sizeof(temp->name));
        break;
    case Brand:
        strncpy(temp->brand, (char *)newValue, sizeof(temp->brand));
        break;
    case Price:
        temp->price = *(float *)newValue;
        break;
    case Quantity:
        temp->quantity = *(float *)newValue;
        break;
    case Department:
        strncpy(temp->department, (char *)newValue, sizeof(temp->department));
        break;
    case ExpiryDate:
        strncpy(temp->expiryDate, (char *)newValue, sizeof(temp->expiryDate));
        break;
    default:
        printf("Invalid field.\n");
        return;
    }

    // File synchronization logic here (overwrite the file)
    fseek(inventoryFile, 0, SEEK_SET);
    freopen("GroceryInventory.txt", "w", inventoryFile);  // Clear the file for rewriting

    InventoryItem *tempWrite = inventory->head;
    while (tempWrite != NULL) {
        fprintf(inventoryFile, "%d,%s,%s,%.2f,%.2f,%s,%s\n", tempWrite->itemID, tempWrite->name, tempWrite->brand,
                tempWrite->price, tempWrite->quantity, tempWrite->department, tempWrite->expiryDate);
        tempWrite = tempWrite->next;
    }
    fflush(inventoryFile);  // Ensure changes are saved
    printf("Field updated and file synchronized.\n");
}


