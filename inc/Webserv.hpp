#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include <iostream>
# include <string>
# include <unistd.h>
# include <vector>
# include <map>
# include <list>
# include <fstream>
# include <sstream>
# include <sys/stat.h>
# include <algorithm>
#include <netinet/in.h>
#include <arpa/inet.h>

# include "Location.hpp"
# include "ServConf.hpp"
# include "ConfigFile.hpp"

#define MAX_CONTENT_LENGTH 99999999

std::vector<std::string> ft_split(const std::string& s, char delimiter) {
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter))
		tokens.push_back(token);
	return tokens;
}

#endif
