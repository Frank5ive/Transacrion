#include "transaction_routes.h"
#include "../models/transaction.h"
#include <nlohmann/json.hpp>
#include <iostream>

void register_transaction_routes(crow::SimpleApp &app)
{
    std::cout << "[DEBUG] Registering transaction routes" << std::endl;

    CROW_ROUTE(app, "/transaction/create").methods(crow::HTTPMethod::POST)([](const crow::request &req)
                                                                           {
        std::cout << "[DEBUG] Received transaction create request" << std::endl;
        
        try {
            std::cout << "[DEBUG] Request body: " << req.body << std::endl;
            auto body = nlohmann::json::parse(req.body);
            
            int user_id = body["user_id"];
            std::cout << "[DEBUG] Parsed user_id: " << user_id << std::endl;
            
            double amount = body["amount"];
            std::cout << "[DEBUG] Parsed amount: " << amount << std::endl;
            
            std::string type = body["type"];
            std::cout << "[DEBUG] Parsed type: " << type << std::endl;

            std::cout << "[DEBUG] Attempting to create transaction..." << std::endl;
            bool success = create_transaction(user_id, amount, type);

            if (success) {
                std::cout << "[DEBUG] Transaction created successfully" << std::endl;
                return crow::response(200, "Transaction created");
            } else {
                std::cout << "[DEBUG] Failed to create transaction" << std::endl;
                return crow::response(500, "Failed to create transaction");
            }
        }
        catch (const std::exception &e) {
            std::cout << "[DEBUG] Exception caught: " << e.what() << std::endl;
            return crow::response(400, std::string("Invalid JSON: ") + e.what());
        } });
}
