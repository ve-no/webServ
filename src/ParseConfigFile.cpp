#include "ParseConfigFile.hpp"

ParseConfigFile::ParseConfigFile() : _nb_server(0) {}

ParseConfigFile::~ParseConfigFile() {}

void ParseConfigFile::parseConfigFile(const std::string &config_file) {
	std::string content = ConfigFile::fileToString(config_file);
	splitServers(content);
	if (_server_config.size() != _nb_server)
		throw std::runtime_error("Error: Server config file is not well formated 1");
	for (size_t i = 0; i < _nb_server; i++) {
		ServConf server;
		createServer(_server_config[i], server);
		_servers.push_back(server);
	}
	checkServers();
}

void ParseConfigFile::splitServers(std::string &content) {
	size_t start = 0;
	size_t end = 1;
	while (start < content.length() && start != end) {
		start = findStartServer(start, content);
		end = findEndServer(start, content);
		_server_config.push_back(content.substr(start, end - start + 1));
		_nb_server++;
		std::cout << "hello world: " << start << "    "<< content.length() << " end " << end << std::endl;
		start = end;
	}
}

size_t ParseConfigFile::findStartServer(size_t start, std::string &content) {
	size_t pos = start;
	for (; pos < content.size() && isspace(content[pos]); pos++)
		if (content[pos] == 's')
			break;
	if (!content[pos])
		return start;
	// while (pos < content.size() && pos < pos + 7)
	// if (!content[pos])
	// std::cout << content.compare(pos, 6, "server") << std::endl;
	// std::cout << content[pos+2] << std::endl;
	if (content.compare(pos, 6, "server") != 0)
		throw std::runtime_error("Error: Wrong character 1");
	pos += 6;
	while (pos < content.size() && isspace(content[pos]))
			pos++;
	if (content[pos] != '{')
		throw std::runtime_error("Error: Wrong character");
	return (pos + 1);
}

size_t ParseConfigFile::findEndServer(size_t start, std::string &content) {
	size_t pos = start;
	int count = 0;

	for (pos = start; pos < content.size(); pos++) {
		if (content[pos] == '{')
			count++;
		else if (content[pos] == '}') {
			if (count == 0)
				return (pos + 1);
			count--;
		}
	}
	return (pos);
}

void ParseConfigFile::createServer(std::string &config, ServConf &server) {
	std::vector<std::string> line = splitParametrs(config, "\n");
	std::vector<std::string> error_page;


	for (size_t i = 0; i < line.size(); i++) {
		std::string str = line[i];
		ServConf::checkToken(str);
		std::vector<std::string> param = ft_split(str);
		if (param.size() > 1) {
			std::string key = param[0];
			std::vector<std::string> value;
			for (size_t i = 1; i < param.size(); i++)
				value.push_back(param[i]);
			if (key == "listen") {
				if (value.size() != 1)
					throw std::runtime_error("Error: Server config file is not well formated 4");
				server.setPort(value[0]);
			}
			else if (key == "server_name") {
				if (value.size() != 1)
					throw std::runtime_error("Error: Server config file is not well formated 5");
				server.setServerName(value[0]);
			}
			else if (key == "error_page") {
				server.setErrorPages(value);
			}
			else if (key == "location") {
				if (value.size() < 2)
					throw std::runtime_error("Error: Server config file is not well formated 6");
				std::string name = value[0];
				if (value[1] != "{")
					throw std::runtime_error("Error: Server config file is not well formated 7");
				std::vector<std::string> location;
				while (i < line.size() && line[i] != "}") {
					ServConf::checkToken(line[i]);
					location.push_back(line[i++]);
				}
				if (line[i] != "}")
					throw std::runtime_error("Error: Server config file is not well formated 8");
				server.setLocation(name, location);
			}
			else if (key == "host") {
				server.setHost(value[0]);
			}
			else if (key == "client_max_body_size") {
				server.setClientMaxBodySize(value[0]);
			}
			else if (key == "root") {
				server.setRoot(value[0]);
			}
			else if (key == "index") {
				server.setIndex(value[0]);
			}
			else if (key == "autoindex") {
				server.setAutoindex(value[0]);
			}
		}
		else {
			if (param.empty() || param[0] == "}")
				continue;
			else
			throw std::runtime_error("Error: Server config file is not well formated 9");
		}
	}
	if (ConfigFile::isReadableAndExist(server.getRoot(), server.getIndex()) < 0)
		throw std::runtime_error("Error: Index from config file not found 1");
	if (ConfigFile::isReadableAndExist(server.getRoot(), "") < 0)
		throw std::runtime_error("Error: Root from config file not found 2");
	// if (!server.checkLocaitons())
	// 	throw std::runtime_error("Error: in Location from config file");
	if (!server.isValidErrorPages())
		throw std::runtime_error("Error: in ErrorPages from config file");
}

