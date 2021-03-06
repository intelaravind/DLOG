/**
 * DLOG_HELPER.hpp
 *
 *  Created on: Dec 15, 2013
 *      Author: aravind
 */

#ifndef DLOG_HELPER_HPP_
#define DLOG_HELPER_HPP_
#include <iostream>
#include <string>

#include "DLOG_ADDON.hpp"
#define mendl  "<br>\n"
#define br  "<br>"

#define RED(s) "<FONT COLOR='red'>" << s <<  "</font>"
#define GREEN(s) "<FONT COLOR='green'>" << s << "</font>"
#define BLUE(s) "<FONT COLOR='blue'>" << s << "</font>"
#define BROWN(s) "<FONT COLOR='#595930'>" << s << "</font>"

#define CHKBOX(s) "<input type='checkbox' name='foo' value=\""<<s<<"\" onClick='toggle_hideme(\""<<s<<"\");' checked>"<< s <<mendl

#define BOLD(s) "<b>" << s << "</b>"
#define DIV(s) "<div class='"<<s<<"' id='"<< s <<"' >"
#define SPAN(s) "<span class='"<<s<<"' id='"<< s <<"' >"
#define EDIV "</div>\n"
#define ESPAN "</span>\n"
#define NBSP "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"
#define CALLINFO "<span class='CALLINFO' id='CALLINFO' style=\"font-size:12px\">"<<NBSP<<RED(userfile)<<":"<<RED(lineno)<<"</span>\n"

bool replace(std::string&, const std::string&, const std::string&);
void replaceAll(std::string&, const std::string&, const std::string&);

std::string dlog_format_string_to_html(std::string );
std::string dlog_format_string_to_html(int);
std::string dlog_format_string_to_html(double );

#endif /* DLOG_HELPER_HPP_ */
