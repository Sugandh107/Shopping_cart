#include <stdio.h>
#include <string.h>

struct Item {
    char name[50];
    float price;
    int quantity;
    int quantityToBuy;  // New: Quantity to buy for each item in the cart
};

void displayItems(struct Item items[], int numItems) {
    printf("\nAvailable Items:\n");
    printf("Index\tItem Name\tPrice\tQuantity\n");
    for (int i = 0; i < numItems; i++) {
        printf("%d\t%s\t\t%.2f\t%d\n", i, items[i].name, items[i].price, items[i].quantity);
    }
    printf("\n");
}

int addItemToCart(struct Item items[], int cart[], int numItems, int cartSize) {
    int choice;
    printf("Enter the index of the item you want to add to cart: ");
    scanf("%d", &choice);

    if (choice < 0 || choice >= numItems) {
        printf("Invalid choice!\n");
        return cartSize;
    }

    printf("Enter the quantity you want to buy: ");
    scanf("%d", &items[choice].quantityToBuy);

    if (items[choice].quantityToBuy > items[choice].quantity) {
        printf("Not enough quantity available!\n");
        return cartSize;
    }

    // Deduct the bought quantity and update cart
    items[choice].quantity -= items[choice].quantityToBuy;
    cart[cartSize++] = choice;

    printf("Item added to your cart.\n");
    return cartSize;
}

int removeItemFromCart(struct Item items[], int cart[], int cartSize) {
    if (cartSize == 0) {
        printf("Cart is empty!\n");
        return cartSize;
    }

    printf("Items in your cart:\n");
    printf("Index\tItem Name\tQuantity in Cart\n");
    for (int i = 0; i < cartSize; i++) {
        printf("%d\t%s\t\t%d\n", i, items[cart[i]].name, items[cart[i]].quantityToBuy);
    }

    int choice;
    printf("Enter the index of the item you want to remove from cart: ");
    scanf("%d", &choice);

    if (choice < 0 || choice >= cartSize) {
        printf("Invalid choice!\n");
        return cartSize;
    }

    int itemIndex = cart[choice];
    items[itemIndex].quantity += items[itemIndex].quantityToBuy; // Add back to available items
    for (int i = choice; i < cartSize - 1; i++) {
        cart[i] = cart[i + 1]; // Shift the array to remove the chosen item
    }

    printf("Item removed from your cart.\n");
    return cartSize - 1;
}

void generateBill(struct Item items[], int cart[], int cartSize) {
    float totalAmount = 0.0;
    printf("\nFinal Bill:\n");
    printf("Index\tItem Name\tPrice\tQuantity\tTotal\n");
    for (int i = 0; i < cartSize; i++) {
        int itemIndex = cart[i];
        float itemTotal = items[itemIndex].price * items[itemIndex].quantityToBuy;
        printf("%d\t%s\t\t%.2f\t%d\t\t%.2f\n", i, items[itemIndex].name, items[itemIndex].price, items[itemIndex].quantityToBuy, itemTotal);
        totalAmount += itemTotal;
    }
    printf("Total Amount: %.2f\n", totalAmount);
}

int main() {
    struct Item items[] = {
        {"Pepsi", 20, 25, 0},
        {"Monaco", 10, 15, 0},
        {"Ponds", 25, 20, 0},
        {"Shampoo", 5, 35, 0}
    };

    int numItems = sizeof(items) / sizeof(items[0]);

    displayItems(items, numItems);

    int cart[100]; // Assuming a maximum of 100 items in the cart
    int cartSize = 0;

    int choice;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Add Item to Cart\n");
        printf("2. Remove Item from Cart\n");
        printf("3. Generate Bill\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                cartSize = addItemToCart(items, cart, numItems, cartSize);
                break;
            case 2:
                cartSize = removeItemFromCart(items, cart, cartSize);
                break;
            case 3:
                generateBill(items, cart, cartSize);
                break;
            case 4:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;

}
