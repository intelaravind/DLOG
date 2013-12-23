/**
 * DLOG_TABLE_SIMPLE.cpp
 *
 *  Created on: Dec 23, 2013
 *      Author: aravind-local
 */

/*
 * compile with g++ DLOG_TABLE_SIMPLE2_Multiple.cpp -std=c++11
 */

#include "../DLOG_TABLE.hpp"
#include <vector>

//NOTE: DLOG_TABLE do not have crash support
using namespace std;

int main()
{
	//if 2nd param is not given, environment variable DLOG_OUPUT_FOLDER is used
	DLOG_TABLES tables("DLOG_TABLE_SIMPLE2_Multiple.html", "./output/");

	//table 1
	{
		TID table_fruits = tables.newtable("fruits");

		/*The header row*/
		vector<string> head_row;
		head_row.push_back("item");
		head_row.push_back("sold");
		head_row.push_back("stockleft");
		head_row.push_back("somevalue");
		tables.insert_head_row(table_fruits, head_row);

		/*Row 1*/
		vector<string> row1;
		row1.push_back("Apple");
		row1.push_back("200");
		row1.push_back("10");
		row1.push_back("50");
		tables.insert_row(table_fruits, row1);

		/*Row 2*/
		vector<string> row2;
		row2.push_back("Orange");
		row2.push_back("1200");
		row2.push_back("120");
		row2.push_back("530");
		tables.insert_row(table_fruits, row2);

		/*Row 3*/
		vector<string> row3;
		row3.push_back("Grapes");
		row3.push_back("2040");
		row3.push_back("130");
		row3.push_back("520");
		tables.insert_row(table_fruits, row3);
	}


	//table 2
	{
		TID table_cars = tables.newtable("cars");

		/*The header row*/
		vector<string> head_row;
		head_row.push_back("item");
		head_row.push_back("sold");
		head_row.push_back("stockleft");
		head_row.push_back("somevalue");
		tables.insert_head_row(table_cars, head_row);

		/*Row 1*/
		vector<string> row1;
		row1.push_back("Ferrari");
		row1.push_back("200");
		row1.push_back("10");
		row1.push_back("50");
		tables.insert_row(table_cars, row1);

		/*Row 2*/
		vector<string> row2;
		row2.push_back("Tata nano");
		row2.push_back("1200");
		row2.push_back("120");
		row2.push_back("530");
		tables.insert_row(table_cars, row2);

		/*Row 3*/
		vector<string> row3;
		row3.push_back("Jaguar");
		row3.push_back("2040");
		row3.push_back("130");
		row3.push_back("520");
		tables.insert_row(table_cars, row3);
	}

	tables.html_dump();

	return 0;
}

