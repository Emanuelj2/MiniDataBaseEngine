#include "Table.h"
#include <string>
#include <fstream> 
#include <sstream>
#include <iostream>


// THIS IS THE GOAL
// id:INT | name : TEXT | age : INT |
// 1 | Bob | 23 |
// 2 | Alice | 30 |

Table::Table(const std::string n): name(n){}

std::string Table::filename() const
{
	return name + ".tbl";
}

void Table::save()
{
    std::ofstream file(filename());

    // write column header
    for (auto& c : columns)
    {
        file << c.name << ":"
            << (c.type == INT ? "INT" : "TEXT")
            << "|";
    }
    file << "\n";

    // write rows
    for (auto& r : rows)
    {
        for (auto& v : r.values)
        {
            file << v << "|";
        }
        file << "\n";
    }
}

bool Table::load()
{
    std::ifstream file(filename());

    if (!file)
    {
        return false;
    }

    columns.clear();
    rows.clear();

    std::string line;
    std::string token;

    std::getline(file, line);

    std::stringstream schema(line);

    while (std::getline(schema, token, '|'))
    {
        if (token.empty())
        {
            continue;
        }

        auto pos = token.find(':');

        Column c;

        c.name = token.substr(0, pos);
        std::string t = token.substr(pos + 1);
        c.type = (t == "INT") ? INT : TEXT;
        columns.push_back(c);
    }

    while (std::getline(file, line))
    {
        Row r;
        std::stringstream rowss(line);
        while (std::getline(rowss, token, '|'))
        {
            if (!token.empty())
            {
                r.values.push_back(token);
            }
        }
        rows.push_back(r);
    }
    return true;
}
