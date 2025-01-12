#include "utils.h"
#include <stdio.h>
void interface_menu()
{
    printf("\n");

    printf("=== Train Loading Management System ===\n");
    printf("1-Load train status from file\n");
    printf("2-Load material, starting from first suitable wagon from head of the Train\n");
    printf("3-Load material to specific wagon\n");
    printf("4-Unload material, starting from first suitable wagon from tail of the Train\n");
    printf("5-Unload material from specific wagon\n");
    printf("6-Display train status\n");
    printf("7-Display materials status\n");
    printf("8-Empty train\n");
    printf("9-Save train status to file\n ");
    printf("10-Exit\n");

    printf("ACTION NUMBER: ");
}
