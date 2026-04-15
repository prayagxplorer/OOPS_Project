#include <iostream>
#include <string>
#include "httplib.h"
#include "json.hpp"
#include "Inventory.h"

using json = nlohmann::json;

int main() {
    Inventory inventory("inventory_data.csv");
    httplib::Server svr;

    // Serve static files from the "public" directory
    auto ret = svr.set_mount_point("/", "./public");
    if (!ret) {
        std::cerr << "The directory './public' doesn't exist. Please create it." << std::endl;
        return 1;
    }

    // GET /api/items - Retrieve all items
    svr.Get("/api/items", [&](const httplib::Request& req, httplib::Response& res) {
        std::vector<Item> items = inventory.getAllItems();
        json j_items = json::array();
        for (const auto& item : items) {
            j_items.push_back(item.toJson());
        }
        res.set_content(j_items.dump(), "application/json");
    });

    // POST /api/items - Add a new item
    svr.Post("/api/items", [&](const httplib::Request& req, httplib::Response& res) {
        try {
            auto j = json::parse(req.body);
            std::string errMsg;
            if (inventory.addItem(j["id"], j["name"], j["quantity"], j["price"], errMsg)) {
                res.status = 201; // Created
                res.set_content(R"({"message": "Item added successfully"})", "application/json");
            } else {
                res.status = 400; // Bad Request
                json errRes;
                errRes["error"] = errMsg;
                res.set_content(errRes.dump(), "application/json");
            }
        } catch (const std::exception& e) {
            res.status = 400;
            res.set_content(R"({"error": "Invalid JSON format"})", "application/json");
        }
    });

    // DELETE /api/items/:id - Delete an item
    svr.Delete(R"(/api/items/(\d+))", [&](const httplib::Request& req, httplib::Response& res) {
        int id = std::stoi(req.matches[1]);
        std::string errMsg;
        if (inventory.deleteItem(id, errMsg)) {
            res.status = 200;
            res.set_content(R"({"message": "Item deleted successfully"})", "application/json");
        } else {
            res.status = 404;
            json errRes;
            errRes["error"] = errMsg;
            res.set_content(errRes.dump(), "application/json");
        }
    });

    // PUT /api/items/:id - Update an item
    svr.Put(R"(/api/items/(\d+))", [&](const httplib::Request& req, httplib::Response& res) {
        try {
            int id = std::stoi(req.matches[1]);
            auto j = json::parse(req.body);
            std::string errMsg;

            std::string newName = j.contains("name") ? j["name"].get<std::string>() : "";
            int newQuantity = j.contains("quantity") ? j["quantity"].get<int>() : -1;
            double newPrice = j.contains("price") ? j["price"].get<double>() : -1.0;

            if (inventory.updateItem(id, newName, newQuantity, newPrice, errMsg)) {
                res.status = 200;
                res.set_content(R"({"message": "Item updated successfully"})", "application/json");
            } else {
                res.status = 404;
                json errRes;
                errRes["error"] = errMsg;
                res.set_content(errRes.dump(), "application/json");
            }
        } catch (const std::exception& e) {
            res.status = 400;
            res.set_content(R"({"error": "Invalid request"})", "application/json");
        }
    });

    std::cout << "Starting web server on http://localhost:8080..." << std::endl;
    svr.listen("0.0.0.0", 8080);
    
    return 0;
}
