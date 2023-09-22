#ifndef CONFIGFILE_HPP
#define CONFIGFILE_HPP

#include "Webserv.hpp"

class ConfigFile {
	public:
		ConfigFile();
		~ConfigFile();

		static int getTypePath(std::string const path);
		static int accessFile(std::string const path, int mode);
		std::string	fileToString(std::string path);
		static int isReadableAndExist(std::string const path, std::string const index);
};

#endif
