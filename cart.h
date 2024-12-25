#ifndef CART_H
#define CART_H
#include"inventory.h"

typedef struct CartItem
{
    int itemID;
    float quantity;
    struct CartItem *next;
} CartItem;

typedef struct Cart
{
    CartItem *head;
    float totalAmount;
} Cart;

int addItemToCart(Cart *cart, Inventory *inventory, int itemID, float quantity);
int removeItemFromCart(Inventory *inventory, Cart *cart, int itemID);
int updateCartItemQuantity(Inventory *inventory, Cart *cart, int itemID, int quantity);
void viewCartSummary(const Cart *cart);

#endif // CART_H


