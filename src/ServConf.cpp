#include "ServConf.hpp"

ServConf::ServConf() {}

ServConf::~ServConf() {}

ServConf::ServConf(const ServConf &other) {
	*this = other;
}

ServConf &ServConf::operator=(const ServConf &other) {
	if (this != &other) {
		_port = other._port;
		_host = other._host;
		_server_name = other._server_name;
		_root = other._root;
		_client_max_body_size = other._client_max_body_size;
		_index = other._index;
		_autoindex = other._autoindex;
		_error_pages = other._error_pages;
		_locations = other._locations;
		_server_address = other._server_address;
		_listen_fd = other._listen_fd;
	}
	return (*this);
}

void ServConf::initErrorPages(void) {
	_error_pages[BAD_REQUEST] = "";
	_error_pages[UNAUTHORIZED] = "";
	_error_pages[FORBIDDEN] = "";
	_error_pages[NOT_FOUND] = "";
	_error_pages[METHOD_NOT_ALLOWED] = "";
	_error_pages[REQUEST_ENTITY_TOO_LARGE] = "";
	_error_pages[INTERNAL_SERVER_ERROR] = "";
	_error_pages[NOT_IMPLEMENTED] = "";
	_error_pages[BAD_GATEWAY] = "";
	_error_pages[SERVICE_UNAVAILABLE] = "";
	_error_pages[GATEWAY_TIMEOUT] = "";
	_error_pages[HTTP_VERSION_NOT_SUPPORTED] = "";
}

void ServConf::setServerName(std::string server_name) {
	_server_name = server_name;
}

void ServConf::setHost(std::string parametr = "localhost") {
	_host = inet_addr(parametr.c_str());
}

void ServConf::setRoot(std::string root = "/") {
	_root = root;
}

void ServConf::setFd(int fd) {
	_listen_fd = fd;
}

void ServConf::setPort(std::string parametr) {
	_port = atoi(parametr.c_str());
}

void ServConf::setClientMaxBodySize(std::string parametr) {
	_client_max_body_size = atoi(parametr.c_str());
}

void ServConf::setErrorPages(std::vector<std::string> &parametr) {
	if (parametr.size() % 2 != 0)
		throw std::runtime_error("Error: invalid error_page");
	for (size_t i = 0; i < parametr.size(); i++) {
		for (size_t j = 0; j < parametr[i].size(); j++) {
			if (!std::isdigit(parametr[i][j]))
				throw std::runtime_error("Error: invalid error_page");
		}
		if (atoi(parametr[i].c_str()) < 100 || atoi(parametr[i].c_str()) > 599)
			throw std::runtime_error("Error: invalid error_page");
		error_pages key = static_cast<error_pages>(atoi(parametr[i].c_str()));
		++i;
		std::string value = parametr[i];
		if (ConfigFile::getTypePath(getRoot() + value) != 2)
			throw std::runtime_error("Error: invalid error_page");
		if (ConfigFile::accessFile(getRoot() + value, F_OK) < 0
			|| ConfigFile::accessFile(getRoot() + value, R_OK) < 0)
			throw std::runtime_error("Error: invalid error_page");
		_error_pages[key] = value;

	}
}

void ServConf::setIndex(std::string index = "index.html") {
	_index = index;
}

void ServConf::setLocation(std::string nameLocation, std::vector<std::string> parametr) {
	Location location;
	std::vector<std::string>::iterator it = parametr.begin();
	std::vector<std::string>::iterator ite = parametr.end();
	for (; it != ite; ++it) {
		std::string::size_type pos = it->find(" ");
		if (pos != std::string::npos) {
			std::string key = it->substr(0, pos);
			std::string value = it->substr(pos + 1);
			if (key == "root")
				location.setRootLocation(value);
			else if (key == "methods")
				location.setMethods(value);
			else if (key == "autoindex")
				location.setAutoindex(value);
			else if (key == "index")
				location.setIndexLocation(value);
			else if (key == "return")
				location.setReturn(value);
			else if (key == "alias")
				location.setAlias(value);
			else if (key == "cgi_path")
				location.setCgiPath(value);
			else if (key == "cgi_extension")
				location.setCgiExtension(value);
			else if (key == "max_body_size")
				location.setMaxBodySize(value);
		}
	}
	location.setPath(nameLocation);
	_locations.push_back(location);
}

void ServConf::setAutoindex(std::string autoindex) {
	if (autoindex == "on")
		_autoindex = true;
	else if (autoindex == "off")
		_autoindex = false;
	else
		throw std::runtime_error("Error: invalid autoindex");
}

bool ServConf::isValidHost(std::string host) const {
	struct sockaddr_in addr;
	if (inet_pton(AF_INET, host.c_str(), &addr.sin_addr) == 1)
		return true;
	return false;
}

bool ServConf::isValidErrorPages() {
	std::map<error_pages, std::string>::iterator it = _error_pages.begin();
	std::map<error_pages, std::string>::iterator ite = _error_pages.end();
	for (; it != ite; ++it) {
		if (ConfigFile::accessFile(getRoot() + it->second, F_OK) < 0
			|| ConfigFile::accessFile(getRoot() + it->second, R_OK) < 0)
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
	return _server_name;
}

const uint16_t &ServConf::getPort() {
	return _port;
}

const in_addr_t &ServConf::getHost() {
	return _host;
}

const size_t &ServConf::getClientMaxBodySize() {
	return _client_max_body_size;
}

const std::vector<Location> &ServConf::getLocations() {
	return _locations;
}

const std::string &ServConf::getRoot() {
	return _root;
}

const std::map<error_pages, std::string> &ServConf::getErrorPages() {
	return _error_pages;
}

const std::string &ServConf::getIndex() {
	return _index;
}

const bool &ServConf::getAutoindex() {
	return _autoindex;
}

const std::string &ServConf::getPathErrorPage(error_pages key) {
	return _error_pages[key];
}

const std::vector<Location>::iterator ServConf::getLocationKey(std::string key) {
	std::vector<Location>::iterator it = _locations.begin();
	std::vector<Location>::iterator ite = _locations.end();
	for (; it != ite; ++it) {
		if (it->getPath() == key)
			return it;
	}
	return it;
}

void ServConf::checkToken(std::string &parametr) {
	std::string::size_type pos = parametr.find(";");
	if (pos != std::string::npos)
		parametr.erase(pos);
}

bool ServConf::checkLocaitons() const {
	std::vector<Location>::const_iterator it = _locations.begin();
	std::vector<Location>::const_iterator ite = _locations.end();
	for (; it != ite; ++it) {
		if (isValidLocation(const_cast<Location &>(*it)) == 0)
			return false;
	}
	return true;
}

void ServConf::setupServer() {
	_server_address.sin_family = AF_INET;
	_server_address.sin_addr.s_addr = _host;
	_server_address.sin_port = htons(_port);
}

int ServConf::getFd() {
	return _listen_fd;
}
