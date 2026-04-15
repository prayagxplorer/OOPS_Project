#ifndef INVENTORY_H
#define INVENTORY_H

#include "Item.h"
#include <vector>
#include <string>

class Inventory {
private:
    std::vector<Item> items;
    std::string dataFile;

    // Helper to find an item by ID
    // Returns index in the vector, or -1 if not found
    int findItemIndex(int id) const;

public:
    Inventory(const std::string& filename);

    bool addItem(int id, const std::string& name, int quantity, double price, std::string& errorMsg);
    std::vector<Item> getAllItems() const;
    bool searchItem(int id, Item& outItem) const;
    bool updateItem(int id, const std::string& newName, int newQuantity, double newPrice, std::string& errorMsg);
    bool deleteItem(int id, std::string& errorMsg);
    
    // File I/O
    void loadFromFile();
    void saveToFile() const;
};

#endif // INVENTORY_H
