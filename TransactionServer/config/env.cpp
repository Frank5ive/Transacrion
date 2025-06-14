#include "env.h"
#include <fstream>
#include <sstream>

std::map<std::string, std::string> load_env(const std::string &filename)
{
    std::map<std::string, std::string> env;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#')
            continue;
        size_t eq = line.find('=');
        if (eq != std::string::npos)
        {
            std::string key = line.substr(0, eq);
            std::string value = line.substr(eq + 1);
            env[key] = value;
        }
    }

    return env;
}
