#ifndef REPORT_FILE_H
#define REPORT_FILE_H

#include "inventory.h"
#include "report.h"

void openFiles();
void closeFiles();
void saveSalesReportToFile(Report *report, Inventory *inventory);
void saveInventoryReportToFile(Inventory *inventory);
void loadSalesReportFromFile(Report *report);
void loadInventoryReportFromFile(Inventory *inventory);

#endif // REPORT_FILE_H
