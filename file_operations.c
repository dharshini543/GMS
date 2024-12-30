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

// Utility function to write padded fields
void writePaddedField(char *dest, const char *src, int maxLen)
{
    snprintf(dest, maxLen + 1, "%-*s", maxLen, src);
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

        char paddedName[MAX_NAME_CHARS + 1], paddedBrand[MAX_BRAND_CHARS + 1];
        char paddedDepartment[MAX_DEPARTMENT_CHARS + 1], paddedExpiry[MAX_EXPIRY_DATE_CHARS + 1];

        writePaddedField(paddedName, current->name, MAX_NAME_CHARS);
        writePaddedField(paddedBrand, current->brand, MAX_BRAND_CHARS);
        writePaddedField(paddedDepartment, current->department, MAX_DEPARTMENT_CHARS);
        writePaddedField(paddedExpiry, current->expiryDate, MAX_EXPIRY_DATE_CHARS);

        fprintf(file, "%-*d|%s|%s|%*.2f|%*.2f|%s|%s\n",
                MAX_ITEM_ID_DIGITS, current->itemID,
                paddedName,
                paddedBrand,
                MAX_PRICE_DIGITS, current->price,
                MAX_QUANTITY_DIGITS, current->quantity,
                paddedDepartment,
                paddedExpiry);

        current = current->next;
    }

    fflush(file);  // Ensure all changes are saved
}




void addInventoryItem(InventoryItem *item)
{
    fseek(file, 0, SEEK_END);  // Move to the end of the file
    item->offset = ftell(file);

    char paddedName[MAX_NAME_CHARS + 1], paddedBrand[MAX_BRAND_CHARS + 1];
    char paddedDepartment[MAX_DEPARTMENT_CHARS + 1], paddedExpiry[MAX_EXPIRY_DATE_CHARS + 1];

    writePaddedField(paddedName, item->name, MAX_NAME_CHARS);
    writePaddedField(paddedBrand, item->brand, MAX_BRAND_CHARS);
    writePaddedField(paddedDepartment, item->department, MAX_DEPARTMENT_CHARS);
    writePaddedField(paddedExpiry, item->expiryDate, MAX_EXPIRY_DATE_CHARS);

    fprintf(file, "%-*d|%s|%s|%*.2f|%*.2f|%s|%s\n",
            MAX_ITEM_ID_DIGITS, item->itemID,
            paddedName,
            paddedBrand,
            MAX_PRICE_DIGITS, item->price,
            MAX_QUANTITY_DIGITS, item->quantity,
            paddedDepartment,
            paddedExpiry);

    fflush(file);  // Ensure the new data is written
}

void deleteInventoryItem(Inventory *inventory, InventoryItem *item) {
    // Step 1: Update the offsets of the subsequent items in memory
    InventoryItem *current = item->next;
    while (current != NULL) {
        // Shift the offset back by one line size (one item is removed, so the subsequent items' offsets decrease)
        current->offset -= MAX_LINE_SIZE;
        current = current->next;
    }

    // Step 2: Re-write the entire inventory to the file, skipping the deleted item
    fseek(file, 0, SEEK_SET);  // Start from the beginning of the file

    current = inventory->head;
    while (current != NULL) {
        // If it's not the item to be deleted, write it to the file
        if (current != item) {
            fprintf(file, "%-*d|%-*s|%-*s|%-*0.2f|%-*0.2f|%-*s|%-*s\n",
                    MAX_ITEM_ID_DIGITS, current->itemID,
                    MAX_NAME_CHARS, current->name,
                    MAX_BRAND_CHARS, current->brand,
                    MAX_PRICE_DIGITS, current->price,
                    MAX_QUANTITY_DIGITS, current->quantity,
                    MAX_DEPARTMENT_CHARS, current->department,
                    MAX_EXPIRY_DATE_CHARS, current->expiryDate);
        }
        // Move to the next item in the list
        current = current->next;
    }
    fflush(file);  // Ensure the new data is written
}


void updateInventoryItemField(InventoryItem *item, int field, void *newValue)
{
    // Update the specific field in the InventoryItem object
    switch (field)
    {
    case Name:
        strncpy(item->name, (char *)newValue, MAX_NAME_CHARS);
        item->name[MAX_NAME_CHARS - 1] = '\0';  // Ensure null termination
        break;
    case Brand:
        strncpy(item->brand, (char *)newValue, MAX_BRAND_CHARS);
        item->brand[MAX_BRAND_CHARS - 1] = '\0';  // Ensure null termination
        break;
    case Price:
        item->price = *(float *)newValue;
        break;
    case Quantity:
        item->quantity = *(float *)newValue;
        break;
    case Department:
        strncpy(item->department, (char *)newValue, MAX_DEPARTMENT_CHARS);
        item->department[MAX_DEPARTMENT_CHARS - 1] = '\0';  // Ensure null termination
        break;
    case ExpiryDate:
        strncpy(item->expiryDate, (char *)newValue, MAX_EXPIRY_DATE_CHARS);
        item->expiryDate[MAX_EXPIRY_DATE_CHARS - 1] = '\0';  // Ensure null termination
        break;
    }

    // Prepare the full line to be written back to the file
    char updatedLine[MAX_LINE_SIZE];

    // Format the updated line with the modified fields
    snprintf(updatedLine, MAX_LINE_SIZE, "%-*d|%-*s|%-*s|%*.2f|%*.2f|%-*s|%-*s\n",
             MAX_ITEM_ID_DIGITS, item->itemID,
             MAX_NAME_CHARS, item->name,
             MAX_BRAND_CHARS, item->brand,
             MAX_PRICE_DIGITS, item->price,
             MAX_QUANTITY_DIGITS, item->quantity,
             MAX_DEPARTMENT_CHARS, item->department,
             MAX_EXPIRY_DATE_CHARS, item->expiryDate);

    // Write the updated line to the file at the specified offset
    fseek(file, item->offset, SEEK_SET);
    fwrite(updatedLine, sizeof(char), strlen(updatedLine), file);

    fflush(file);  // Ensure that the updated data is written to the file
}
