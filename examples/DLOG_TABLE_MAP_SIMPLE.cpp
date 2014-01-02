/*
 * DLOG_TABLE_MAP_SIMPLE.cpp
 *
 *  Created on: Jan 3, 2014
 *      Author: aravind
 */

/*
 * compile with g++ DLOG_TABLE_MAP_SIMPLE.cpp -std=c++11
 */


#include "../DLOG_TABLE_MAP.hpp"

using namespace std;

int main()
{
	DLOG_TABLE_MAP table("DLOG_TABLE_MAP_SIMPLE.html", "fruits", "./output/");

	/*
	 * First elem: row identifier
	 * Second elem: col identifier
	 * Thrid elem: Value
	 */
	table.insert_elem("Apple", "sold", "100");
	table.insert_elem("Apple", "stockleft", "20");
	table.insert_elem("Apple", "somevalue", "50");

	table.insert_elem("Orange", "sold", "130");
	table.insert_elem("Orange", "stockleft", "7");
	//table.insert_elem("Orange", "somevalue", "60"); //Lets say we dont insert this

	table.insert_elem("Coconut", "sold", "120");
	table.insert_elem("Coconut", "stockleft", "10");
	table.insert_elem("Coconut", "somevalue", "0");

//	table.table_dump(); // to dump on screen
	table.table_html_dump();

	return 0;
}
