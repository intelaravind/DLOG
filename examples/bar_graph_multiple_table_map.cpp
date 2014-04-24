/*
 * bar_graph.cpp
 *
 *  Created on: Jan 3, 2014
 *      Author: aravind
 */



/*
 * compile with g++ bar_graph_multiple_table_map.cpp -std=c++11
 */

#include "../DLOG_TABLE_MAP.hpp"
#include <vector>

//NOTE: DLOG_BAR_GRAPH requires the data to be in dlog table
using namespace std;

//The only thing to be done is call the function tables.show_graph() for the tables you need to show graph

int main()
{
	DLOG_TABLES_MAP tables("bar_graph_table_map_multiple.html", "./output/");

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
			tables.show_graph(table_fruits);
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
//			tables.show_graph(table_cars); //commented not to display graph for this table
		}

		//table 2
		{
			TID_PAIR table_cars2 = tables.newtable("cars2");

			/*Row 1*/
			tables.insert_elem(table_cars2, "Maruthi", "sold", "250");
			tables.insert_elem(table_cars2, "Maruthi", "stockleft", "13");
			tables.insert_elem(table_cars2, "Maruthi", "somevalue", "58");

			/*Row 2*/
			tables.insert_elem(table_cars2, "BMW", "sold", "1400");
			tables.insert_elem(table_cars2, "BMW", "stockleft", "160");
			tables.insert_elem(table_cars2, "BMW", "somevalue", "630");

			/*Row 3*/
			tables.insert_elem(table_cars2, "Audi", "sold", "2900");
			tables.insert_elem(table_cars2, "Audi", "stockleft", "213");
			tables.insert_elem(table_cars2, "Audi", "somevalue", "234");
			tables.show_graph(table_cars2);
		}

		tables.html_dump();

	return 0;
}

