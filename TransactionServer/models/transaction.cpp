#include "transaction.h"
#include "../database/mysql.h"
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <memory>
#include <iostream>

extern std::unique_ptr<sql::Connection> con;

/**
 * @brief Creates a new transaction record in the database
 *
 * This function inserts a new transaction entry into the transactions table
 * with the specified user ID, amount, type and status. It uses a prepared
 * statement to safely handle SQL injection prevention.
 *
 * @param user_id The ID of the user making the transaction
 * @param amount The monetary value of the transaction
 * @param type The type of transaction (e.g., "deposit", "withdrawal")
 * @param status The current status of the transaction (e.g., "pending", "completed")
 *
 * @return true if the transaction was successfully created in the database,
 *         false if there was a database error during insertion
 *
 * @throws sql::SQLException Caught internally and logged to stderr
 *
 * @note This function requires an established database connection (con)
 * @see Transaction table schema should have columns: user_id, amount, type, status
 */
bool create_transaction(int user_id, double amount, const std::string &type, const std::string &status)
{
    try
    {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            con->prepareStatement("INSERT INTO transactions (user_id, amount, type, status) VALUES (?, ?, ?, ?)"));
        pstmt->setInt(1, user_id);
        pstmt->setDouble(2, amount);
        pstmt->setString(3, type);
        pstmt->setString(4, status);
        pstmt->executeUpdate();
        return true;
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "[DB ERROR] " << e.what() << std::endl;
        return false;
    }
}
