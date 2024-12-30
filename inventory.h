#ifndef INVENTORY_H
#define INVENTORY_H

#define MAX_ITEM_ID_DIGITS 10
#define MAX_PRICE_DIGITS 10
#define MAX_QUANTITY_DIGITS 10
#define MAX_NAME_CHARS 50
#define MAX_BRAND_CHARS 50
#define MAX_DEPARTMENT_CHARS 30
#define MAX_EXPIRY_DATE_CHARS 15
#define MAX_LINE_SIZE (MAX_ITEM_ID_DIGITS + MAX_NAME_CHARS + MAX_BRAND_CHARS + \
                       MAX_PRICE_DIGITS + MAX_QUANTITY_DIGITS + MAX_DEPARTMENT_CHARS + \
                       MAX_EXPIRY_DATE_CHARS + 6 + 2)  // Delimiters and newline

typedef struct InventoryItem
{
    int itemID;
    char name[MAX_NAME_CHARS];
    char brand[MAX_BRAND_CHARS];
    float price;
    float quantity;
    char department[MAX_DEPARTMENT_CHARS];
    char expiryDate[MAX_EXPIRY_DATE_CHARS];
    long offset;  // To store the file position of this item
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
void displayInventorySummary(const Inventory *inventory);
int sortInventorybyName(Inventory *inventory);
int sortInventorybyDepartment(Inventory *inventory);
int sortInventorybyPrice(Inventory *inventory);
int sortInventorybyItemID(Inventory *inventory);
int getInventoryItemByID(Inventory*inventory, int itemID);

#endif // INVENTORY_H


