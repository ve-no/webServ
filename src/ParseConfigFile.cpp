#include "ParseConfigFile.hpp"

ParseConfigFile::ParseConfigFile() : _nb_server(0) {}

ParseConfigFile::~ParseConfigFile() {}

void ParseConfigFile::parseConfigFile(const std::string &config_file) {
	std::string content = ConfigFile::fileToString(config_file);
	splitServers(content);
	if (_server_config.size() != _nb_server)
		throw std::runtime_error("Error: Server config file is not well formated");
	for (size_t i = 0; i < _nb_server; i++) {
		ServConf server;
		createServer(_server_config[i], server);
		_servers.push_back(server);
	}
	checkServers();
}

void ParseConfigFile::splitServers(std::string &content) {
	size_t start = 0;
	size_t end = 0;
	if (content.find("#") != std::string::npos)
		content.erase(content.find("#"));
	content.erase(0, content.find_first_not_of(" \t"));
	content.erase(content.find_last_not_of(" \t") + 1);
	while (end < content.size()) {
		start = findStartServer(end, content);
		end = findEndServer(start, content);
		_server_config.push_back(content.substr(start, end - start));
	}
}

size_t ParseConfigFile::findStartServer(size_t start, std::string &content) {
	size_t pos = start;
	while (pos < content.size()) {
		if (content[pos] == '{')
			return pos + 1;
		pos++;
	}
	throw std::runtime_error("Error: Server config file is not well formated");
}

size_t ParseConfigFile::findEndServer(size_t start, std::string &content) {
	size_t pos = start;
	int count = 1;
	while (pos < content.size()) {
		if (content[pos] == '{')
			count++;
		else if (content[pos] == '}')
			count--;
		if (count == 0)
			return pos;
		pos++;
	}
	throw std::runtime_error("Error: Server config file is not well formated");
}

void ParseConfigFile::createServer(std::string &config, ServConf &server) {
	std::vector<std::string> line = ft_split(config, '\n');
	std::vector<std::string>::iterator it = line.begin();
	std::vector<std::string>::iterator ite = line.end();

	for (; it != ite; ++it) {
		std::string str = *it;
		if (str.at(str.length() - 1) == ';')
			str.pop_back();
		else
			throw std::runtime_error("Error: Server config file is not well formated");
		std::vector<std::string> param = ft_split(str, ' ');
		if (param.size() > 1) {
			std::string key = param[0];
			std::vector<std::string> value;
			for (size_t i = 1; i < param.size(); i++)
				value.push_back(param[i]);
			if (key == "listen") {
				if (value.size() != 1)
					throw std::runtime_error("Error: Server config file is not well formated");
				server.setPort(value[0]);
			}
			else if (key == "server_name") {
				if (value.size() != 1)
					throw std::runtime_error("Error: Server config file is not well formated");
				server.setServerName(value[0]);
			}
			else if (key == "error_page")
		}
	}

}
// void ParseConfigFile::createServer(std::string &config, ServConf &server) {
// 	size_t pos = 0;
// 	size_t start = 0;
// 	size_t end = 0;
// 	std::string key;
// 	std::string value;

// 	while (pos < config.size()) {
// 		if (config[pos] == ';') {
// 			key = config.substr(start, pos - start);
// 			start = pos + 1;
// 			while (config[start] == ' ')
// 				start++;
// 			end = start;
// 			while (config[end] != ' ' && config[end] != ';')
// 				end++;
// 			value = config.substr(start, end - start);
// 			if (key == "listen")
// 				server.setListen(value);
// 			else if (key == "server_name")
// 				server.setServerName(value);
// 			else if (key == "error_page")
// 				server.setErrorPage(value);
// 			else if (key == "client_max_body_size")
// 				server.setMaxBodySize(value);
// 			else if (key == "root")
// 				server.setRoot(value);
// 			else if (key == "index")
// 				server.setIndex(value);
// 			else if (key == "autoindex")
// 				server.setAutoindex(value);
// 			else if (key == "methods")
// 				server.setMethods(value);
// 			else if (key == "return")
// 				server.setReturn(value);
// 			else if (key == "alias")
// 				server.setAlias(value);
// 			else if (key == "cgi_path")
// 				server.setCgiPath(value);
// 			else if (key == "cgi_extension")
// 				server.setCgiExtension(value);
// 			else if (key == "location")
// 				server.setLocation(value);
// 			else
// 				throw std::runtime_error("Error: Server config file is not well formated");
// 			pos++;
// 			start = pos + 1;
// 		}
// 		pos++;
// 	}
// }

// void ParseConfigFile::checkServers() {
// 	for (size_t i = 0; i < _servers.size(); i++) {
// 		if (_servers[i].getListen().empty())
// 			throw std::runtime_error("Error: Server config file is not well formated");
// 		if (_servers[i].getServerName().empty())
// 			throw std::runtime_error("Error: Server config file is not well formated");
// 		if (_servers[i].getRoot().empty())
// 			throw std::runtime_error("Error: Server config file is not well formated");
// 		if (_servers[i].getLocation().empty())
// 			throw std::runtime_error("Error: Server config file is not well formated");
// 		if (_servers[i].getAutoindex().empty())
// 			throw std::runtime_error("Error: Server config file is not well formated");
// 		if (_servers[i].getMethods().empty())
// 			throw std::runtime_error("Error: Server config file is not well formated");
// 		if (_servers[i].getReturn().empty())
// 			throw std::runtime_error("Error: Server config file is not well formated");
// 		if (_servers[i].getAlias().empty())
// 			throw std::runtime_error("Error: Server config file is not well formated");
// 		if (_servers[i].getCgiPath().empty())
// 			throw std::runtime_error("Error: Server config file is not well formated");
// 		if (_servers[i].getCgiExtension().empty())
// 			throw std::runtime_error("Error: Server config file is not well formated");
// 		if (_servers[i].getMaxBodySize().empty())
// 			throw std::runtime_error("Error: Server config file is not well formated");
// 	}
// }

// const std::vector<ServerConfig> &ParseConfigFile::getServers() { return (_servers); }

// int ParseConfigFile::stringCompare(std::string str1, std::string str2, size_t pos) {
// 	size_t i = 0;

// 	while (i < str1.size() && i < str2.size()) {
// 		if (str1[i] != str2[i + pos])
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

int ParseConfigFile::print() {
	std::cout << "nb server: " << _nb_server << std::endl;
	for (size_t i = 0; i < _server_config.size(); i++) {
		std::cout << "server config: " << _server_config[i] << std::endl;
	}
	return (0);
}

