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
# include "ParseConfigFile.hpp"

#define MAX_CONTENT_LENGTH 99999999

std::vector<std::string> ft_split(const std::string& s);
std::vector<std::string> splitParametrs(std::string line, std::string sep);

#endif
