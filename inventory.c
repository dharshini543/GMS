#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "inventory.h"
#include "enum.h"
#include "file_operations.h"

int addItemToInventory(Inventory *inventory)
{
    int choice = 1;
    InventoryItem *temp = inventory->head;

    while(choice)
    {
        InventoryItem *newitem = (InventoryItem*)malloc(sizeof(InventoryItem));
        if (!newitem)
        {
            printf("Memory allocation failed.\n");
            return Failure;
        }
        newitem->itemID = inventory->itemCount+1;
        printf("Item name:");
        scanf(" %[^\n]", newitem->name);
        printf("Item Brand:");
        scanf(" %[^\n]",newitem->brand);
        printf("Item price:");
        scanf("%f",&newitem->price);
        printf("Item Quantity:");
        scanf("%f", &newitem->quantity);
        printf("Item Department:");
        scanf(" %[^\n]",newitem->department);
        printf("Item ExpiryDate:");
        scanf("%s",newitem->expiryDate);
        newitem->next = 0;

        if(inventory->head == 0 || strcmp(newitem->name,inventory->head->name) < 0)
        {
            newitem->next = inventory->head;
            inventory->head = newitem;
        }
        else
        {
            InventoryItem *temp = inventory->head;

            while(temp->next != 0 && strcmp(temp->next->name ,newitem->name) < 0)
            {
                temp = temp->next;
            }
            newitem->next = temp->next;
            temp->next = newitem;
        }
        inventory->itemCount++;
        printf("Item Added\n");
        addInventoryItem(inventory, *newitem);
        printf("Want to continue...press 1\n");
        scanf("%d",&choice);

    }

    return Success;
}


int deleteItemFromInventory(Inventory *inventory, int itemID)
{

    InventoryItem *current = inventory->head;
    InventoryItem *prev = NULL;

    if (!current)
    {
        printf("Inventory is Empty\n");
        return Failure;
    }
    if(inventory->head->itemID == itemID)
    {
        InventoryItem *temp = inventory->head->next;
        printf("%d\t%s\t\t%s\t\t%.2f\t\t%f\t\t%s\t\t%s\n", inventory->head->itemID, inventory->head->name, inventory->head->brand, inventory->head->price, inventory->head->quantity, inventory->head->department, inventory->head->expiryDate);
        free(inventory->head);
        inventory->head = temp;
        deleteInventoryItem(inventory, itemID);

        return Success;
    }
    else
    {
        while(current->itemID != itemID)
        {
            prev = current;
            current = current->next;
        }
        prev->next = current->next;
        printf("%d\t%s\t\t%s\t\t%.2f\t\t%f\t\t%s\t\t%s\n", current->itemID, current->name, current->brand, current->price, current->quantity, current->department, current->expiryDate);
        free(current);
        inventory->itemCount--;
        deleteInventoryItem(inventory, itemID);
        return Success;
    }
}

int updateItemDetails(Inventory *inventory, int itemID)
{
    int field;
    char newName[50];
    char newBrand[50];
    char newDepartment[50];
    char newExpiryDate[15];
    float newPrice;
    float newQuantity;

    InventoryItem *temp = inventory->head;
    if (!temp)
    {
        printf("No Item in inventory. Please add.\n");
        return Failure;
    }

    while (temp != NULL && temp->itemID != itemID)
    {
        temp = temp->next;
    }
    if (temp == NULL)
    {
        printf("Item not found with the given item Id.\n");
        return Failure;
    }

    printf("Enter new details for the item\n");
    printf("Enter\n1.Update Name\n2.Update Brand\n3.Update Price\n4.Update Quantity\n5.Update Department\n6.Update Expiry Date\n");
    scanf("%d", &field);

    switch (field) {
    case Name:
        printf("Item name: ");
        scanf(" %[^\n]", newName);
        updateInventoryItemField(inventory, itemID, Name, newName);
        break;
    case Brand:
        printf("Item Brand: ");
        scanf(" %[^\n]", newBrand);
        updateInventoryItemField(inventory, itemID, Brand, newBrand); // Pass newBrand
        break;
    case Price:
        printf("Item Price: ");
        scanf("%f", &newPrice);
        updateInventoryItemField(inventory, itemID, Price, &newPrice); // Pass address of newPrice
        break;
    case Quantity:
        printf("Item Quantity: ");
        scanf("%f", &newQuantity);
        updateInventoryItemField(inventory, itemID, Quantity, &newQuantity); // Pass address of newQuantity
        break;
    case Department:
        printf("Item Department: ");
        scanf(" %[^\n]", newDepartment);
        updateInventoryItemField(inventory, itemID, Department, newDepartment); // Pass newDepartment
        break;
    case ExpiryDate:
        printf("Item Expiry Date: ");
        scanf(" %[^\n]", newExpiryDate);
        updateInventoryItemField(inventory, itemID, ExpiryDate, newExpiryDate); // Pass newExpiryDate
        break;
    default:
        printf("Enter a valid option\n");
        return Failure;
    }

    return Success;
}

