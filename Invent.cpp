#include <iostream>
using namespace std;

// Node structure
struct Item {
    string name;
    Item* next;
};

// Inventory class
class Inventory {
private:
    Item* head;

public:
    // Constructor
    Inventory() {
        head = NULL;
    }

    // Add item to inventory
    void addItem(string itemName) {
        Item* newItem = new Item();

        newItem->name = itemName;
        newItem->next = NULL;

        // If inventory empty
        if (head == NULL) {
            head = newItem;
        }
        else {
            // Go to last node
            Item* temp = head;

            while (temp->next != NULL) {
                temp = temp->next;
            }

            temp->next = newItem;
        }

        cout << itemName << " added to inventory.\n";
    }

    // Display inventory
    void showInventory() {
        if (head == NULL) {
            cout << "Inventory is empty.\n";
            return;
        }

        Item* temp = head;

        cout << "\n=== INVENTORY ===\n";

        int index = 1;

        while (temp != NULL) {
            cout << index << ". " << temp->name << endl;
            temp = temp->next;
            index++;
        }
    }

    // Remove item
    void removeItem(string itemName) {
        if (head == NULL) {
            cout << "Inventory is empty.\n";
            return;
        }

        // Remove first item
        if (head->name == itemName) {
            Item* deleteNode = head;
            head = head->next;

            delete deleteNode;

            cout << itemName << " removed.\n";
            return;
        }

        Item* temp = head;

        while (temp->next != NULL &&
               temp->next->name != itemName) {
            temp = temp->next;
        }

        // Item found
        if (temp->next != NULL) {
            Item* deleteNode = temp->next;

            temp->next = temp->next->next;

            delete deleteNode;

            cout << itemName << " removed.\n";
        }
        else {
            cout << "Item not found.\n";
        }
    }
};

int main() {

    Inventory bag;

    bag.addItem("Sword");
    bag.addItem("Potion");
    bag.addItem("Shield");

    bag.showInventory();

    cout << endl;

    bag.removeItem("Potion");

    bag.showInventory();

    return 0;
}