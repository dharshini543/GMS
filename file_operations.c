#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_operations.h"
#include "inventory.h"
#include "enum.h"

FILE *inventoryFile = NULL;

void openFilesForReadingWriting()
{
    inventoryFile = fopen("GroceryInventory.txt", "r+");
    if (inventoryFile == NULL)
    {
        inventoryFile = fopen("GroceryInventory.txt", "w+");
        if (inventoryFile == NULL)
        {
            printf("Error opening inventory file.\n");
            exit(1);
        }
    }
}


void closeFiles()
{
    if (inventoryFile != NULL)
    {
        fflush(inventoryFile);
        fclose(inventoryFile);
    }
}


/*void loadInventoryFromFile(Inventory *inventory)
{
    InventoryItem tempItem;
    while (fscanf(inventoryFile, "%d,%49[^,],%49[^,],%f,%f,%49[^,],%49[^\n]\n",
                  &tempItem.itemID, tempItem.name, tempItem.brand,
                  &tempItem.price, &tempItem.quantity, tempItem.department, tempItem.expiryDate) != EOF)
    {
        InventoryItem *newItem = (InventoryItem*)malloc(sizeof(InventoryItem));
        *newItem = tempItem;
        newItem->next = inventory->head;
        inventory->head = newItem;
        inventory->itemCount++;
    }
}*/
void loadInventoryFromFile(Inventory *inventory)
{
    InventoryItem tempItem;
    while (fscanf(inventoryFile, "%d, %49[^,], %49[^,], %f,  %f, %49[^,], %49[^\n]\n",
                  &tempItem.itemID, tempItem.name, tempItem.brand,
                  &tempItem.price, &tempItem.quantity, tempItem.department, tempItem.expiryDate) != EOF)
    {
        InventoryItem *newItem = (InventoryItem*)malloc(sizeof(InventoryItem));
        *newItem = tempItem;
        newItem->next = NULL;

        if (inventory->head == NULL)
        {
            inventory->head = newItem;
        }
        else
        {
            InventoryItem *temp = inventory->head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newItem;
        }
        inventory->itemCount++;
    }
}

void saveInventoryToFile(Inventory *inventory)
{

    fseek(inventoryFile, 0, SEEK_SET);

    InventoryItem *temp = inventory->head;
    while (temp != NULL)
    {
        fprintf(inventoryFile, "%d,%s,%s,%.2f,%.2f,%s,%s\n", temp->itemID, temp->name, temp->brand,
                temp->price, temp->quantity, temp->department, temp->expiryDate);
        temp = temp->next;
    }

    fflush(inventoryFile);
}

void addInventoryItem(Inventory *inventory, InventoryItem newItem)
{

    fseek(inventoryFile, 0, SEEK_END);
    fprintf(inventoryFile, "%d,%s,%s,%.2f,%.2f,%s,%s\n", newItem.itemID, newItem.name, newItem.brand,
                            newItem.price, newItem.quantity, newItem.department, newItem.expiryDate);


    fflush(inventoryFile);
}


void deleteInventoryItem(Inventory *inventory, int itemID)
{
    fseek(inventoryFile, 0, SEEK_SET);
    freopen("GroceryInventory.txt", "w", inventoryFile);

    InventoryItem *temp = inventory->head;
    while (temp != NULL)
    {
        fprintf(inventoryFile, "%d,%s,%s,%.2f,%.2f,%s,%s\n", temp->itemID, temp->name, temp->brand,
                temp->price, temp->quantity, temp->department, temp->expiryDate);
        temp = temp->next;
    }
    fflush(inventoryFile);
    printf("Item with ID %d has been deleted and file updated.\n", itemID);
}


void updateInventoryItemField(Inventory *inventory, int itemID, int field, void *newValue)
{
    InventoryItem *temp = inventory->head;

    while (temp != NULL && temp->itemID != itemID)
    {
        temp = temp->next;
    }
    if (temp == NULL)
    {
        printf("Item not found.\n");
        return;
    }

    switch (field)
    {
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

    fseek(inventoryFile, 0, SEEK_SET);
    freopen("GroceryInventory.txt", "w", inventoryFile);

    InventoryItem *tempWrite = inventory->head;
    while (tempWrite != NULL)
    {
        fprintf(inventoryFile, "%d,%s,%s,%.2f,%.2f,%s,%s\n", tempWrite->itemID, tempWrite->name, tempWrite->brand,
                tempWrite->price, tempWrite->quantity, tempWrite->department, tempWrite->expiryDate);
        tempWrite = tempWrite->next;
    }
    fflush(inventoryFile);
    printf("Field updated and file synchronized.\n");
}


