/*
 * gantt_example.cpp
 * Copyright (C) 2017 Aravind SUKUMARAN RAJAM (asr) <aravind_sr@outlook.com>
 *
 * Distributed under terms of the GNU LGPL3 license.
 */

/*
 * compile with g++ DLOG_TABLE_SIMPLE.cpp -std=c++11
 */

#include "DLOG_TABLE.hpp"
#include <vector>
#include <string>


int main(int argc, char *argv[])
{
    DLOG_TABLE table("gantt_example.html", "thread visualization", "./output");

    std::vector<long> start {0, 0, 5, 5, 10, 11};
    std::vector<long> end   {2, 5, 6, 9, 12, 14};
    std::vector<long> tid   {0, 1, 0, 1,  0, 1};



    for(unsigned int i = 0; i < start.size(); i++)
    {
        std::vector < std::string > row;
        std::string info = "you can add any info here; for eg i = " + std::to_string(i);
        row.push_back(info);                       //any info you want
        row.push_back(std::to_string(tid[i]));     // the name of event (group name)
        row.push_back(std::to_string(start[i]));   // event start
        row.push_back(std::to_string(end[i]));     //event end
        table.insert_row(row);
    }

    table.table_gantt_dump();

    return 0;
}

