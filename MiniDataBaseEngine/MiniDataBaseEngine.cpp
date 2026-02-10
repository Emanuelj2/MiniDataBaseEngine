#include "MiniDatabaseEngine.h"
#include <cctype>

void MiniDatabaseEngine::createTable(const std::string& name,
    const std::vector<Column>& cols)
{
    Table t(name);
    t.columns = cols;
    t.save();
    tables[name] = t;
    std::cout << "Table '" << name << "' created.\n";
}

void MiniDatabaseEngine::seeTables()const
{
    if (tables.empty())
    {
        std::cout << "There are no tables\n";
        return;
    }

    std::cout << "Tabels\n";
    for (auto t : tables)
    {
        std::cout << "- " << t.first << "\n";
    }
}

void MiniDatabaseEngine::useTable(const std::string& name)
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

void MiniDatabaseEngine::insertRow(const std::vector<std::string>& values)
{
    if (!current)
    {
        std::cout << "No table selected\n";
        return;
    }

    if (values.size() != current->columns.size())
    {
        std::cout << "Column count does not match\n";
        return;
    }

    for (size_t i = 0; i < values.size(); i++)
    {
        if (current->columns[i].type == INT)
        {
            for (char c : values[i])
            {
                if (!isdigit(c))
                {
                    std::cout << "Invalid INT value\n";
                    return;
                }
            }
        }
    }

    Row r;
    r.values = values;
    current->rows.push_back(r);
    current->save();
    std::cout << "Row inserted\n";
}

void MiniDatabaseEngine::selectAll()
{
    if (!current)
    {
        std::cout << "No table selected.\n";
        return;
    }

    for (auto& c : current->columns)
        std::cout << c.name << "\t";
    std::cout << "\n";

    for (auto& r : current->rows)
    {
        for (auto& v : r.values)
            std::cout << v << "\t";
        std::cout << "\n";
    }
}

void MiniDatabaseEngine::run()
{
    std::string line;

    while (true)
    {
        std::cout << "db > ";
        std::getline(std::cin, line);

        if (line == "EXIT") break;

        else if (line.find("CREATE") == 0)
        {
            auto p1 = line.find("(");
            auto p2 = line.find(")");

            std::string name = line.substr(7, p1 - 7);
            name.erase(name.find_last_not_of(" ") + 1);

            std::string cols = line.substr(p1 + 1, p2 - p1 - 1);
            std::stringstream ss(cols);
            std::vector<Column> columns;

            std::string part;
            while (std::getline(ss, part, ','))
            {
                std::stringstream ps(part);
                Column c;
                std::string type;
                ps >> c.name >> type;
                c.type = (type == "INT") ? INT : TEXT;
                columns.push_back(c);
            }

            createTable(name, columns);
        }
        else if (line == "SHOW TABLES")
        {
            seeTables();
        }

        else if (line.find("USE") == 0)
        {
            std::string name = line.substr(4);
            useTable(name);
        }

        else if (line.find("INSERT") == 0)
        {
            auto p1 = line.find("(");
            auto p2 = line.find(")");

            std::string vals = line.substr(p1 + 1, p2 - p1 - 1);
            std::stringstream ss(vals);
            std::vector<std::string> values;
            std::string v;

            while (std::getline(ss, v, ','))
            {
                v.erase(0, v.find_first_not_of(" "));
                values.push_back(v);
            }

            insertRow(values);
        }

        else if (line == "SELECT *")
        {
            selectAll();
        }
        else
        {
            std::cout << "Invalid command.\n";
        }
    }
}
