#include "mysql.h"
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <memory>
#include <iostream>

static sql::mysql::MySQL_Driver *driver = nullptr;

// Define the global connection variable
std::unique_ptr<sql::Connection> con;

void create_transactions_table_if_not_exists()
{
    try
    {
        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        std::string create_table_sql = R"(
            CREATE TABLE IF NOT EXISTS transactions (
                id INT AUTO_INCREMENT PRIMARY KEY,
                user_id INT NOT NULL,
                amount DECIMAL(15, 2) NOT NULL,
                type VARCHAR(50) NOT NULL,
                status VARCHAR(50) NOT NULL,
                created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
            )
        )";
        stmt->execute(create_table_sql);
        std::cout << "[DB] Checked/created 'transactions' table successfully." << std::endl;
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "[DB ERROR] Could not create 'transactions' table: " << e.what() << std::endl;
    }
}

void init_db_connection(const std::string &host,
                        const std::string &user,
                        const std::string &pass,
                        const std::string &db_name,
                        int port)
{
    try
    {
        std::string url = "tcp://" + host + ":" + std::to_string(port);
        driver = sql::mysql::get_mysql_driver_instance();
        con.reset(driver->connect(url, user, pass));
        con->setSchema(db_name);
        std::cout << "[DB] Connected successfully to " << url << std::endl;

        // Auto-create table if missing
        create_transactions_table_if_not_exists();
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "[DB ERROR] " << e.what() << std::endl;
    }
}

std::string get_mysql_version()
{
    try
    {
        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT VERSION()"));
        if (res->next())
        {
            return res->getString(1);
        }
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "[DB ERROR] " << e.what() << std::endl;
    }
    return "unknown";
}
