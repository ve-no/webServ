# include "Location.hpp"

Location::Location() {
	_path = "";
	_root = "";
	_autoindex = false;
	_index = "";
	_methods = std::vector<bool>(3, false);
	_return = "";
	_alias = "";
	_cgi_path = std::vector<std::string>();
	_cgi_ext = std::vector<std::string>();
	_client_max_body_size = MAX_CONTENT_LENGTH;
}

Location::Location(const Location &other) {
	*this = other;
}

Location &Location::operator=(const Location &rhs) {
	if (this != &rhs) {
		_path = rhs._path;
		_root = rhs._root;
		_autoindex = rhs._autoindex;
		_index = rhs._index;
		_methods = rhs._methods;
		_return = rhs._return;
		_alias = rhs._alias;
		_cgi_path = rhs._cgi_path;
		_cgi_ext = rhs._cgi_ext;
		_client_max_body_size = rhs._client_max_body_size;
	}
	return (*this);
}

Location::~Location() {}

// setters
void Location::setMethods(std::vector<std::string> methods) {
	for (size_t i = 0; i < methods.size(); i++) {
		if (methods[i] == "GET")
			_methods[0] = true;
		else if (methods[i] == "POST")
			_methods[1] = true;
		else if (methods[i] == "DELETE")
			_methods[2] = true;
		else
			throw std::runtime_error("Error: invalid method");
	}
}

void Location::setAutoindex(std::string parametr) {
	if (parametr == "on")
		_autoindex = true;
	else if (parametr == "off")
		_autoindex = false;
	else
		throw std::runtime_error("Error: invalid autoindex");
}

void Location::setRootLocation(std::string parametr) { _root = parametr; }

void Location::setPath(std::string parametr) { _path = parametr; }

void Location::setIndexLocation(std::string parametr) { _index = parametr; }

void Location::setReturn(std::string parametr) { _return = parametr; }

void Location::setAlias(std::string parametr) { _alias = parametr; }

void Location::setCgiPath(std::vector<std::string> path) { _cgi_path = path; }

void Location::setCgiExtension(std::vector<std::string> extension) { _cgi_ext = extension; }

void Location::setMaxBodySize(std::string parametr) { _client_max_body_size = std::stoi(parametr); }

void Location::setMaxBodySize(unsigned long parametr) { _client_max_body_size = parametr; }

// getters
const std::string &Location::getPath() const { return (_path); }

const std::string &Location::getRootLocation() const { return (_root); }

const std::vector<bool> &Location::getMethods() const { return (_methods); }

const bool &Location::getAutoindex() const { return (_autoindex); }

const std::string &Location::getIndexLocation() const { return (_index); }

const std::string &Location::getReturn() const { return (_return); }

const std::string &Location::getAlias() const { return (_alias); }

const std::vector<std::string> &Location::getCgiPath() const { return (_cgi_path); }

const std::vector<std::string> &Location::getCgiExtension() const { return (_cgi_ext); }

const std::map<std::string, std::string> &Location::getExtensionPath() const { return (_ext_path); }

const unsigned long &Location::getMaxBodySize() const { return (_client_max_body_size); }

std::string Location::getPrintMethods() const {
	std::string result = "";
	if (_methods[0])
		result += "GET ";
	if (_methods[1])
		result += "POST ";
	if (_methods[2])
		result += "DELETE ";
	return (result);
}

