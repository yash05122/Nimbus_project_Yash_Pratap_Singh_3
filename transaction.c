#include "project.h"
#include <stdio.h>
#include <stdlib.h>  
#include <string.h>  

// NOTE: Struct definition is repeated here, but should be replaced by #include "project.h" 
// when compiled by the team.
struct Product {
    int product_code;           
    char product_name[50];      
    float unit_price;           
    int stock_quantity;         
};

// Function to reduce the stock after a sale
void deductStock(struct Product *inventory, int found_index, int quantity_sold) {
    // Go to the product's position and subtract the quantity sold from the stock
    inventory[found_index].stock_quantity -= quantity_sold;
}