#include "project.h"
#include <stdio.h>
#include <stdlib.h>  
#include <string.h>  

#define GST_RATE 0.18 // fixed tax rate

// Main structure data fora product 
struct Product {
    int product_code;           
    char product_name[50];      
    float unit_price;           
    int stock_quantity;         
};

// Function to show the list of all products
void displayProducts(struct Product *inventory, int product_count) {
    printf("\n--- Current Inventory Stock ---\n");
    // Print the row containing details
    printf("| %-10s | %-20s | %-12s | %-8s |\n", "CODE", "NAME", "UNIT PRICE", "STOCK");
    printf("------------------------------------------------------------------\n");
    
    // for loop here prints one product each time
    for (int i = 0; i < product_count; i++) {
        printf("| %-10d | %-20s |% -12.2f | %-8d |\n",
               inventory[i].product_code, 
               inventory[i].product_name, 
               inventory[i].unit_price, 
               inventory[i].stock_quantity);
    }
    printf("------------------------------------------------------------------\n");
}
