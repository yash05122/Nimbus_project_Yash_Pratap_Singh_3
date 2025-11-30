Smart Inventory Billing System

A console-based inventory management and billing application developed in C, designed to demonstrate core programming concepts like Structures, Pointers, Dynamic Memory Allocation, and Conditional Logic.

Features

This system provides a full-cycle solution for inventory management, stock updates, and sales transactions:

  * Dynamic Inventory Allocation: Uses `malloc` for dynamic memory allocation.
  * Inventory Management: Displays current stock, including product code, name, price, and quantity.
  * Search & Update: Users can search and modify product details (price or stock) by its unique code.
  * Sales Transactions: Allows for multi-item billing in a single session.
  * Stock Validation: Prevents sales if the requested quantity exceeds the available stock.
  * Conditional Discounts: Automatically applies discounts based on the quantity purchased:
      * 5% Discount: For quantities of 5 or more.
      * 10% Discount: For quantities of 10 or more.
  * Final Bill Generation: Calculates and displays a detailed receipt, including Gross Total, Discounts, Net Subtotal, GST (18% Tax), and the Final Amount Due.

-----

## Technologies Used

  * Language: C
  * IDE: VS CODE
  * Compiler: MinGW
  * Core Concepts: Structures, Pointers, Dynamic Arrays, Modular Programming (using `.c` and `.h` files).

-----

## Installation and Setup

This project is built using modular programming, split across several source files (`.c`), which requires a C compiler (like GCC) to link them together into a single executable program.

### Prerequisites

You must have the GCC (GNU Compiler Collection) installed on your system.

### Compilation

1.  Place all the project files (`core.c`, `main.c`, `search.c`, `transaction.c`, and `project.h`) into the same folder.

2.  Open your Terminal or Command Prompt and navigate to the project directory.

3.  Run the following command to compile and link the files:

    ```bash
    gcc core.c main.c search.c transaction.c -o program.exe
    ```

      * This command creates the executable file named `program.exe`.
      * Note: The header file (`project.h`) is included in the source files, not in the compilation command.

### Running the Program

Execute the compiled program from your terminal:

```bash
./program.exe
```

-----

## Usage Guide

Upon starting, you'll be prompted to enter the initial number of products, followed by their details (Code, Name, Price, Stock).

The main menu will then appear for operations:

| Menu Option | Description |
| :--- | :--- |
| 1. View Current Inventory Stock | Displays a formatted table of all products. |
| 2. Search for a Product | Finds and displays details using its unique code. |
| 3. Modify Product Details | Allows updating the unit price or adding stock. |
| 4. Start New Billing Transaction | Begins the multi-item sales process. |
| 5. Finalize Bill and Exit System | Calculates the final bill, prints the receipt, and terminates the program. |

-----

##  Contribution

If you find an issue or have suggestions for improvement, please open an issue or submit a pull request.

## License

This project is for educational purposes only.

