#include <stdio.h>
#include <stdlib.h>
#include "inventory.h"
#include "report.h"

FILE *salesReportFile = NULL;
FILE *inventoryReportFile = NULL;

void openFiles()
{
    salesReportFile = fopen("SalesReport.txt", "a+");
    if (salesReportFile == NULL)
    {
        printf("Error opening SalesReport.txt.\n");
        exit(1);
    }

    inventoryReportFile = fopen("InventoryReport.txt", "a+");
    if (inventoryReportFile == NULL)
    {
        printf("Error opening InventoryReport.txt.\n");
        exit(1);
    }
}

void closeFiles()
{
    if (salesReportFile != NULL)
    {
        fflush(salesReportFile);
        fclose(salesReportFile);
    }
    if (inventoryReportFile != NULL)
    {
        fflush(inventoryReportFile);
        fclose(inventoryReportFile);
    }
}


void saveSalesReportToFile(Report *report, Inventory *inventory)
{
    if (salesReportFile == NULL)
    {
        printf("Sales report file is not open.\n");
        return;
    }

    freopen("SalesReport.txt", "r+", salesReportFile);
    ReportItem *current = report->head;

    while (current != NULL)
    {
        InventoryItem *temp = inventory->head;
        while (temp != NULL && temp->itemID != current->itemID)
        {
            temp = temp->next;
        }

        if (temp != NULL)
        {
            fprintf(salesReportFile, "%d,%s,%.2f,%.2f,%.2f\n", current->itemID, temp->name,
                    temp->price, current->quantity, temp->price * current->quantity);
        }
        current = current->next;
    }

    fflush(salesReportFile);
    printf("Sales report saved to file.\n");
}

void saveInventoryReportToFile(Inventory *inventory)
{
    if (inventoryReportFile == NULL)
    {
        printf("Inventory report file is not open.\n");
        return;
    }

    freopen("InventoryReport.txt", "r+", inventoryReportFile);
    InventoryItem *current = inventory->head;

    while (current != NULL)
    {
        fprintf(inventoryReportFile, "%d,%s,%s,%.2f,%.2f,%s,%s\n", current->itemID, current->name, current->brand,
                current->price, current->quantity, current->department, current->expiryDate);
        current = current->next;
    }

    fflush(inventoryReportFile);
    printf("Inventory report saved to file.\n");
}


void loadSalesReportFromFile(Report *report)
{
    if (salesReportFile == NULL)
    {
        printf("Sales report file is not open.\n");
        return;
    }

    rewind(salesReportFile);
    ReportItem tempItem;
    while (fscanf(salesReportFile, "%d,%*[^,],%*f,%f,%*f\n", &tempItem.itemID, &tempItem.quantity) != EOF)
    {
        ReportItem *newItem = (ReportItem *)malloc(sizeof(ReportItem));
        *newItem = tempItem;
        newItem->next = report->head;
        report->head = newItem;
    }

    printf("Sales report loaded from file.\n");
}

void loadInventoryReportFromFile(Inventory *inventory)
{
    if (inventoryReportFile == NULL)
    {
        printf("Inventory report file is not open.\n");
        return;
    }

    rewind(inventoryReportFile);
    InventoryItem tempItem;
    while (fscanf(inventoryReportFile, "%d,%49[^,],%49[^,],%f,%f,%49[^,],%38[^\n]\n",
                  &tempItem.itemID, tempItem.name, tempItem.brand, &tempItem.price,
                  &tempItem.quantity, tempItem.department,tempItem.expiryDate) != EOF)
    {
        InventoryItem *newItem = (InventoryItem *)malloc(sizeof(InventoryItem));
        *newItem = tempItem;
        newItem->next = inventory->head;
        inventory->head = newItem;
    }

    printf("Inventory loaded from file.\n");
}
