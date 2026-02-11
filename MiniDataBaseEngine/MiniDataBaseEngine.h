#ifndef MINIDATABASEENGINE_H
#define MINIDATABASEENGINE_H

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include "Table.h"

class MiniDatabaseEngine
{
    std::map<std::string, Table> tables;
    Table* current = nullptr;

public:
    void createTable(const std::string& name, const std::vector<Column>& cols);
    void seeTables()const;
    void useTable(const std::string& name);
    void deleteTable(const std::string& name);
    void insertRow(const std::vector<std::string>& values);
    void selectAll();
    void run();
};

#endif
