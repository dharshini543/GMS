#ifndef REPORT_H
#define REPORT_H

#include "inventory.h"
#include"cart.h"

typedef struct ReportItem
{
    int itemID;
    float quantity;
    struct ReportItem *next;
}ReportItem;

typedef struct Report
{
    ReportItem *head;
}Report;


void addSalesReportItem(Cart *cart, Inventory *inventory, Report * report);
void generateSalesReport(Cart *cart, Inventory *inventory,const Report *report);
void generateInventoryReport(const Inventory *inventory);
void viewLowStockAlerts(const Inventory *inventory);
int isItemIdAlreadyPresentInSalesReport(Report *report, int ItemID);

#endif // REPORT_H


