#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include "inventory.h"
 void openFilesForReadingWriting();
 void closeInventoryFile();
 void loadInventoryFromFile(Inventory *inventory);
 void saveInventoryToFile(Inventory *inventory);
 void addInventoryItem(InventoryItem *item);
 void deleteInventoryItem(Inventory *inventory,InventoryItem *item) ;
 void updateInventoryItemField(InventoryItem *item, int field, void *newValue) ;

// Function prototypes
/*void openFilesForReadingWriting();
void closeInventoryFile();
void loadInventoryFromFile(Inventory *inventory);
void saveInventoryToFile(Inventory *inventory);
void addInventoryItem(InventoryItem *item);
void deleteInventoryItem(Inventory *inventory, InventoryItem *item);
void updateInventoryItemField(InventoryItem *item, int field, void *newValue);*/

#endif // FILE_OPERATIONS_H

