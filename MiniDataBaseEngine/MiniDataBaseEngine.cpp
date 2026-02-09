#include <iostream>
#include <map>
#include "Table.h"
#include <vector>


class MiniDb
{
    std::map<std::string, Table> tables;
    Table* current = nullptr;

public:
    void createTable(const std::string& name, const std::vector<Column>& cols)
    {
        Table t(name);
        t.columns = cols;
        t.save();
        tables[name] = t;
        std::cout << "Table '" << name << "' created.\n";
    }

    void useTable(const std::string& name)
    {
        Table t(name);
        if (!t.load())
        {
            std::cout << "Table not found.\n";
            return;
        }

        tables[name] = t;
        current = &tables[name];
        std::cout << "Using table '" << name << "'.\n";
    }

    void run()
    {
        std::string line;
        while (true)
        {
            std::cout << "db->";
            std::getline(std::cin, line);

            if (line == "exit") break;


        }
    }
 
};


int main()
{
    MiniDb db;

}
