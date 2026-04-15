#include "Item.h"
#include <iostream>
#include <iomanip>
#include <sstream>

// Default Constructor
Item::Item() : id(0), name(""), quantity(0), price(0.0) {}

// Parameterized Constructor
Item::Item(int id, std::string name, int quantity, double price)
    : id(id), name(name), quantity(quantity), price(price) {}

// Getters
int Item::getId() const { return id; }
std::string Item::getName() const { return name; }
int Item::getQuantity() const { return quantity; }
double Item::getPrice() const { return price; }

// Setters
void Item::setName(const std::string& newName) { name = newName; }
void Item::setQuantity(int newQuantity) { quantity = newQuantity; }
void Item::setPrice(double newPrice) { price = newPrice; }

// Display function
void Item::display() const {
    std::cout << std::left << std::setw(10) << id 
              << std::setw(20) << name 
              << std::setw(10) << quantity 
              << "$" << std::fixed << std::setprecision(2) << price << std::endl;
}

// Convert to CSV format for storing
std::string Item::toCSV() const {
    std::stringstream ss;
    ss << id << "," << name << "," << quantity << "," << price;
    return ss.str();
}

nlohmann::json Item::toJson() const {
    return {
        {"id", id},
        {"name", name},
        {"quantity", quantity},
        {"price", price}
    };
}
