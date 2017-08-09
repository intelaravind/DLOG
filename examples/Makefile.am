AUTOMAKE_OPTIONS = foreign

AM_CPPFLAGS=-std=c++11 -O3 -I$(top_srcdir)/include #-g

LDADD = ../.libs/libDLOG.a

bin_PROGRAMS = bar_graph bar_graph_multiple bar_graph_multiple_table bar_graph_table_map dlog_simple dlog_simple_crash dlog_table_map_simple dlog_table_map_simple_multiple pie_graph pie_timer_graph_advanced pie_timer_graph_simple simple_timer dlog_table_simple dlog_table_simple2_multiple gantt_example

bar_graph_SOURCES = bar_graph.cpp

bar_graph_multiple_SOURCES = bar_graph_multiple.cpp

bar_graph_multiple_table_SOURCES = bar_graph_multiple_table_map.cpp

bar_graph_table_map_SOURCES = bar_graph_table_map.cpp

dlog_simple_SOURCES = DLOG_SIMPLE.cpp

dlog_simple_crash_SOURCES = DLOG_SIMPLE2_CRASH_TEST.cpp

dlog_table_map_simple_SOURCES = DLOG_TABLE_MAP_SIMPLE.cpp

dlog_table_simple_SOURCES =  DLOG_TABLE_SIMPLE.cpp

dlog_table_map_simple_multiple_SOURCES = DLOG_TABLE_MAP_SIMPLE_Multiple.cpp

dlog_table_simple2_multiple_SOURCES = DLOG_TABLE_SIMPLE2_Multiple.cpp

pie_graph_SOURCES = pie_graph.cpp

pie_timer_graph_advanced_SOURCES = pie_timer_graph_advanced.cpp

pie_timer_graph_simple_SOURCES = pie_timer_graph_simple.cpp

simple_timer_SOURCES = simple_timer.cpp

gantt_example_SOURCES = gantt_example.cpp
