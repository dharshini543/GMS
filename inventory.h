#ifndef INVENTORY_H
#define INVENTORY_H

typedef struct InventoryItem
{
    int itemID;
    char name[50];
    char brand[50];
    float price;
    float quantity;
    char department[30];
    char expiryDate[15];
    struct InventoryItem *next;
} InventoryItem;

typedef struct Inventory
{
    InventoryItem *head;
    int itemCount;
} Inventory;

int addItemToInventory(Inventory *inventory);
int deleteItemFromInventory(Inventory *inventory, int itemID);
int updateItemDetails(Inventory *inventory, int itemID);
void viewInventorySummary(const Inventory *inventory);
int sortInventorybyName(Inventory *inventory);
int sortInventorybyDepartment(Inventory *inventory);
int sortInventorybyPrice(Inventory *inventory);
int sortInventorybyItemID(Inventory *inventory);
int getInventoryItemByID(Inventory*inventory, int itemID);

#endif // INVENTORY_H


