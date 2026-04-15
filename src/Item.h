#ifndef ITEM_H
#define ITEM_H

#include <string>
#include "json.hpp"

class Item {
private:
    int id;
    std::string name;
    int quantity;
    double price;

public:
    // Constructors
    Item();
    Item(int id, std::string name, int quantity, double price);

    // Getters
    int getId() const;
    std::string getName() const;
    int getQuantity() const;
    double getPrice() const;

    // Setters
    void setName(const std::string& name);
    void setQuantity(int quantity);
    void setPrice(double price);

    // Helpers
    void display() const;
    std::string toCSV() const;
    nlohmann::json toJson() const;
};

#endif // ITEM_H
