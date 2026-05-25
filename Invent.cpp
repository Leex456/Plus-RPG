#include <iostream>
using namespace std;

// Node
struct Item {
    string name;
    Item* next;
};

class Inventory {

private:
    Item* head;

public:

    // Constructor
    Inventory() {
        head = NULL;
    }

    // Add item
    void addItem(string itemName) {

        Item* newItem = new Item;

        newItem->name = itemName;
        newItem->next = NULL;

        // First item
        if (head == NULL) {
            head = newItem;
        }
        else {

            Item* temp = head;

            while (temp->next != NULL) {
                temp = temp->next;
            }

            temp->next = newItem;
        }

        cout << itemName << " added!\n";
    }

    // Show inventory
    void showInventory() {

        if (head == NULL) {
            cout << "Inventory empty.\n";
            return;
        }

        Item* temp = head;

        cout << "\nInventory:\n";

        while (temp != NULL) {

            cout << "- " << temp->name << endl;

            temp = temp->next;
        }
    }

    // Remove item
    void removeItem(string itemName) {

        // Empty inventory
        if (head == NULL) {
            cout << "Inventory empty.\n";
            return;
        }

        // Remove first item
        if (head->name == itemName) {

            Item* temp = head;

            head = head->next;

            delete temp;

            cout << itemName << " removed!\n";

            return;
        }

        Item* current = head;

        while (current->next != NULL &&
               current->next->name != itemName) {

            current = current->next;
        }

        // Found item
        if (current->next != NULL) {

            Item* temp = current->next;

            current->next = current->next->next;

            delete temp;

            cout << itemName << " removed!\n";
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