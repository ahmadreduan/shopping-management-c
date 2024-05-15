#include <stdio.h>
#include <string.h>

// Define a structure for an item
struct Item {
    char name[50];
};

// Maximum number of items
const int MAX_ITEMS = 100;

// Array to store shopping list items
struct Item shoppingList[100];
int itemCount = 0; // Keep track of the number of items in the list

// Function to add an item to the list
void addItem() {
    if (itemCount == MAX_ITEMS) {
        printf("Shopping list is full. Cannot add more items.\n");
        return;
    }
    printf("Enter the name of the item to add: ");
    fgets(shoppingList[itemCount].name, sizeof(shoppingList[itemCount].name), stdin);
    // Remove the newline character from the input
    shoppingList[itemCount].name[strcspn(shoppingList[itemCount].name, "\n")] = '\0';
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
        strcpy(shoppingList[i].name, shoppingList[i + 1].name);
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
    // Remove the newline character from the input
    shoppingList[index - 1].name[strcspn(shoppingList[index - 1].name, "\n")] = '\0';
    printf("Item name updated.\n");
}

// Function to view the current list of items
void viewList() {
    if (itemCount == 0) {
        printf("Shopping list is empty.\n");
        return;
    }
    printf("Current Shopping List:\n");
    for (int i = 0; i < itemCount; i++)
        printf("%d. %s\n", i + 1, shoppingList[i].name);
}

// Main function to drive the program
int main() {
    int choice;

    // Menu-driven loop
    do {
        printf("\nShopping List Management\n1. Add Item\n2. Remove Item\n3. Update Item\n4. View List\n5. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume the newline character left in the input buffer
        switch (choice) {
            case 1:
                addItem();
                break;
            case 2:
                removeItem();
                break;
            case 3:
                updateItem();
                break;
            case 4:
                viewList();
                break;
            case 5:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5); // Loop until user chooses to exit
    return 0;
}