void ParseConfigFile::checkServers() {
	for (size_t i = 0; i < _servers.size(); i++) {
		for (size_t j = i + 1; j < _servers.size(); j++) {
			if (_servers[i].getPort() == _servers[j].getPort()
				&& _servers[i].getHost() == _servers[j].getHost())
				throw std::runtime_error("Error: Server config file is not well formated 11");
		}
	}
}

std::vector<ServConf> ParseConfigFile::getServers() {
	return _servers;
}

int ParseConfigFile::print() {
	std::cout << "nb server: " << _nb_server << std::endl;
	for (size_t i = 0; i < _server_config.size(); i++) {
		std::cout << "getRoot: " << _servers[i].getRoot() << std::endl;
		std::cout << "getPort: " << _servers[i].getPort() << std::endl;
		std::cout << "getHost: " << _servers[i].getHost() << std::endl;
		std::cout << "getServerName: " << _servers[i].getServerName() << std::endl;
		std::cout << "getClientMaxBodySize: " << _servers[i].getClientMaxBodySize() << std::endl;
		std::cout << "getIndex: " << _servers[i].getIndex() << std::endl;
		std::cout << "getAutoindex: " << _servers[i].getAutoindex() << std::endl;
		std::map<error_pages, std::string> errors = _servers[i].getErrorPages();
		std::map<error_pages, std::string>::iterator it = errors.begin();
		std::map<error_pages, std::string>::iterator ite = errors.end();
		for (; it != ite; ++it) {
			std::cout  << "error code: "<< it->first << "\nerror page: " << it->second << std::endl;
		}
		std::vector<Location> locations = _servers[i].getLocations();
		std::vector<Location>::iterator itl = locations.begin();
		std::vector<Location>::iterator itle = locations.end();
		for (; itl != itle; itl++) {
			std::cout << "location: " << itl->getPath() << std::endl;
			std::cout << "location root: " << itl->getRootLocation()<< std::endl;
			std::cout << "location autoindex: " << itl->getAutoindex()<< std::endl;
			std::cout << "location index: " << itl->getIndexLocation()<< std::endl;
			std::cout << "location return: " << itl->getReturn()<< std::endl;
			std::cout << "location alias: " << itl->getAlias()<< std::endl;
			std::vector<std::string> getCgi = itl->getCgiPath();
			std::vector<std::string>::iterator itc = getCgi.begin();
			std::vector<std::string>::iterator itce = getCgi.end();
			for (; itc != itce; itc++) {
				std::cout << "location cgi path: " << *itc<< std::endl;
			}
			std::vector<std::string> getCgiExt = itl->getCgiExtension();
			std::vector<std::string>::iterator itce2 = getCgiExt.begin();
			std::vector<std::string>::iterator itce2e = getCgiExt.end();
			for (; itce2 != itce2e; itce2++) {
				std::cout << "location cgi extension: " << *itce2<< std::endl;
			}
			// std::cout << "location cgi path: " << itl->getCgiPath()[0]<< std::endl;
			// std::cout << "location cgi extension: " << itl->getCgiExtension()[0]<< std::endl;
			std::cout << "location max body size: " << itl->getMaxBodySize()<< std::endl;
			std::vector<bool> getMethods = itl->getMethods();
			std::vector<bool>::iterator itm = getMethods.begin();
			std::vector<bool>::iterator itme = getMethods.end();
			for (; itm != itme; itm++) {
				std::cout << "location methods: " << *itm<< std::endl;
			}
			std::cout << "location methods: " << itl->getPrintMethods()<< std::endl;
		}
	}
	return 0;
}

