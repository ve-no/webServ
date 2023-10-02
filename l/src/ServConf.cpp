#include "../inc/main.hpp"

ServConf::ServConf() {
	setRoot("/");
	setListen("80");
	setHost("localhost");
	setIndex("index.html");
}

ServConf::~ServConf() {}

ServConf::ServConf(const ServConf &other) {
	*this = other;
}

ServConf &ServConf::operator=(const ServConf &other) {
	if (this != &other) {
		port = other.port;
		host = other.host;
		name_server = other.name_server;
		root = other.root;
		client_max_body_size = other.client_max_body_size;
		index = other.index;
		autoindex = other.autoindex;
		_error_pages = other._error_pages;
		locations = other.locations;
		server_address = other.server_address;
		listen_fd = other.listen_fd;
	}
	return (*this);
}

void ServConf::setServerName(std::string server_name) {
	name_server = server_name;
}

void ServConf::setHost(std::string parametr) {
	struct sockaddr_in addr;

	if (parametr == "localhost")
		parametr = "127.0.0.1";
	if (inet_pton(AF_INET, parametr.c_str(), &addr.sin_addr) == 0)
		throw std::runtime_error("Error: invalid host");
	host = inet_addr(parametr.c_str());
}

void ServConf::setRoot(std::string root) {
	this->root = root;
}

void ServConf::setFd(int fd) {
	listen_fd = fd;
}

void ServConf::setListen(std::string parametr) {
	port = atoi(parametr.c_str());
}

void ServConf::setClientMaxBodySize(std::string parametr) {
	client_max_body_size = atoi(parametr.c_str());
}

void ServConf::setErrorPages(std::vector<std::string> &parametr) {
	if (parametr.size() % 2 != 0)
		throw std::runtime_error("Error: invalid error_page 1");
	for (size_t i = 0; i < parametr.size(); i++) {
		for (size_t j = 0; j < parametr[i].size(); j++) {
			if (!std::isdigit(parametr[i][j]))
				throw std::runtime_error("Error: invalid error_page 2");
		}
		if (atoi(parametr[i].c_str()) < 100 || atoi(parametr[i].c_str()) > 599)
			throw std::runtime_error("Error: invalid error_page 3");
		error_pages key = static_cast<error_pages>(atoi(parametr[i].c_str()));
		++i;
		std::string value = parametr[i];
		if (ServConf::getTypePath(value) != 2)
			throw std::runtime_error("Error: invalid error_page 4");
		if (ServConf::accessFile(value, F_OK) < 0
			|| ServConf::accessFile(value, R_OK) < 0)
			throw std::runtime_error("Error: invalid error_page");
		_error_pages[key] = value;

	}
}

void ServConf::setIndex(std::string index) {
	this->index = index;
}

void ServConf::setLocation(std::string nameLocation, std::vector<std::string> parametr) {
	Location location;
	for(size_t i = 0; i < parametr.size(); i++) {
		std::string str = parametr[i];
		ServConf::checkToken(str);
		std::vector<std::string> param = ft_split(str);
		if (param.size() > 1) {
			std::string key = param[0];
			std::vector<std::string> value;
			for (size_t i = 1; i < param.size(); i++)
				value.push_back(param[i]);
			if (key == "root")
				location.setRootLocation(value[0]);
			else if (key == "allow_methods")
				location.setMethods(value);
			else if (key == "autoindex")
				location.setAutoindex(value[0]);
			else if (key == "index")
				location.setIndexLocation(value[0]);
			else if (key == "return")
				location.setReturn(value[0]);
			else if (key == "alias") {
				location.setAlias(value[0]);
			}
			else if (key == "cgi_path")
				location.setCgiPath(value);
			else if (key == "cgi_extension")
				location.setCgiExtension(value);
			else if (key == "max_body_size")
				location.setMaxBodySize(value[0]);

			// if (key == "root")
			// 	location.setRootLocation(value);
			// else if (key == "methods")
			// 	location.setMethods(value);
			// else if (key == "autoindex")
			// 	location.setAutoindex(value);
			// else if (key == "index")
			// 	location.setIndexLocation(value);
			// else if (key == "return")
			// 	location.setReturn(value);
			// else if (key == "alias") {
			// 	std::cout << "alias: " << value << std::endl;
			// 	location.setAlias(value);
			// }
			// else if (key == "cgi_path")
			// 	location.setCgiPath(value);
			// else if (key == "cgi_extension")
			// 	location.setCgiExtension(value);
			// else if (key == "max_body_size")
			// 	location.setMaxBodySize(value);
		}
	}
	location.setPath(nameLocation);
	locations.push_back(location);
}

