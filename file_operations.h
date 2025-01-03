#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include "inventory.h"
void openFilesForReadingWriting();
void closeFile();
void loadInventoryFromFile(Inventory *inventory);
void saveInventoryToFile(Inventory *inventory);
void addInventoryItem(Inventory *inventory, InventoryItem newItem);
void deleteInventoryItem(Inventory *inventory, int itemID) ;
void updateInventoryItemField(Inventory *inventory, int itemID, int field, void *newValue) ;
#endif // FILE_OPERATIONS_H

