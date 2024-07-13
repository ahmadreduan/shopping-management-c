#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Define a structure for an item
struct Item {
    char name[50];
    char category[50];
    int quantity;
    float price;
    int purchased; // 0 for not purchased, 1 for purchased
};

// Define a structure for a user
struct User {
    char username[50];
    char password[50];
    struct Item cart[100];
    int cartItemCount;
};

// Maximum number of items and users
const int MAX_ITEMS = 100;
const int MAX_USERS = 10;

// Array to store shopping list items
struct Item shoppingList[100];
int itemCount = 0; // Keep track of the number of items in the list

// Array to store users
struct User users[10];
int userCount = 0; // Keep track of the number of registered users
int loggedInUserIndex = -1; // Keep track of the currently logged-in user

// Function to register a new user
void registerUser() {
    if (userCount == MAX_USERS) {
        printf("User limit reached. Cannot register more users.\n");
        return;
    }
    printf("Enter username: ");
    fgets(users[userCount].username, sizeof(users[userCount].username), stdin);
    users[userCount].username[strcspn(users[userCount].username, "\n")] = '\0';
    printf("Enter password: ");
    fgets(users[userCount].password, sizeof(users[userCount].password), stdin);
    users[userCount].password[strcspn(users[userCount].password, "\n")] = '\0';
    users[userCount].cartItemCount = 0;
    userCount++;
    printf("User registered successfully.\n");
}

// Function to login a user
void loginUser() {
    if (userCount == 0) {
        printf("No users registered. Please register first.\n");
        return;
    }
    char username[50];
    char password[50];
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';
    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            loggedInUserIndex = i;
            printf("Login successful. Welcome, %s!\n", username);
            return;
        }
    }
    printf("Invalid username or password.\n");
}

// Function to logout the current user
void logoutUser() {
    if (loggedInUserIndex == -1) {
        printf("No user is currently logged in.\n");
        return;
    }
    loggedInUserIndex = -1;
    printf("Logout successful.\n");
}

// Function to add an item to the list
void addItem() {
    if (itemCount == MAX_ITEMS) {
        printf("Shopping list is full. Cannot add more items.\n");
        return;
    }
    printf("Enter the name of the item to add: ");
    fgets(shoppingList[itemCount].name, sizeof(shoppingList[itemCount].name), stdin);
    shoppingList[itemCount].name[strcspn(shoppingList[itemCount].name, "\n")] = '\0';
    printf("Enter the category of the item: ");
    fgets(shoppingList[itemCount].category, sizeof(shoppingList[itemCount].category), stdin);
    shoppingList[itemCount].category[strcspn(shoppingList[itemCount].category, "\n")] = '\0';
    printf("Enter the quantity of the item: ");
    scanf("%d", &shoppingList[itemCount].quantity);
    printf("Enter the price of the item: ");
    scanf("%f", &shoppingList[itemCount].price);
    getchar(); // Consume the newline character left in the input buffer
    shoppingList[itemCount].purchased = 0; // Initially, the item is not purchased
    itemCount++;
    printf("Item added to the list.\n");
}

// Function to remove an item from the list
void removeItem() {
    if (itemCount == 0) {
        printf("Shopping list is empty. Nothing to remove.\n");
        return;
    }
    int index;
    printf("Enter the index of the item to remove: ");
    scanf("%d", &index);
    getchar(); // Consume the newline character left in the input buffer

    if (index < 1 || index > itemCount) {
        printf("Invalid index. Please enter a valid index.\n");
        return;
    }

    // Shift items to the left to remove the item at the specified index
    for (int i = index - 1; i < itemCount - 1; i++) {
        shoppingList[i] = shoppingList[i + 1];
    }
    itemCount--;
    printf("Item removed from the list.\n");
}

// Function to update the name of an item in the list
void updateItem() {
    if (itemCount == 0) {
        printf("Shopping list is empty. Nothing to update.\n");
        return;
    }
    int index;
    printf("Enter the index of the item to update: ");
    scanf("%d", &index);
    getchar(); // Consume the newline character left in the input buffer

    if (index < 1 || index > itemCount) {
        printf("Invalid index. Please enter a valid index.\n");
        return;
    }

    printf("Enter the new name for the item: ");
    fgets(shoppingList[index - 1].name, sizeof(shoppingList[index - 1].name), stdin);
    shoppingList[index - 1].name[strcspn(shoppingList[index - 1].name, "\n")] = '\0';
    printf("Enter the new category for the item: ");
    fgets(shoppingList[index - 1].category, sizeof(shoppingList[index - 1].category), stdin);
    shoppingList[index - 1].category[strcspn(shoppingList[index - 1].category, "\n")] = '\0';
    printf("Enter the new quantity for the item: ");
    scanf("%d", &shoppingList[index - 1].quantity);
    printf("Enter the new price for the item: ");
    scanf("%f", &shoppingList[index - 1].price);
    getchar(); // Consume the newline character left in the input buffer
    printf("Item updated.\n");
}

