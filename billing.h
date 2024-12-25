#ifndef BILLING_H
#define BILLING_H
#include"inventory.h"
#include"cart.h"
#include"report.h"

int calculateFinalBill(Cart *cart, Inventory *inventory, float * totalsales);
int applyDiscount(float *total, float discountRate);
void generateReceipt(Cart *cart, Inventory *inventory, float DiscountAmount, Report *report);
void updateInventoryQuantity(InventoryItem* temp1, CartItem* temp);

#endif // BILLING_H