void ServConf::setAutoindex(std::string autoindex) {
	if (autoindex == "on")
		this->autoindex = true;
	else if (autoindex == "off")
		this->autoindex = false;
	else
		throw std::runtime_error("Error: invalid autoindex");
}

bool ServConf::isValidErrorPages() {
	std::map<error_pages, std::string>::iterator it = _error_pages.begin();
	std::map<error_pages, std::string>::iterator ite = _error_pages.end();
	for (; it != ite; ++it) {
		if (ServConf::accessFile(it->second, F_OK) < 0
			|| ServConf::accessFile(it->second, R_OK) < 0)
			return false;
	}
	return true;
}

int ServConf::isValidLocation(Location &location) const {
	if (location.getPath().empty())
		return 0;
	if (location.getRootLocation().empty())
		return 0;
	if (location.getMethods().empty())
		return 0;
	if (location.getIndexLocation().empty())
		return 0;
	if (location.getAlias().empty())
		return 0;
	if (location.getCgiPath().empty())
		return 0;
	if (location.getCgiExtension().empty())
		return 0;
	if (location.getMaxBodySize() == 0)
		return 0;
	return 1;
}

// getters
const std::string &ServConf::getServerName() {
	return name_server;
}

const uint16_t &ServConf::getPort() {
	return port;
}

const in_addr_t &ServConf::getHost() {
	return host;
}

const size_t &ServConf::getClientMaxBodySize() {
	return client_max_body_size;
}

const std::vector<Location> &ServConf::getLocations() {
	return locations;
}

const std::string &ServConf::getRoot() {
	return root;
}

const std::map<error_pages, std::string> &ServConf::getErrorPages() {
	return _error_pages;
}

const std::string &ServConf::getIndex() {
	return index;
}

const bool &ServConf::getAutoindex() {
	return autoindex;
}

const std::string &ServConf::getPathErrorPage(error_pages key) {
	return _error_pages[key];
}

const std::vector<Location>::iterator ServConf::getLocationKey(std::string key) {
	std::vector<Location>::iterator it = locations.begin();
	std::vector<Location>::iterator ite = locations.end();
	for (; it != ite; ++it) {
		if (it->getPath() == key)
			return it;
	}
	return it;
}

void ServConf::checkToken(std::string &parametr) {
	std::string::size_type pos = parametr.find('#');
	if (pos != std::string::npos)
		parametr.erase(pos, parametr.find('\n', pos) - pos);
	pos = parametr.find(";");
	if (pos != std::string::npos)
		parametr.erase(pos);
}

bool ServConf::checkLocaitons() const {
	std::vector<Location>::const_iterator it = locations.begin();
	std::vector<Location>::const_iterator ite = locations.end();
	for (; it != ite; ++it) {
		if (isValidLocation(const_cast<Location &>(*it)) == 0)
			return false;
	}
	return true;
}

// void ServConf::setupServer() {
// 	server_address.sin_family = AF_INET;
// 	server_address.sin_addr.s_addr = host;
// 	server_address.sin_port = htons(port);
// }

int ServConf::getFd() {
	return listen_fd;
}

// define is path is directory or file
int ServConf::getTypePath(std::string const path) {
	struct stat buf;

	if (stat(path.c_str(), &buf) == -1)
		return -1;
	if (S_ISDIR(buf.st_mode))
		return 1;
	if (S_ISREG(buf.st_mode))
		return 2;
	return 0;
}

// Check file exist and readable
int ServConf::accessFile(std::string const path, int mode) {
	if (access(path.c_str(), mode) == -1)
		return -1;
	return 0;
}

// Read file to string
std::string ServConf::fileToString(std::string path) {
	std::string		file;
	std::string		line;
	std::ifstream	in(path.c_str());

	if (!in.is_open())
		throw std::runtime_error("Error: file " + path + " not found");
	while (getline(in, line))
		file += line + "\n";
	in.close();
	return file;
}

int ServConf::isReadableAndExist(std::string const path, std::string const index) {
	int		type;

	type = getTypePath(path);
	if (type == -1)
		return -1;
	if (type == 1)
		if ((accessFile(path, R_OK | X_OK)) == -1)
			return -1;
	if (type == 2)
		if ((accessFile(path, R_OK)) == -1)
			return -1;
	if (type == 0)
		if ((accessFile(path + index, R_OK)) == -1)
			return -1;
	return 0;
}

