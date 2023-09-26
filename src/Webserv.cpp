
# include "Webserv.hpp"

std::vector<std::string> ft_split(const std::string& s) {
	std::vector<std::string> tokens;
	std::string token;
	std::stringstream ss(s);
	while (ss >> token)
		tokens.push_back(token);
	return tokens;
}

std::vector<std::string> splitParametrs(std::string line, std::string sep)
{
	std::vector<std::string>	str;
	size_t		start, end;

	start = end = 0;
	while (1)
	{
		end = line.find_first_of(sep, start);
		if (end == std::string::npos)
			break;
		std::string tmp = line.substr(start, end - start);
		str.push_back(tmp);
		start = line.find_first_not_of(sep, end);
		if (start == std::string::npos)
			break;
	}
	return (str);
}
