#include "Table.h"
#include "string"
#include <fstream> 
#include <sstream>
#include <iostream>

Table::Table(const std::string n = ""): name(n){}

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
}