#ifndef SORTING_H
#define SORTING_H

#include "inventory.h"
void splitList(InventoryItem *source, InventoryItem **frontRef, InventoryItem **backRef);
InventoryItem *sortedMerge(InventoryItem *a, InventoryItem *b, int criterion);
InventoryItem *mergeSort(InventoryItem *head, int criterion);
int sortInventorybyName(Inventory *inventory);
int sortInventorybyDepartment(Inventory *inventory);
int sortInventorybyItemID(Inventory *inventory);
int sortInventorybyPrice(Inventory *inventory);
#endif // SORTING_H
