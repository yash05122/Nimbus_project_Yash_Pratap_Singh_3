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

// Function to find a product's location (index) in the array using its code
int findProductIndex(struct Product *inventory, int product_count, int product_code) {
    // Loop through the entire inventory array, checking every item
    for (int i = 0; i < product_count; i++) {
        // If the code matches, we found it!
        if (inventory[i].product_code == product_code)
            return i; // Send back the position (index)
    }
    return -1; // If the loop finishes, the product was not found, so send back -1
}

// Function to change the price or stock quantity of an existing product
void modifyProductDetails(struct Product *inventory, int product_count) {
    int code_to_modify, found_index, update_choice;
    
    printf("\n--- Modify Inventory Details ---\n");
    printf("Enter Product Code you want to modify: ");
    // Reading product code (number)
    scanf("%d", &code_to_modify);
    
    // Find where the product is located in the array
    found_index = findProductIndex(inventory, product_count, code_to_modify);
    
    // If the search failed (index is -1), show error
    if (found_index == -1) {
        printf("[ERROR] Product code %d was not found.\n", code_to_modify);
        return;
    }

    // Show the user which product they are modifying
    printf("\nModifying Product: %s (Price: %.2f, Stock: %d)\n", 
           inventory[found_index].product_name, 
           inventory[found_index].unit_price, 
           inventory[found_index].stock_quantity);
           
    // Ask the user what they want to change
    printf("What modification do you need?\n");
    printf("1. Update Unit Price\n");
    printf("2. Add Stock Quantity\n");
    printf("Enter choice (1 or 2): ");
    
    // Reading choice (number)
    if (scanf("%d", &update_choice) != 1 || (update_choice != 1 && update_choice != 2)) {
        printf("[ERROR] Invalid choice. Returning to menu.\n");
        return;
    }

    // 'if-else' logic to handle the user's choice
    if (update_choice == 1) {
        float new_price;
        printf("Enter the NEW Unit Price: ");
        // Reading new price (float)
        scanf("%f", &new_price);
        
        // Change the price in the structure
        inventory[found_index].unit_price = new_price;
        printf("[SUCCESS] Price for %s updated to %.2f.\n", inventory[found_index].product_name, new_price);
    } else if (update_choice == 2) {
        int quantity_to_add;
        printf("Enter Quantity to ADD to existing stock: ");
        // Reading quantity to add (number)
        scanf("%d", &quantity_to_add);
        
        // Add the new quantity to the existing stock
        inventory[found_index].stock_quantity += quantity_to_add;
        printf("[SUCCESS] Stock updated. New stock is %d.\n", inventory[found_index].stock_quantity);
    }
}