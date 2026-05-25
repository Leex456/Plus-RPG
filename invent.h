#ifndef INVENT_H
#define INVENT_H

#include <iostream>
#include <string>

using namespace std;

struct Item {
    string name;
    Item* next;
};

class Inventory;
int countPotions(Inventory& inv);
void displayNumberedPotions(Inventory& inv);
string getPotionAt(Inventory& inv, int targetIndex);

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
        if (head == NULL) {
            cout << "Inventory empty.\n";
            return;
        }

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

    // Grant exclusive private access to the battle.cpp helper functions
    friend int countPotions(Inventory& inv);
    friend void displayNumberedPotions(Inventory& inv);
    friend string getPotionAt(Inventory& inv, int targetIndex);
};

#endif