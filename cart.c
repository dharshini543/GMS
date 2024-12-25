#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"cart.h"
#include"enum.h"

int addItemToCart(Cart *cart, Inventory *inventory, int itemID, float quantity)
{
    InventoryItem *temp = inventory->head;
    CartItem *current = cart->head;

    if(temp == 0)
    {
        printf("Inventory is Empty\n");
        return Failure;
    }

    while(temp != NULL && temp->itemID != itemID )
    {
        temp = temp->next;
    }
    if(temp == NULL)
    {
        printf("Item not found in Inventory\n");
        return Failure;
    }
    if(temp->quantity < quantity)
    {
        printf("Not enough stock available\n");
        return Failure;
    }

    CartItem *newitem = (CartItem*)malloc(sizeof(CartItem));
    if (!newitem)
    {
        printf("Memory allocation failed.\n");
        return Failure;
    }
    newitem->itemID = itemID;
    newitem->quantity = quantity;
    newitem->next = 0;
    if(cart->head == 0)
    {
        cart->head = newitem;
    }
    else
    {
        while(current->next != 0)
        {
            current = current->next;
        }
        current->next = newitem;
    }
    printf("ItemID:%d, Quantity:%.2f\n", newitem->itemID, newitem->quantity);
    cart->totalAmount = cart->totalAmount +(temp->price * quantity);
    return Success;

}

int removeItemFromCart(Inventory *inventory, Cart *cart, int itemID)
{
    CartItem *current = cart->head;
    CartItem *prev = NULL;
    InventoryItem *temp = inventory->head;

    if (current == NULL)
    {
        printf("Cart is Empty\n");
        return Failure;
    }

    if(cart->head->itemID == itemID)
    {
        CartItem *temp1 = cart->head->next;
        printf("%d\t%.2f\n", cart->head->itemID, cart->head->quantity);

        while(temp->itemID != itemID)
        {
            temp = temp->next;
        }
        cart->totalAmount = cart->totalAmount - (temp->price * cart->head->quantity);
        printf("Payable Amount =Rs:%.2f\n", cart->totalAmount);
        free(cart->head);
        cart->head = temp1;
        return Success;
    }
    else
    {
        while(current->itemID != itemID)
        {
            prev = current;
            current = current->next;
        }
        prev->next = current->next;
        printf("%d\t%.2f\n", current->itemID, current->quantity);

        while(temp->itemID != itemID)
        {
            temp = temp->next;
        }
        cart->totalAmount = cart->totalAmount - (temp->price * current->quantity);
        printf("Payable Amount =Rs:%.2f\n", cart->totalAmount);
        free(current);
        return Success;
    }
}

int updateCartItemQuantity(Inventory*inventory, Cart *cart, int itemID, int quantity)
{
    CartItem *current = cart->head;
    InventoryItem *temp = inventory->head;

    if(current == 0)
    {
        printf("No Item in Cart. Please add.\n");
        return Failure;
    }

    while(current != 0 && current->itemID != itemID)
    {
        current = current->next;
    }
    if(current == 0)
    {
        printf("Item not found with the given item Id.\n");
        return Failure;
    }
    current->quantity =quantity;

    while(temp->itemID != current->itemID)
    {
        temp = temp->next;
    }
    cart->totalAmount = ( temp->price * quantity );
    printf("%.2f",cart->totalAmount);

    return Success;
}

void viewCartSummary(const Cart *cart)
{
    CartItem *current = cart->head;
    if(current == 0)
    {
        printf("No Items in cart,Please add\n");
    }
    else
    {
        printf("ItemID\tQuantity\n");
        while(current != 0)
        {
            printf("%d\t%.2f\n", current->itemID, current->quantity);
            current = current->next;
        }
        printf("Total Amount =Rs:%.2f\n",cart->totalAmount);
    }

}

