/*
 * bar_graph.cpp
 *
 *  Created on: Dec 23, 2013
 *      Author: aravind-local
 */



/*
 * compile with g++ bar_graph_multiple.cpp -std=c++11
 */

#include "../DLOG_TABLE.hpp"
#include <vector>

//NOTE: DLOG_BAR_GRAPH requires the data to be in dlog table
using namespace std;

//The only thing to be done is call the function tables.show_graph() for the tables you need to show graph

int main()
{
	//if 2nd param is not given, environment variable DLOG_OUPUT_FOLDER is used
	DLOG_TABLES tables("bar_graph_multiple.html", "./output/");

	//table 1
	{
		TID table_fruits = tables.newtable("fruits");

		/*The header row*/
		vector<string> head_row;
		head_row.push_back("item");
		head_row.push_back("sold");
		head_row.push_back("stockleft");
		head_row.push_back("somevalue");
		tables.insert_row(table_fruits, head_row);

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
		tables.show_graph(table_fruits); //Show graph for fruits
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

	//table 3
	{
		TID table_currency = tables.newtable("currency");

		/*The header row*/
		vector<string> head_row;
		head_row.push_back("item");
		head_row.push_back("sold");
		head_row.push_back("stockleft");
		head_row.push_back("somevalue");
		tables.insert_head_row(table_currency, head_row);

		/*Row 1*/
		vector<string> row1;
		row1.push_back("INR");
		row1.push_back("200");
		row1.push_back("10");
		row1.push_back("50");
		tables.insert_row(table_currency, row1);

		/*Row 2*/
		vector<string> row2;
		row2.push_back("USD");
		row2.push_back("10");
		row2.push_back("10");
		row2.push_back("50");
		tables.insert_row(table_currency, row2);

		/*Row 3*/
		vector<string> row3;
		row3.push_back("EUR");
		row3.push_back("2");
		row3.push_back("13");
		row3.push_back("15");
		tables.insert_row(table_currency, row3);
		tables.show_graph(table_currency); //Show graph for fruits
	}

	tables.html_dump();

	return 0;
}

