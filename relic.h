#ifndef RELIC_H
#define RELIC_H

#include <iostream>
#include <string>

using namespace std;

struct RelicInv {
    string name;
    RelicInv* next;
};

class Relic;
int countRelic(Relic& rec);
void displayNumberedRelic(Relic& rec);
string getRelicAt(Relic& rec, int targetIndex);

class Relic {
private:
    RelicInv* head;

public:
    Relic() {
        head = NULL;
    }

    void addItem(string itemName) {
        RelicInv* newItem = new RelicInv;
        newItem->name = itemName;
        newItem->next = NULL;

        if (head == NULL) {
            head = newItem;
        } else {
            RelicInv* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newItem;
        }
        cout << itemName << " added!\n";
    }

    void showRelic() {
        if (head == NULL) {
            cout << "Inventory empty.\n";
            return;
        }
        RelicInv* temp = head;
        cout << "\nInventory:\n";
        while (temp != NULL) {
            cout << "- " << temp->name << endl;
            temp = temp->next;
        }
    }

    void removeRelic(string itemName) {
        if (head == NULL) {
            cout << "Inventory empty.\n";
            return;
        }

        if (head->name == itemName) {
            RelicInv* temp = head;
            head = head->next;
            delete temp;
            cout << itemName << " removed!\n";
            return;
        }

        RelicInv* current = head;
        while (current->next != NULL && current->next->name != itemName) {
            current = current->next;
        }

        if (current->next != NULL) {
            RelicInv* temp = current->next;
            current->next = current->next->next;
            delete temp;
            cout << itemName << " removed!\n";
        } else {
            cout << "Item not found.\n";
        }
    }

    void insertRelic(string itemName, int position = 1) {
        RelicInv* newItem = new RelicInv;
        newItem->name = itemName;
        newItem->next = NULL;

        if (position <= 1 || head == NULL) {
            newItem->next = head;
            head = newItem;
            return;
        }

        RelicInv* current = head;
        int currentPosition = 1;
        while (current->next != NULL && currentPosition < position - 1) {
            current = current->next;
            currentPosition++;
        }

        newItem->next = current->next;
        current->next = newItem;
    }

    int length() {
        int count = 0;
        RelicInv* temp = head;
        while (temp != NULL) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    friend int countRelic(Relic& rec);
    friend void displayNumberedRelic(Relic& rec);
    friend string getRelicAt(Relic& rec, int targetIndex);
};

#endif