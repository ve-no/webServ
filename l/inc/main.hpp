#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <cstring>

#define RED_BOLD "\033[1;31m"
#define GREEN_BOLD "\033[1;32m"
#define YELLOW_BOLD "\033[1;33m"
#define BLUE_BOLD "\033[1;34m"
#define MAGENTA_BOLD "\033[1;35m"
#define ORANGE_BOLD "\033[1;36m"
#define WHITE_BOLD "\033[1;37m"
#define CYAN_BOLD "\033[1;38m"
#define RESET "\033[0m"

#include "Webserv.hpp"
#include "Request.hpp"
#include "config.hpp"
#include "Response.hpp"
#include "ParseConfigFile.hpp"
#include "ServConf.hpp"
#include "Location.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>
