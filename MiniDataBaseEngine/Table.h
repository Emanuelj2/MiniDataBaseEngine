#ifndef TABLE_H
#define TEBLE_H

#include <string>
#include <vector>

enum DataType
{
	INT,
	TEXT
};

struct Column 
{
	std::string name;
	DataType type;
};

struct Row
{
	std::vector<std::string> values;
};

class Table
{
public:
	//constuctor
	Table(std::string n = "");

	std::string filename() const;
	void save();
	bool load();

	std::string name;
	std::vector<Column> columns;
	std::vector<Row> rows;
};

#endif

