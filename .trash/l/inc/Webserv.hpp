#pragma once

# include <iostream>
# include <fcntl.h>
# include <cstring>
# include <string>
# include <unistd.h>
# include <dirent.h>
# include <sstream>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <cctype>
# include <climits>
# include <ctime>
# include <cstdarg>

/* STL Containers */
# include <map>
# include <set>
# include <vector>
# include <algorithm>
# include <iterator>
# include <list>

/* System */
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <unistd.h>
# include <signal.h>

# include <sys/socket.h>
# include <netinet/in.h>
# include <sys/select.h>
# include <arpa/inet.h>


#include "main.hpp"

#define MAX_URI_LENGTH 4096
#define MAX_CONTENT_LENGTH 99999999


// autoindex
std::string autoindex_style();
std::string create_autoindex_string(std::string dir, std::string dir_str, const std::vector<std::string> &files);
std::string autoindex_body(char *path, std::string req_path);
template <typename T>
std::string to_string(const T& value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

class Webserv
{
private:
    std::string config_path;
    std::string* config;
    int config_size;

public:
    // Construction and Destruction
    Webserv();
    Webserv(std::string conf);
    Webserv(const Webserv &other);
    Webserv &operator=(const Webserv &other);
    ~Webserv();

    // Config parsing
    int parse_config(const std::string& conf);
	std::string* get_config() const;
	int get_config_size() const;
};

std::vector<std::string> ft_split(const std::string& s);
std::vector<std::string> splitParametrs(std::string line, std::string sep);

