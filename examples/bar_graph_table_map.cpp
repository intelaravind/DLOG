/*
 * bar_graph.cpp
 *
 * Created on: Jan 3, 2014
 *      Author: aravind
 */

/*
 * compile with g++ bar_graph_table_map.cpp -std=c++11
 */

#include "DLOG_TABLE_MAP.hpp"

using namespace std;

int main()
{
	DLOG_TABLE_MAP table("bar_graph_table_map.html", "fruits", "./output/");

	table.insert_elem("Apple", "sold", "100");
	table.insert_elem("Apple", "stockleft", "20");
	table.insert_elem("Apple", "somevalue", "50");

	table.insert_elem("Orange", "sold", "130");
	table.insert_elem("Orange", "stockleft", "7");
	//table.insert_elem("Orange", "somevalue", "60"); //Lets say we dont insert this

	table.insert_elem("Coconut", "sold", "120");
	table.insert_elem("Coconut", "stockleft", "10");
	table.insert_elem("Coconut", "somevalue", "25");

	table.drawGraph = 1;
//	table.table_dump();
	table.table_html_dump();

	return 0;
}
