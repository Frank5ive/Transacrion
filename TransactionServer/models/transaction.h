#pragma once
#include <string>

struct Transaction
{
    int id;
    int user_id;
    double amount;
    std::string type;
    std::string status;
    std::string created_at;
};

bool create_transaction(int user_id, double amount, const std::string &type, const std::string &status = "pending");
