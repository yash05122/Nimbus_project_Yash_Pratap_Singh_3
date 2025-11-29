#ifndef PROJECT_H
#define PROJECT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define GST_RATE 0.18
struct Product {
    int product_code;
    char product_name[50];
    float unit_price;
    int stock_quantity;
};
void deductStock(struct Product *inventory, int found_index, int quantity_sold);
void displayProducts(struct Product *inventory, int product_count);
int findProductIndex(struct Product *inventory, int product_count, int product_code);
void modifyProductDetails(struct Product *inventory, int product_count);
#endif