/*void viewInventorySummary(const Inventory *inventory)
{
    if(inventory->head == 0)
    {
        printf("Inventory is empty\n");
    }
    else
    {
        InventoryItem* temp = inventory->head;
        printf("Inventory Summary:\n");
        printf("ID\t\tName\t\t\tBrand\t\t\tPrice\t\t\tQuantity\t\tDepartment\t\tExpiry Date\n");
        while(temp != 0)
        {
            printf("%d\t\t%s\t\t\t%s\t\t\t%.2f\t\t\t%.2f\t\t\t%s\t\t\t%s\n", temp->itemID, temp->name, temp->brand, temp->price, temp->quantity, temp->department, temp->expiryDate);
            temp = temp->next;
        }
    }
}*/

void displayInventorySummary(const Inventory *inventory)
{
    printf("Inventory Summary:\n");
    printf("ID   Name                Brand            Price     Quantity    Department  Expiry Date\n");
    InventoryItem *temp = inventory->head;
    while (temp != NULL)
    {
        printf("%-4d %-20s %-15s  %.2f    %-9.2f   %-12s %-10s\n",
               temp->itemID, temp->name, temp->brand,
               temp->price, temp->quantity, temp->department, temp->expiryDate);
        temp = temp->next;
    }
}


/*int sortInventorybyName(Inventory *inventory)
{
    if (inventory->head == NULL || inventory->head->next == NULL)
    {
        return Failure;
    }

    InventoryItem *i, *j;
    for (i = inventory->head; i != NULL; i = i->next)
    {
        for (j = i->next; j != NULL; j = j->next)
        {
            if (strcmp(i->name, j->name) > 0)
            {
                InventoryItem temp = *i;
                *i = *j;
                *j = temp;

                InventoryItem *tempNext = i->next;
                i->next = j->next;
                j->next = tempNext;
            }
        }
    }
    return Success;
}

int sortInventorybyDepartment(Inventory *inventory)
{
    if (inventory->head == NULL || inventory->head->next == NULL)
    {
        return Failure;
    }

    InventoryItem *i, *j;
    for (i = inventory->head; i != NULL; i = i->next)
    {
        for (j = i->next; j != NULL; j = j->next)
        {
            if (strcmp(i->department, j->department) > 0)
            {
                InventoryItem temp = *i;
                *i = *j;
                *j = temp;

                InventoryItem *tempNext = i->next;
                i->next = j->next;
                j->next = tempNext;
            }
        }
    }
    return Success;
}

int sortInventorybyPrice(Inventory *inventory)
{
    if (inventory->head == NULL || inventory->head->next == NULL)
    {
        return Failure;
    }

    InventoryItem *i, *j;
    for (i = inventory->head; i != NULL; i = i->next)
    {
        for (j = i->next; j != NULL; j = j->next)
        {
            if ((i->price > j->price))
            {
                InventoryItem temp = *i;
                *i = *j;
                *j = temp;

                InventoryItem *tempNext = i->next;
                i->next = j->next;
                j->next = tempNext;
            }
        }
    }
    return Success;
}

int sortInventorybyItemID(Inventory *inventory)
{
    if (inventory->head == NULL || inventory->head->next == NULL)
    {
        return Failure;
    }

    InventoryItem *i, *j;
    for (i = inventory->head; i != NULL; i = i->next)
    {
        for (j = i->next; j != NULL; j = j->next)
        {
            if ((i->itemID > j->itemID))
            {
                InventoryItem temp = *i;
                *i = *j;
                *j = temp;

                InventoryItem *tempNext = i->next;
                i->next = j->next;
                j->next = tempNext;
            }
        }
    }
    return Success;
}*/

int getInventoryItemByID(Inventory*inventory,int itemID)
{
    InventoryItem *temp = inventory->head;
    if(!temp)
    {
        printf("No Item in inventory. Please add.\n");
        return Failure;
    }
    while(temp != 0 && temp->itemID != itemID)
    {
        temp = temp->next;
    }
    if(temp == 0)
    {
        printf("Item not found with the given item Id.\n");
        return Failure;
    }
    printf("%d\t%s\t\t%s\t\t%.2f\t\t%.2f\t\t%s\t\t%s\n", temp->itemID, temp->name, temp->brand, temp->price, temp->quantity, temp->department, temp->expiryDate);

    return Success;
}
