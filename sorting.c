#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventory.h"
#include "enum.h"

void splitList(InventoryItem *source, InventoryItem **frontRef, InventoryItem **backRef)
{
    InventoryItem *slow = source;
    InventoryItem *fast = source->next;

    while (fast != NULL)
    {
        fast = fast->next;
        if (fast != NULL)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}

InventoryItem *sortedMerge(InventoryItem *a, InventoryItem *b, int criterion) {
    if (a == NULL) return b;
    if (b == NULL) return a;

    InventoryItem *result;

    int compare = 0;
    switch (criterion)
    {
    case Sort_By_Name:
        compare = strcmp(a->name, b->name);
        break;
    case Sort_By_Department:
        compare = strcmp(a->department, b->department);
        break;
    case Sort_By_ItemID:
        compare = (a->itemID - b->itemID);
        break;
    case Sort_By_Price:
        compare = (a->price > b->price) - (a->price < b->price);
        break;
    default:
        break;
    }

    if (compare <= 0)
    {
        result = a;
        result->next = sortedMerge(a->next, b, criterion);
    }
    else
    {
        result = b;
        result->next = sortedMerge(a, b->next, criterion);
    }

    return result;
}

InventoryItem *mergeSort(InventoryItem *head, int criterion)
{
    if (head == NULL || head->next == NULL)
        return head;

    InventoryItem *a;
    InventoryItem *b;

    splitList(head, &a, &b);

    a = mergeSort(a, criterion);
    b = mergeSort(b, criterion);

    return sortedMerge(a, b, criterion);
}

int sortInventorybyName(Inventory *inventory)
{
    if (inventory->head == NULL)
        return Failure;
    inventory->head = mergeSort(inventory->head, Sort_By_Name);
    return Success;
}

int sortInventorybyDepartment(Inventory *inventory)
{
    if (inventory->head == NULL)
        return Failure;
    inventory->head = mergeSort(inventory->head, Sort_By_Department);
    return Success;
}

int sortInventorybyItemID(Inventory *inventory)
{
    if (inventory->head == NULL)
        return Failure;
    inventory->head = mergeSort(inventory->head, Sort_By_ItemID);
    return Success;
}

int sortInventorybyPrice(Inventory *inventory)
{
    if (inventory->head == NULL)
        return Failure;
    inventory->head = mergeSort(inventory->head, Sort_By_Price);
    return Success;
}
