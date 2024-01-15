#ifndef PARSECONFIGFILE_HPP
#define PARSECONFIGFILE_HPP

#include "Webserv.hpp"

class ServConf;

class ParseConfigFile {
	public:
		ParseConfigFile();
		~ParseConfigFile();

		void					parseConfigFile(const std::string &config_file);
		void					splitServers(std::string &content);
		size_t					startServer(size_t start, std::string &content);
		size_t					endServer(size_t start, std::string &content);
		void					createServer(std::string &config, ServConf &server);
		std::vector<ServConf>	getServers();
		int						print();
	private:
		std::vector<ServConf>		servers;
		std::vector<std::string>	serv_conf;
		size_t						nbr_serv;
};

#endif
