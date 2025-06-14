#include "../includes/crow_all.h"
#include "database/mysql.h"
#include "config/env.h"
#include "routes/transaction_routes.h"
#include <nlohmann/json.hpp>

int main()
{
    auto env = load_env(".env");

    init_db_connection(
        env["DB_HOST"],
        env["DB_USER"],
        env["DB_PASS"],
        env["DB_NAME"],
        std::stoi(env["DB_PORT"]));

    crow::SimpleApp app;

    // Register transaction routes
    register_transaction_routes(app);

    CROW_ROUTE(app, "/db-test")([]()
                                {
        nlohmann::json j;
        j["mysql_version"] = get_mysql_version();
        return crow::response{j.dump()}; });

    app.port(5000).multithreaded().run();
}
