#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include "inventory.h"
#include"report.h"
void openFilesForReadingWriting();
void closeFiles();
void loadInventoryFromFile(Inventory *inventory);
void saveInventoryToFile(Inventory *inventory);
void addInventoryItem(Inventory *inventory, InventoryItem newItem);
void deleteInventoryItem(Inventory *inventory, int itemID) ;
void updateInventoryItemField(Inventory *inventory, int itemID, int field, void *newValue) ;
#endif // FILE_OPERATIONS_H

