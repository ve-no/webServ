#ifndef PARSECONFIGFILE_HPP
#define PARSECONFIGFILE_HPP

#include "Webserv.hpp"

class ServConf;

class ParseConfigFile {
	private:
		std::vector<ServConf>	_servers;
		std::vector<std::string>	_server_config;
		size_t						_nb_server;

	public:

		ParseConfigFile();
		~ParseConfigFile();

		void parseConfigFile(const std::string &config_file);

		void splitServers(std::string &content);

		size_t findStartServer(size_t start, std::string &content);
		size_t findEndServer(size_t start, std::string &content);
		void createServer(std::string &config, ServConf &server);
		void checkServers();
		std::vector<ServConf>	getServers();
		int	stringCompare(std::string str1, std::string str2, size_t pos);

		int print();
};

#endif
