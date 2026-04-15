#include "Inventory.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

Inventory::Inventory(const std::string& filename) : dataFile(filename) {
    loadFromFile();
}

int Inventory::findItemIndex(int id) const {
    for (size_t i = 0; i < items.size(); ++i) {
        if (items[i].getId() == id) {
            return i;
        }
    }
    return -1;
}

bool Inventory::addItem(int id, const std::string& name, int quantity, double price, std::string& errorMsg) {
    if (findItemIndex(id) != -1) {
        errorMsg = "Item with ID already exists.";
        return false;
    }
    items.push_back(Item(id, name, quantity, price));
    saveToFile();
    return true;
}

std::vector<Item> Inventory::getAllItems() const {
    return items;
}

bool Inventory::searchItem(int id, Item& outItem) const {
    int index = findItemIndex(id);
    if (index != -1) {
        outItem = items[index];
        return true;
    }
    return false;
}

bool Inventory::updateItem(int id, const std::string& newName, int newQuantity, double newPrice, std::string& errorMsg) {
    int index = findItemIndex(id);
    if (index != -1) {
        if (!newName.empty()) {
            items[index].setName(newName);
        }
        if (newQuantity >= 0) {
            items[index].setQuantity(newQuantity);
        }
        if (newPrice >= 0.0) {
            items[index].setPrice(newPrice);
        }
        saveToFile();
        return true;
    } else {
        errorMsg = "Item not found.";
        return false;
    }
}

bool Inventory::deleteItem(int id, std::string& errorMsg) {
    int index = findItemIndex(id);
    if (index != -1) {
        items.erase(items.begin() + index);
        saveToFile();
        return true;
    } else {
        errorMsg = "Item not found.";
        return false;
    }
}

void Inventory::loadFromFile() {
    std::ifstream file(dataFile);
    if (!file.is_open()) {
        // File might not exist yet, which is fine
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string token;
        
        int id, quantity;
        std::string name;
        double price;

        std::getline(ss, token, ',');
        id = std::stoi(token);

        std::getline(ss, name, ',');

        std::getline(ss, token, ',');
        quantity = std::stoi(token);

        std::getline(ss, token, ',');
        price = std::stod(token);

        items.push_back(Item(id, name, quantity, price));
    }
    file.close();
}

void Inventory::saveToFile() const {
    std::ofstream file(dataFile, std::ios::trunc);
    if (!file.is_open()) {
        std::cout << "Error: Could not open file for writing.\n";
        return;
    }

    for (const auto& item : items) {
        file << item.toCSV() << "\n";
    }
    file.close();
}