// Function to view the current list of items
void viewList() {
    if (itemCount == 0) {
        printf("Shopping list is empty.\n");
        return;
    }
    printf("Current Shopping List:\n");
    for (int i = 0; i < itemCount; i++) {
        printf("%d. %s - %s - Quantity: %d - Price: %.2f%s\n", i + 1, shoppingList[i].name, shoppingList[i].category, shoppingList[i].quantity, shoppingList[i].price, shoppingList[i].purchased ? " (Purchased)" : "");
    }
}

// Function to search for an item in the list
void searchItem() {
    if (itemCount == 0) {
        printf("Shopping list is empty.\n");
        return;
    }
    char searchName[50];
    printf("Enter the name of the item to search for: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = '\0';

    for (int i = 0; i < itemCount; i++) {
        if (strcmp(shoppingList[i].name, searchName) == 0) {
            printf("Item found at index %d.\n", i + 1);
            return;
        }
    }
    printf("Item not found in the list.\n");
}

// Function to clear the shopping list
void clearList() {
    itemCount = 0;
    printf("Shopping list cleared.\n");
}

// Function to save the shopping list to a file
void saveListToFile() {
    FILE *file = fopen("shopping_list.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    for (int i = 0; i < itemCount; i++) {
        fprintf(file, "%s,%s,%d,%.2f,%d\n", shoppingList[i].name, shoppingList[i].category, shoppingList[i].quantity, shoppingList[i].price, shoppingList[i].purchased);
    }
    fclose(file);
    printf("Shopping list saved to file.\n");
}

// Function to load the shopping list from a file
void loadListFromFile() {
    FILE *file = fopen("shopping_list.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }
    itemCount = 0;
    while (fscanf(file, "%49[^,],%49[^,],%d,%f,%d\n", shoppingList[itemCount].name, shoppingList[itemCount].category, &shoppingList[itemCount].quantity, &shoppingList[itemCount].price, &shoppingList[itemCount].purchased) == 5) {
        itemCount++;
    }
    fclose(file);
    printf("Shopping list loaded from file.\n");
}

// Function to sort the shopping list by item name
void sortList() {
    struct Item temp;
    for (int i = 0; i < itemCount - 1; i++) {
        for (int j = i + 1; j < itemCount; j++) {
            if (strcmp(shoppingList[i].name, shoppingList[j].name) > 0) {
                temp = shoppingList[i];
                shoppingList[i] = shoppingList[j];
                shoppingList[j] = temp;
            }
        }
    }
    printf("Shopping list sorted by item name.\n");
}

// Function to mark an item as purchased
void markItemAsPurchased() {
    if (itemCount == 0) {
        printf("Shopping list is empty. Nothing to mark as purchased.\n");
        return;
    }
    int index;
    printf("Enter the index of the item to mark as purchased: ");
    scanf("%d", &index);
    getchar(); // Consume the newline character left in the input buffer

    if (index < 1 || index > itemCount) {
        printf("Invalid index. Please enter a valid index.\n");
        return;
    }
    shoppingList[index - 1].purchased = 1;
    printf("Item marked as purchased.\n");
}

// Function to unmark an item as purchased
void unmarkItemAsPurchased() {
    if (itemCount == 0) {
        printf("Shopping list is empty. Nothing to unmark as purchased.\n");
        return;
    }
    int index;
    printf("Enter the index of the item to unmark as purchased: ");
    scanf("%d", &index);
    getchar(); // Consume the newline character left in the input buffer

    if (index < 1 || index > itemCount) {
        printf("Invalid index. Please enter a valid index.\n");
        return;
    }
    shoppingList[index - 1].purchased = 0;
    printf("Item unmarked as purchased.\n");
}

// Function to view the purchased items
void viewPurchasedItems() {
    if (itemCount == 0) {
        printf("Shopping list is empty.\n");
        return;
    }
    printf("Purchased Items:\n");
    for (int i = 0; i < itemCount; i++) {
        if (shoppingList[i].purchased) {
            printf("%d. %s - %s - Quantity: %d - Price: %.2f\n", i + 1, shoppingList[i].name, shoppingList[i].category, shoppingList[i].quantity, shoppingList[i].price);
        }
    }
}

// Function to view the unpurchased items
void viewUnpurchasedItems() {
    if (itemCount == 0) {
        printf("Shopping list is empty.\n");
        return;
    }
    printf("Unpurchased Items:\n");
    for (int i = 0; i < itemCount; i++) {
        if (!shoppingList[i].purchased) {
            printf("%d. %s - %s - Quantity: %d - Price: %.2f\n", i + 1, shoppingList[i].name, shoppingList[i].category, shoppingList[i].quantity, shoppingList[i].price);
        }
    }
}

// Function to get the total number of items
void getItemCount() {
    printf("Total number of items: %d\n", itemCount);
}

// Function to add an item to the user's cart
void addToCart() {
    if (loggedInUserIndex == -1) {
        printf("Please log in to add items to your cart.\n");
        return;
    }
    if (itemCount == 0) {
        printf("Shopping list is empty. Nothing to add to the cart.\n");
        return;
    }
    int index;
    printf("Enter the index of the item to add to the cart: ");
    scanf("%d", &index);
    getchar(); // Consume the newline character left in the input buffer

    if (index < 1 || index > itemCount) {
        printf("Invalid index. Please enter a valid index.\n");
        return;
    }
    if (users[loggedInUserIndex].cartItemCount == MAX_ITEMS) {
        printf("Cart is full. Cannot add more items.\n");
        return;
    }
    users[loggedInUserIndex].cart[users[loggedInUserIndex].cartItemCount] = shoppingList[index - 1];
    users[loggedInUserIndex].cartItemCount++;
    printf("Item added to the cart.\n");
}

// Function to view the user's cart
void viewCart() {
    if (loggedInUserIndex == -1) {
        printf("Please log in to view your cart.\n");
        return;
    }
    if (users[loggedInUserIndex].cartItemCount == 0) {
        printf("Your cart is empty.\n");
        return;
    }
    printf("Your Cart:\n");
    for (int i = 0; i < users[loggedInUserIndex].cartItemCount; i++) {
        printf("%d. %s - %s - Quantity: %d - Price: %.2f\n", i + 1, users[loggedInUserIndex].cart[i].name, users[loggedInUserIndex].cart[i].category, users[loggedInUserIndex].cart[i].quantity, users[loggedInUserIndex].cart[i].price);
    }
}

// Function to clear the user's cart
void clearCart() {
    if (loggedInUserIndex == -1) {
        printf("Please log in to clear your cart.\n");
        return;
    }
    users[loggedInUserIndex].cartItemCount = 0;
    printf("Your cart has been cleared.\n");
}

// Function to checkout and clear the cart
void checkout() {
    if (loggedInUserIndex == -1) {
        printf("Please log in to checkout.\n");
        return;
    }
    if (users[loggedInUserIndex].cartItemCount == 0) {
        printf("Your cart is empty. Nothing to checkout.\n");
        return;
    }
    printf("Checking out the following items:\n");
    for (int i = 0; i < users[loggedInUserIndex].cartItemCount; i++) {
        printf("%d. %s - %s - Quantity: %d - Price: %.2f\n", i + 1, users[loggedInUserIndex].cart[i].name, users[loggedInUserIndex].cart[i].category, users[loggedInUserIndex].cart[i].quantity, users[loggedInUserIndex].cart[i].price);
    }
    users[loggedInUserIndex].cartItemCount = 0;
    printf("Checkout complete. Your cart has been cleared.\n");
}

// Main function to drive the program
int main() {
    int choice;

    // Menu-driven loop
    do {
        printf("\nShopping Mall Management\n1. Register User\n2. Login User\n3. Logout User\n4. Add Item to List\n5. Remove Item from List\n6. Update Item\n7. View List\n8. Search Item\n9. Clear List\n10. Save List to File\n11. Load List from File\n12. Sort List\n13. Mark Item as Purchased\n14. Unmark Item as Purchased\n15. View Purchased Items\n16. View Unpurchased Items\n17. Get Item Count\n18. Add Item to Cart\n19. View Cart\n20. Clear Cart\n21. Checkout\n22. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume the newline character left in the input buffer
        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                logoutUser();
                break;
            case 4:
                addItem();
                break;
            case 5:
                removeItem();
                break;
            case 6:
                updateItem();
                break;
            case 7:
                viewList();
                break;
            case 8:
                searchItem();
                break;
            case 9:
                clearList();
                break;
            case 10:
                saveListToFile();
                break;
            case 11:
                loadListFromFile();
                break;
            case 12:
                sortList();
                break;
            case 13:
                markItemAsPurchased();
                break;
            case 14:
                unmarkItemAsPurchased();
                break;
            case 15:
                viewPurchasedItems();
                break;
            case 16:
                viewUnpurchasedItems();
                break;
            case 17:
                getItemCount();
                break;
            case 18:
                addToCart();
                break;
            case 19:
                viewCart();
                break;
            case 20:
                clearCart();
                break;
            case 21:
                checkout();
                break;
            case 22:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 22); // Loop until user chooses to exit
    return 0;
}
