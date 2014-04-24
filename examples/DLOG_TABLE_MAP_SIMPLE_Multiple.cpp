/**
 * DLOG_TABLE_SIMPLE.cpp
 *
 *  Created on: Dec 23, 2013
 *      Author: aravind-local
 */

/*
 * compile with g++ DLOG_TABLE_MAP_SIMPLE_Multiple.cpp -std=c++11
 */

#include "../DLOG_TABLE_MAP.hpp"
#include <vector>

//NOTE: DLOG_TABLE do not have crash support
using namespace std;
int main()
{
	//if 2nd param is not given, environment variable DLOG_OUPUT_FOLDER is used
	DLOG_TABLES_MAP tables("DLOG_TABLE_MAP_SIMPLE_Multiple.html", "./output/");

	//table 1
	{
		TID_PAIR table_fruits = tables.newtable("fruits");
		tables.insert_elem(table_fruits, "Apple", "sold", "100");
		tables.insert_elem(table_fruits, "Apple", "stockleft", "20");
		tables.insert_elem(table_fruits, "Apple", "somevalue", "50");

		tables.insert_elem(table_fruits, "Orange", "sold", "130");
		tables.insert_elem(table_fruits, "Orange", "stockleft", "7");
		//table.insert_elem(table_fruits,"Orange", "somevalue", "60"); //Lets say we dont insert this

		tables.insert_elem(table_fruits, "Coconut", "sold", "120");
		tables.insert_elem(table_fruits, "Coconut", "stockleft", "10");
		tables.insert_elem(table_fruits, "Coconut", "somevalue", "0");
	}

	//table 2
	{
		TID_PAIR table_cars = tables.newtable("cars");

		/*Row 1*/
		tables.insert_elem(table_cars, "Ferrari", "sold", "200");
		tables.insert_elem(table_cars, "Ferrari", "stockleft", "10");
		tables.insert_elem(table_cars, "Ferrari", "somevalue", "50");

		/*Row 2*/
		tables.insert_elem(table_cars, "Tata nano", "sold", "1200");
		tables.insert_elem(table_cars, "Tata nano", "stockleft", "120");
		tables.insert_elem(table_cars, "Tata nano", "somevalue", "530");

		/*Row 3*/
		tables.insert_elem(table_cars, "Jaguar", "sold", "2040");
		tables.insert_elem(table_cars, "Jaguar", "stockleft", "130");
		tables.insert_elem(table_cars, "Jaguar", "somevalue", "520");
	}

	tables.html_dump();

	return 0;
}

