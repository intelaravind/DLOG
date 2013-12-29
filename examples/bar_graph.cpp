/*
 * bar_graph.cpp
 *
 *  Created on: Dec 23, 2013
 *      Author: aravind-local
 */



/*
 * compile with g++ bar_graph.cpp -std=c++11
 */

#include "../DLOG_TABLE.hpp"
#include <vector>

//NOTE: DLOG_BAR_GRAPH requires the data to be in dlog table
using namespace std;

//The only thing to be done is table.drawGraph = 1;

int main()
{
	//if 3rd param is not given, environment variable DLOG_OUPUT_FOLDER is used
	DLOG_TABLE table("bar_graph.html", "fruits", "./output/");

	/*The header row*/
	vector<string> head_row;
	head_row.push_back("item");
	head_row.push_back("sold");
	head_row.push_back("stockleft");
	head_row.push_back("somevalue");
	table.insert_row(head_row);

	/*Row 1*/
	vector<string> row1;
	row1.push_back("Apple");
	row1.push_back("200");
	row1.push_back("110");
	row1.push_back("510");
	table.insert_row(row1);

	/*Row 2*/
	vector<string> row2;
	row2.push_back("Orange");
	row2.push_back("1200");
	row2.push_back("120");
	row2.push_back("530");
	table.insert_row(row2);

	/*Row 3*/
	vector<string> row3;
	row3.push_back("Coconut");
	row3.push_back("1440");
	row3.push_back("130");
	row3.push_back("520");
	table.insert_row(row3);

	table.drawGraph = 1;

	table.table_html_dump();

	return 0;
}

