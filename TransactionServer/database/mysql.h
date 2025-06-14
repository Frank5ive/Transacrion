#pragma once
#include <string>
#include <memory>
#include <mysql_connection.h>

extern std::unique_ptr<sql::Connection> con;

std::string get_mysql_version();
void init_db_connection(const std::string &host,
                        const std::string &user,
                        const std::string &pass,
                        const std::string &db_name,
                        int port = 3306);
