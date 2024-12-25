#include<stdio.h>
#include<stdlib.h>
#include"inventory.h"
#include"cart.h"
#include"report.h"

void addSalesReportItem(Cart *cart, Inventory *inventory, Report *report)
{
    CartItem *current = cart->head;
    int count = 0;

    while(current != 0)
    {
        InventoryItem *temp = inventory->head;

        while(temp != NULL && temp->itemID != current->itemID)
        {
            temp = temp->next;
        }
        InventoryItem *Item = temp;
        if(Item != NULL )
        {
            int check = isItemIdAlreadyPresentInSalesReport(report, Item->itemID);

            if(check == 0)
            {
                ReportItem *temp1 = report->head;
                ReportItem *newitem = (ReportItem*)malloc(sizeof(ReportItem));
                if (newitem == 0)
                {
                    printf("Memory allocation failed.\n");
                    return;
                }
                newitem->itemID = Item->itemID;
                newitem->quantity = current->quantity;
                newitem->next = 0;
                if(report->head == 0)
                {
                    report->head = newitem;
                    temp1 = newitem;
                }
                else
                {
                    while(temp1->next != 0)
                    {
                        temp1 = temp1->next;
                    }
                    temp1->next = newitem;
                    temp1 = newitem;
                }
            }
            else
            {
                ReportItem *temp2 = report->head;
                while(temp2->itemID != Item->itemID)
                {
                    temp2 = temp2->next;
                }
                temp2->quantity = temp2->quantity + current->quantity;
            }
        }
        current = current->next;
    }
}

int isItemIdAlreadyPresentInSalesReport(Report *report, int ItemID)
{
    int isPresent = 0;
    ReportItem * temp1 = report->head;

    while(temp1 != 0)
    {
        if(temp1->itemID == ItemID)
        {
            isPresent = 1;
            break;
        }
        else
        {
            isPresent = 0;
        }
        temp1 = temp1->next;
    }
    return isPresent;
}

void generateSalesReport(Cart *cart, Inventory *inventory,const Report *report)
{
    ReportItem *temp1 = report->head;
    int count = 0;
    float FinalAmount = 0;
    float Totalsales;

    printf("--------------------------Sales Report------------------------------\n");
    printf("Item_No\tItemID\tName\t\tPrice\t\tQuantity\tAmount\n");
    printf("---------------------------------------------------------------------\n");
    while(temp1 != 0)
    {
        InventoryItem *temp = inventory->head;
        while(temp != NULL && temp->itemID != temp1->itemID)
        {
            temp = temp->next;
        }
        InventoryItem *Item = temp;
        if(Item != NULL)
        {
            printf("%d\t%d\t%s\t\t%.2f\t\t%.2f\t\t%.2f\n",++count, Item->itemID, Item->name, Item->price, temp1->quantity, Item->price * temp1->quantity);
            Totalsales = Totalsales + (Item->price * temp1->quantity) ;
        }
        temp1 = temp1->next;
    }

    printf("---------------------------------------------------------------------\n");
    printf("\t\t\t\t\t\tTotal Sales = %.2f\n",Totalsales);
}

void generateInventoryReport(const Inventory *inventory)
{
    InventoryItem*temp = inventory->head;
    if(inventory->head == 0)
    {
        printf("Inventory is empty\n");
    }
    else
    {
        printf("--------------------------Inventory Report---------------------------\n");
        printf("ID\tName\t\tBrand\t\tPrice\t\tQuantity\tDepartment\tExpiryDate\n");
        printf("---------------------------------------------------------------------\n");
        while(temp != 0)
        {
            printf("%d\t%s\t\t%s\t\t%.2f\t\t%.2f\t\t%s\t\t%s\n", temp->itemID, temp->name, temp->brand, temp->price, temp->quantity, temp->department, temp->expiryDate);
            temp = temp->next;
        }
    }
}

void viewLowStockAlerts(const Inventory *inventory)
{
    InventoryItem *temp = inventory->head;
    int isFirstLowStock = 1;
    int numOfLowStock = 0;

    while(temp != 0)
    {
        if(temp->quantity < 5)
        {
            if(isFirstLowStock)
            {
                printf("----------------Low stock Alert!----------------\n");
                printf("ItemID\t\tName\t\tQuantity\n");
                isFirstLowStock = 0;
            }
            ++numOfLowStock;
            printf("%d\t\t%s\t\t%.2f\n", temp->itemID, temp->name, temp->quantity);
        }
        temp = temp->next;
    }

    if(!numOfLowStock)
    {
        printf("All stocks are above limit\n");
    }
}

