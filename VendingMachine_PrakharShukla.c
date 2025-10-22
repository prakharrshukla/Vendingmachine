
// Header Function
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Admin password 
int password = 1769;

// Minimum stock thresholds for alerts
#define MIN_ME 2    // Minimum stock for Monster Energy
#define MIN_RB 2    // Minimum stock for Red Bull
#define MIN_ZC 2    // Minimum stock for Zero Cola

// Tracks total sales money
float total_amount = 0.0;

// Product quantities 
int quantity_ME = 10;    // Monster Energy quantity
int quantity_RB = 10;    // Red Bull quantity
int quantity_ZC = 10;    // Zero Cola quantity

// Product prices 
float price_ME = 2.50;    // price of Monster Energy
float price_RB = 3.00;    // price of Red Bull
float price_ZC = 3.50;    // price of Zero Cola

// Function declarations
void showProducts(void);           // displays available products
void buyProduct(void);            // handles customer purchases
void adminMode(void);            // handles admin operations
void replenishProducts(void);    // refills stock randomly
void changeProductPrices(void);  // updates product prices
void displayTotalSales(void);    // shows/resets total sales
void displayQuantities(void);    // shows current stock levels

// Shows menu of available products with prices and quantities
void showProducts(void) {
    printf("\nAvailable Products:\n");
    printf("%-25s %-8s %-8s\n", "Product", "Price", "Quantity");
    printf("%-25s %-8.2f %-8d\n", "ME(Monster Energy)", price_ME, quantity_ME);
    printf("%-25s %-8.2f %-8d\n", "RB(Red Bull)", price_RB, quantity_RB);
    printf("%-25s %-8.2f %-8d\n", "ZC(Zero Cola)", price_ZC, quantity_ZC);
}

// Handles the complete purchase process
void buyProduct(void) {
    char choice;          // product selection
    float price = 0.0;    // selected product price
    int selected_qty = 0; // selected product quantity
    float paid = 0.0;     // amount paid so far
    float coin;           // current coin input
    char confirm;         // purchase confirmation

    while(1) {
        // Display products and get selection
        showProducts();
        printf("\nSelect product (M/R/Z) or 0 to cancel: ");
        scanf(" %c", &choice);

        if(choice == '0') {
            printf("Purchase cancelled.\n");
            return;
        }

        // Match product selection
        if(choice == 'M') {
            price = price_ME;
            selected_qty = quantity_ME;
            printf("\nYou selected Monster Energy - Price: %.2f AED\n", price_ME);
        }
        else if(choice == 'R') {
            price = price_RB;
            selected_qty = quantity_RB;
            printf("\nYou selected Red Bull - Price: %.2f AED\n", price_RB);
        }
        else if(choice == 'Z') {
            price = price_ZC;
            selected_qty = quantity_ZC;
            printf("\nYou selected Zero Cola - Price: %.2f AED\n", price_ZC);
        }
        else {
            printf("Invalid choice! Please enter M, R, or Z.\n");
            continue;
        }

        // Check if product is in stock
        if(selected_qty <= 0) {
            printf("Sorry, product is out of stock!\n");
            continue;
        }

        // Confirm purchase
        printf("Confirm purchase? (Y/N): ");
        scanf(" %c", &confirm);
        if(confirm != 'Y' && confirm != 'y') {
            printf("Purchase cancelled.\n");
            continue;
        }

        // Handle payment
        printf("\nPrice: %.2f AED\n", price);
        printf("Please insert coins (1.00, 0.50, 0.25 AED)\n");
        printf("Enter -1 to cancel payment\n");

        while(paid < price) {
            printf("Amount still needed: %.2f AED: ", price - paid);
            scanf("%f", &coin);
            
            if(coin == -1) {
                if(paid > 0) {
                    printf("Purchase cancelled. Please collect your refund: %.2f AED\n", paid);
                }
                return;
            }
            
            // Check for valid coin values with small tolerance for floating point
            if(coin >= 0.99 && coin <= 1.01) {
                paid += 1.0;
            } else if(coin >= 0.49 && coin <= 0.51) {
                paid += 0.5;
            } else if(coin >= 0.24 && coin <= 0.26) {
                paid += 0.25;
            } else if(coin != -1) {
                printf("Invalid coin! Please use 1.00, 0.50, or 0.25 AED only.\n");
            }
        }

        // Update stock and check for low stock alert
        if(choice == 'M') {
            quantity_ME--;
            if(quantity_ME <= MIN_ME)
                printf("\nALERT: Monster Energy stock low (%d items)\n", quantity_ME);
        }
        else if(choice == 'R') {
            quantity_RB--;
            if(quantity_RB <= MIN_RB)
                printf("\nALERT: Red Bull stock low (%d items)\n", quantity_RB);
        }
        else if(choice == 'Z') {
            quantity_ZC--;
            if(quantity_ZC <= MIN_ZC)
                printf("\nALERT: Zero Cola stock low (%d items)\n", quantity_ZC);
        }

        // Update total sales and give change
        total_amount += price;
        printf("\nThank you for your purchase!\n");
        if(paid > price) {
            printf("Please collect your change: %.2f AED\n", paid - price);
        }
        return;
    }
}

