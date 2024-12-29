#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_operations.h"
#include "inventory.h"
#include "enum.h"

FILE *file = NULL;

void openFilesForReadingWriting()
{
    file = fopen("GroceryInventory.txt", "r+");
    if (file == NULL)
    {
        file = fopen("GroceryInventory.txt", "w+");
        if (file == NULL)
        {
            printf("Error opening inventory file.\n");
            exit(1);
        }
    }
}

// Close the file
void closeInventoryFile()
{
    if (file != NULL)
    {
        fclose(file);
        file = NULL;
    }
}

void loadInventoryFromFile(Inventory *inventory)
{
    char buffer[MAX_LINE_SIZE];
    long offset = 0;
    InventoryItem *current = inventory->head;

    rewind(file);  // Ensure we're at the start of the file

    while (fgets(buffer, MAX_LINE_SIZE, file) != NULL && current != NULL)
    {
        current->offset = offset;
        offset += MAX_LINE_SIZE;
        current = current->next;
    }
}

void saveInventoryToFile(Inventory *inventory)
{
    InventoryItem *current = inventory->head;

    while (current != NULL)
    {
        fseek(file, current->offset, SEEK_SET);
        fprintf(file, "%d|%s|%s|%.2f|%.2f|%s|%s\n",
                current->itemID,
                current->name,
                current->brand,
                current->price,
                current->quantity,
                current->department,
                current->expiryDate);

        current = current->next;
    }

    fflush(file);  // Ensure all changes are saved
}

void addInventoryItem(InventoryItem *item)
{
    fseek(file, 0, SEEK_END);  // Move to the end of the file
    item->offset = ftell(file);

    fprintf(file, "%d|%s|%s|%.2f|%.2f|%s|%s\n",
            item->itemID,
            item->name,
            item->brand,
            item->price,
            item->quantity,
            item->department,
            item->expiryDate);

    fflush(file);  // Ensure the new data is written
}

void deleteInventoryItem(Inventory *inventory, InventoryItem *item)
{
    InventoryItem *previous = NULL;

    // Find the previous item in the linked list
    InventoryItem *temp = inventory->head;
    while (temp != NULL)
    {
        if (temp->next == item)
        {
            previous = temp;
            break;
        }
        temp = temp->next;
    }

    // If there's a previous item, remove the newline from its line
    if (previous != NULL)
    {
        fseek(file, previous->offset + MAX_LINE_SIZE - 1, SEEK_SET);
        fputc('\n', file);
    }

    // Update offsets for all subsequent items
    InventoryItem *remaining = item->next;
    while (remaining != NULL)
    {
        remaining->offset -= MAX_LINE_SIZE;
        remaining = remaining->next;
    }
}

void updateInventoryItemField(InventoryItem *item, int field, void *newValue)
{
    char buffer[MAX_LINE_SIZE];
    fseek(file, item->offset, SEEK_SET);
    fgets(buffer, MAX_LINE_SIZE, file);

    // Parse fields into temporary variables
    int itemID;
    char name[MAX_NAME_CHARS], brand[MAX_BRAND_CHARS];
    float price, quantity;
    char department[MAX_DEPARTMENT_CHARS], expiryDate[MAX_EXPIRY_DATE_CHARS];

    sscanf(buffer, "%d|%[^|]|%[^|]|%f|%f|%[^|]|%s",
           &itemID, name, brand, &price, &quantity, department, expiryDate);

    // Update the specified field
    switch (field)
    {
    case Name:
        strncpy(name, (char *)newValue, MAX_NAME_CHARS);
        break;
    case Brand:
        strncpy(brand, (char *)newValue, MAX_BRAND_CHARS);
        break;
    case Price:
        price = *(float *)newValue;
        break;
    case Quantity:
        quantity = *(float *)newValue;
        break;
    case Department:
        strncpy(department, (char *)newValue, MAX_DEPARTMENT_CHARS);
        break;
    case ExpiryDate:
        strncpy(expiryDate, (char *)newValue, MAX_EXPIRY_DATE_CHARS);
        break;
    }

    // Write the updated line back to the file
    fseek(file, item->offset, SEEK_SET);
    fprintf(file, "%d|%s|%s|%.2f|%.2f|%s|%s\n",
            itemID, name, brand, price, quantity, department, expiryDate);

    fflush(file);  // Ensure the updated data is written
}
