#include "DLOG_HELPER.hpp"

bool replace(std::string& str, const std::string& from, const std::string& to)
{
	size_t start_pos = str.find(from);
	if (start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}

void replaceAll(std::string& str, const std::string& from,
		const std::string& to)
{
	if (from.empty())
		return;
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos)
	{
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
	}
}

std::string dlog_format_string_to_html(std::string obj)
{
	replaceAll(obj, "\n", mendl);
	return obj;
}


std::string dlog_format_string_to_html(int obj)
{
	return std::to_string(obj);
}

std::string dlog_format_string_to_html(double obj)
{
	return std::to_string(obj);
}
