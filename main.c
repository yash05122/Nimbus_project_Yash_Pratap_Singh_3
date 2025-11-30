#include "project.h"
#include <stdio.h>   // (input/output)
#include <stdlib.h>  // Need this for malloc
#include <string.h> 
#define GST_RATE 0.18 // This is our fixed tax rate: 18%

// This is our main custom data structure, like a template for ONE product.
struct Product {
    int product_code;           // Holds the unique number for the product
    char product_name[50];      // Holds the name (up to 49 characters)
    float unit_price;           // Holds the cost of one unit
    int stock_quantity;         // Holds how many units we have left
};

// --- PROTOTYPES FOR OTHER MEMBER'S FUNCTIONS (REQUIRED FOR COMPILATION) ---
// These declarations would be replaced by #include "project.h" in a real scenario
void displayProducts(struct Product *inventory, int product_count);
int findProductIndex(struct Product *inventory, int product_count, int product_code);
void deductStock(struct Product *inventory, int found_index, int quantity_sold);
void modifyProductDetails(struct Product *inventory, int product_count);

// --- This is where the program actually starts running! ---
int main(void) {
    int product_count = 0;
    int menu_choice, product_code, quantity_to_purchase, found_index;
    
    // Financial variables, all starting at zero
    float gross_total = 0.0;             // Total cost BEFORE any discounts
    float cumulative_discount = 0.0;     // Total amount saved by the customer
    float bill_subtotal = 0.0;           // Total cost AFTER discounts, BEFORE tax (Taxable Amount)
    float final_amount_due = 0.0;        // The final money the customer pays
    
    // Declare a pointer to the Product structure. This pointer will hold the memory address of our whole inventory list.
    struct Product *inventory = NULL; 

    printf("Welcome to the Inventory Setup!\n");
    printf("Please specify how many different products you want to manage initially: ");
    
    // Reading the initial array size (number)
    if (scanf("%d", &product_count) != 1 || product_count <= 0) {
        printf("[SYSTEM ERROR] Invalid or zero number entered. Closing system.\n");
        exit(1); // Stop the program
    }

    // Dynamic Allocation: 'malloc' asks the operating system for a chunk of memory big enough to store all our products
    inventory = (struct Product *) malloc(product_count * sizeof(struct Product));
    
    // Check if memory was successfully given
    if (inventory == NULL) {
        printf("[SYSTEM ERROR] Failed to allocate memory. Closing system.\n");
        exit(1);
    }

    printf("\n--- Entering Product Details ---\n");
    // Loop to ask the user for details for each of the products they specified
    for (int i = 0; i < product_count; i++) {
        printf("\nProduct #%d (of %d):\n", i + 1, product_count);
        
        // Reading product code (number)
        printf("  Enter unique product code: ");
        if (scanf("%d", &inventory[i].product_code) != 1) {
            printf("[SYSTEM ERROR] Invalid code input. Program terminated.\n"); exit(1);
        }
        
        // Reading product name (string - CANNOT contain spaces)
        printf("  Enter product name: ");
        if (scanf("%49s", inventory[i].product_name) != 1) {
            printf("[SYSTEM ERROR] Input error. Program terminated.\n"); exit(1);
        }
        
        // Reading unit price (float)
        printf("  Enter unit price (e.g., 99.99): ");
        if (scanf("%f", &inventory[i].unit_price) != 1) {
            printf("[SYSTEM ERROR] Invalid price input. Program terminated.\n"); exit(1);
        }
        
        // Reading starting stock quantity 
        printf("  Enter starting stock quantity: ");
        if (scanf("%d", &inventory[i].stock_quantity) != 1) {
            printf("[SYSTEM ERROR] Invalid stock input. Program terminated.\n"); exit(1);
        }
    }
    // The 'do-while' loop runs the menu repeatedly until the user chooses option 5
    do {
        printf("\n\n============ SMART BILLING SYSTEM MENU ============\n");
        printf("1. View Current Inventory Stock\n");
        printf("2. Search for a Product (by code)\n");
        printf("3. Modify Product Details (Update Price or Add Stock)\n"); 
        printf("4. Start New Billing Transaction (Add to Bill)\n");
        printf("5. Finalize Bill and Exit System\n");
        printf("---------------------------------------------------\n");
        printf("Enter your choice (1-5): ");
        
        // Reading the menu choice (number)
        if (scanf("%d", &menu_choice) != 1) {
            printf("\n[INPUT ERROR] Please enter a valid number from the menu.\n");
            menu_choice = 0; // Reset choice to keep the loop going
            continue;
        }

        // The 'switch' statement decides which block of code to run based on 'menu_choice'
        switch(menu_choice) {

            case 1:
                displayProducts(inventory, product_count); // Go to function 1
                break;

            case 2:
                // Go to search function
                printf("\n--- Product Search ---\n");
                printf("Enter product code to look up: ");
                // Reading search code (number)
                if (scanf("%d", &product_code) != 1) {
                    printf("[ERROR] Invalid code input.\n");
                    break;
                }
                found_index = findProductIndex(inventory, product_count, product_code);

                // 'if-else' checks the search result
                if (found_index != -1) {
                    printf("\nProduct Found:\n");
                    // Display details using the found index
                    printf("  Name: %s\n", inventory[found_index].product_name);
                    printf("  Price: %.2f\n", inventory[found_index].unit_price);
                    printf("  Stock Available: %d units\n", inventory[found_index].stock_quantity);
                } else {
                    printf("[INFO] Product code %d was not found in the inventory.\n", product_code);
                }
                break;

            case 3: 
                modifyProductDetails(inventory, product_count); // Go to modification function
                break;
            
            case 4: // Add to Bill
                printf("\n--- Adding Item to Current Bill ---\n");
                printf("Enter product code: ");
                // Reading product code (number)
                if (scanf("%d", &product_code) != 1) {
                    printf("ERROR ! Invalid code input.\n");
                    break;
                }
                found_index = findProductIndex(inventory, product_count, product_code);

                if (found_index == -1) {
                    printf("ERROR ! Invalid code entered. Product not available.\n");
                    break;
                }

                printf("Enter quantity to purchase (Max available: %d): ", inventory[found_index].stock_quantity);
                // Reading quantity to purchase (number)
                if (scanf("%d", &quantity_to_purchase) != 1) {
                    printf("ERROR ! Invalid quantity input.\n");
                    break;
                }

                // 'if' statement checks if quantity is valid
                if (quantity_to_purchase <= 0) {
                    printf("ERROR ! Quantity must be greater than zero. Item not added.\n");
                    break;
                }
                // 'if' statement checks if we have enough stock
                if (quantity_to_purchase > inventory[found_index].stock_quantity) {
                    printf("ERROR! Not enough stock! Only %d units available. Item not added.\n", inventory[found_index].stock_quantity);
                    break;
                }

                // Calculate cost before any discounts
                float item_amount = inventory[found_index].unit_price * quantity_to_purchase;
                gross_total += item_amount; // Add to the total BEFORE discount

                float item_discount = 0.0;

                // 'if-else if-else' logic for conditional discounts
                if (quantity_to_purchase >= 10) {
                    item_discount = 0.10 * item_amount; // 10% discount
                    printf("[DISCOUNT APPLIED] 10%% bulk discount.\n");
                } else if (quantity_to_purchase >= 5) {
                    item_discount = 0.05 * item_amount; // 5% discount
                    printf("[DISCOUNT APPLIED] 5%% discount.\n");
                }
                
                item_amount -= item_discount; // Subtract the discount
                cumulative_discount += item_discount; // Keep track of total discount given
                bill_subtotal += item_amount; // Add the discounted amount to the taxable total

                deductStock(inventory, found_index, quantity_to_purchase); // Update stock after sale

                printf("Item Added: %s (x%d). Cost after discount: %.2f\n", 
                       inventory[found_index].product_name, quantity_to_purchase, item_amount);
                break;

            case 5:
                printf("\nFinalizing transaction and generating bill...\n");
                break; // Exit the switch, allowing the do-while loop to end

            default:
                printf("[WARNING] Please enter a valid menu option (1-5).\n");
        }

    } while(menu_choice != 5); // Loop continues as long as user doesn't choose '5'

    // --- Final Bill Calculation ---
    // Calculate the actual amount the tax is applied to
    float taxable_total = gross_total - cumulative_discount;
    
    // Calculate tax amount
    float tax_amount = taxable_total * GST_RATE;
    // Final total owed by the customer
    final_amount_due = taxable_total + tax_amount;

    printf("\n\n================ FINAL TRANSACTION RECEIPT ================\n");
    printf("Gross Subtotal (Before Discounts):      | %15.2f\n", gross_total); 
    printf("Total Item Discounts Applied:           | - %15.2f\n", cumulative_discount);
    printf("-----------------------------------------------------------\n");
    printf("Net Subtotal (Taxable Amount):          |   %15.2f\n", taxable_total); 
    printf("GST (%.0f%% Tax):                         | + %15.2f\n", GST_RATE * 100, tax_amount);
    printf("-----------------------------------------------------------\n");
    printf("FINAL AMOUNT DUE:                       | %15.2f\n", final_amount_due);
    printf("===========================================================\n");
    printf("Thank you for choosing the Smart Billing System!\n");

    return 0; // Program successfully ends
}