// Handles admin functions - requires password
void adminMode(void) {
    int input_pass;
    int choice;
    char c;
    
    // Verify password
    printf("\nEnter admin password: ");
    while(1) {
        if(scanf("%d", &input_pass) != 1) {
            while((c = getchar()) != '\n' && c != EOF); // clear input buffer
            printf("Invalid password format! Please enter numbers only: ");
            continue;
        }
        break;
    }
    
    if(input_pass != password) {
        printf("Incorrect password!\n");
        return;
    }
    
    // Admin menu loop
    while(1) {
        printf("\nAdmin Menu:\n");
        printf("1: Replenish Products\n");
        printf("2: Change Product Prices\n");
        printf("3: Display Total Sales\n");
        printf("4: Display Stock Levels\n");
        printf("0: Exit Admin Mode\n");
        printf("Choice: ");
        
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                replenishProducts();
                break;
            case 2:
                changeProductPrices();
                break;
            case 3:
                displayTotalSales();
                break;
            case 4:
                displayQuantities();
                break;
            case 0:
                return;
            default:
                printf("Invalid choice!\n");
        }
    }
}

// Randomly refills all products [1-20]
void replenishProducts(void) {
    // Initialize random seed
    srand((unsigned int)time(NULL));
    
    // Generate new quantities
    quantity_ME = (rand() % 20) + 1;
    quantity_RB = (rand() % 20) + 1;
    quantity_ZC = (rand() % 20) + 1;
    
    printf("\nProducts have been refilled!\n");
    displayQuantities();
}

// Updates prices for all products
void changeProductPrices(void) {
    printf("\nEnter new prices:\n");
    
    printf("Monster Energy (current: %.2f): ", price_ME);
    scanf("%f", &price_ME);
    
    printf("Red Bull (current: %.2f): ", price_RB);
    scanf("%f", &price_RB);
    
    printf("Zero Cola (current: %.2f): ", price_ZC);
    scanf("%f", &price_ZC);
    
    printf("\nPrices updated successfully!\n");
    showProducts();
}

// Shows and optionally resets total sales
void displayTotalSales(void) {
    int choice;
    
    printf("\nTotal sales: %.2f AED\n", total_amount);
    printf("Reset total to zero? (1 for Yes, 0 for No): ");
    scanf("%d", &choice);
    
    if(choice == 1) {
        total_amount = 0.0;
        printf("Total sales reset to zero.\n");
        printf("Please collect money from machine.\n");
    }
}

// Shows current stock levels with alerts
void displayQuantities(void) {
    printf("\nCurrent Stock Levels:\n");
    printf("%-25s %-8s\n", "Product", "Quantity");
    
    printf("%-25s %-8d", "Monster Energy", quantity_ME);
    if(quantity_ME <= MIN_ME) printf("(LOW STOCK)");
    printf("\n");
    
    printf("%-25s %-8d", "Red Bull", quantity_RB);
    if(quantity_RB <= MIN_RB) printf("(LOW STOCK)");
    printf("\n");
    
    printf("%-25s %-8d", "Zero Cola", quantity_ZC);
    if(quantity_ZC <= MIN_ZC) printf("(LOW STOCK)");
    printf("\n");
}

// Main program loop
int main(void) {
    int choice;
    
    printf("Welcome to the Energy Drinks Vending Machine!\n");
    
    while(1) {
        printf("\nMain Menu:\n");
        printf("1. Purchase Product\n");
        printf("2. Admin Mode\n");
        printf("3. Exit\n");
        printf("Choice: ");
        
        // Better input handling
        if(scanf("%d", &choice) != 1) {
            // Clear input buffer if invalid input
            while(getchar() != '\n');
            printf("Invalid input! Please enter a number.\n");
            continue;
        }
        
        switch(choice) {
            case 1:
                buyProduct();
                break;
            case 2:
                adminMode();
                break;
            case 3:
                printf("\nThank you for using the Energy Drinks Vending Machine!\n");
                return 0;
            default:
                printf("Invalid choice! Please enter 1, 2, or 3.\n");
        }
    }

}
