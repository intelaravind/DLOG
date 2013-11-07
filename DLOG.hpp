/*
 * DLOG.hpp
 *
 *  Created on: Jul 11, 2013
 *      Author: aravind
 *
 * This class is a wrapper for mydebug class
 */

#ifndef DLOG_HPP_
#define DLOG_HPP_

#include "mydebug.hpp"

//#define DLOG_DEBUG

#ifdef DLOG_ENABLE
#define MDEBG_CREATE(path)  DLOG(__FILE__,__LINE__,path)
#define PRINT_TO_FILE(...)  print_to_file(__FILE__,__LINE__ ,__VA_ARGS__)
#else
#define MDEBG_CREATE(path)  DLOG()
#define PRINT_TO_FILE(...)  print_to_file()
#endif

/**
 * If MDEBG class in instantiated with same path from two
 * different code points or files, we should append the data.
 * path_to_debug_map maps the path to the aravdebug instance
 */

static std::map<std::string, aravdebug*> path_to_debug_map;

/***
 * Wrapper for aravdebug
 */
class DLOG
{
	aravdebug *dbg;
	int should_free = 0;

public:

	/**
	 * Empty constructor to do nothing;
	 * Used mainly to disable DLOG
	 */
	DLOG()
	{

	}
	DLOG(const char * userfile, int lineno, const char *PATH)
	{
		if (path_to_debug_map.find(PATH) != path_to_debug_map.end())
		{
			dbg = path_to_debug_map.find(PATH)->second;
			should_free++;
			/*
			 if (filemode == FILE_NEW)
			 {
			 std::cout
			 << "WARNING (MDEBG): OBJECT WITH SAME PATH WAS CREATED EARLIER.\n"
			 << "\tIGNORING THE REQUEST TO CREATE A NEW FILE ::" << userfile<<":"<<lineno;
			 }
			 */
		}
		else
		{
			dbg = new aravdebug(userfile, lineno, PATH);

			path_to_debug_map[PATH] = dbg;
		}
	}

	/**
	 * Do nothing. Used mainly for disabling DLOG
	 */
	void print_to_file()
	{

	}

	template<typename T>
	void print_to_file(const char * userfile, int lineno, T obj)
	{
#ifdef DLOG_DEBUG
		llvm::errs() << "I am called in line no" << __LINE__ << "\n";
#endif
		dbg->print_to_file(userfile, lineno, obj);
	}

	template<typename T>
	void print_to_file(const char * userfile, int lineno, const char* tag,
			T* obj)
	{
#ifdef DLOG_DEBUG
		llvm::errs() << "I am called in line no" << __LINE__ << "\n";
#endif
		dbg->print_to_file(userfile, lineno, tag, obj);
	}

//	template<typename T>
//	void print_to_file(const char * userfile, int lineno, const char* tag,
//			T obj)
//	{
//		dbg->print_to_file(userfile, lineno, tag, &obj);
//	}

	template<typename T>
	void print_to_file(const char * userfile, int lineno, const char* tag,
			T &obj)
	{
#ifdef DLOG_DEBUG
		llvm::errs() << "I am called in line no" << __LINE__ << "\n";
#endif
		dbg->print_to_file(userfile, lineno, tag, obj);
	}

	template<typename T>
	void print_to_file(const char * userfile, int lineno, const char* tag,
			T* obj, ADDON addon)
	{
#ifdef DLOG_DEBUG
		llvm::errs() << "I am called in line no" << __LINE__ << "\n";
#endif
		dbg->print_to_file(userfile, lineno, tag, obj, addon);
	}

	template<typename T>
	void print_to_file(const char * userfile, int lineno, const char* tag,
			T obj, ADDON addon)
	{
#ifdef DLOG_DEBUG
		llvm::errs() << "I am called in line no" << __LINE__ << "\n";
#endif
		dbg->print_to_file(userfile, lineno, &tag, obj, addon);
	}

	template<typename T>
	void print_to_file(const char * userfile, int lineno, const char* tag,
			T &obj, ADDON addon)
	{
#ifdef DLOG_DEBUG
		llvm::errs() << "I am called in line no" << __LINE__ << "\n";
#endif
		dbg->print_to_file(userfile, lineno, &tag, obj, addon);
	}

	void print_to_file(const char * userfile, int lineno, const char* tag,
			unsigned int obj)
	{
#ifdef DLOG_DEBUG
		llvm::errs() << "I am called in line no" << __LINE__ << "\n";
#endif
		dbg->print_to_file(userfile, lineno, tag, &obj);
	}

	void print_to_file(const char * userfile, int lineno, const char* tag,
			int obj)
	{
#ifdef DLOG_DEBUG
		llvm::errs() << "I am called in line no" << __LINE__ << "\n";
#endif
		dbg->print_to_file(userfile, lineno, tag, &obj);
	}

	~DLOG()
	{
		//llvm::errs() << "Calling ~MDEBG\n";

		if (should_free == 0)
		{
			delete dbg;
		}
		else
		{
			should_free--;
		}
	}

};

//MDEBG d1 = MDEBG_CREATE("temp");

#endif /* MDEBG_HPP_ */
