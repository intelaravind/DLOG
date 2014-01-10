/*
 * DLOG_ADDON.hpp
 *
 *  Created on: Dec 15, 2013
 *      Author: aravind
 */

#ifndef DLOG_ADDON_HPP_
#define DLOG_ADDON_HPP_

#include <string>

class ADDON {
	std::string s;

public:
	ADDON() {
		s = "";
	}

	ADDON(const std::string in) {
		s = in;
	}

	void operator=(const std::string in) {
		s = in;
	}

//	void operator=(const ADDON &obj) {
//		s = obj.s;
//	}

	ADDON(const ADDON &obj) {
		s = obj.s;
	}

	std::string getString() {
		return s;
	}
};

#endif /* DLOG_ADDON_HPP_ */
