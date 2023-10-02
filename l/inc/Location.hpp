#pragma once

#include "main.hpp"

class Location
{
	public:
		Location();
		Location(const Location &other);
		Location &operator=(const Location &rhs);
		~Location();

		void setPath(std::string parametr);
		const std::string &getPath() const;

		void setRootLocation(std::string parametr);
		const std::string &getRootLocation() const;

		void setMethods(std::vector<std::string> methods);
		const std::vector<bool> &getMethods() const;

		void setAutoindex(std::string parametr);
		const bool &getAutoindex() const;

		void setIndexLocation(std::string parametr);
		const std::string &getIndexLocation() const;

		void setReturn(std::string parametr);
		const std::string &getReturn() const;

		void setAlias(std::string parametr);
		const std::string &getAlias() const;

		void setCgiPath(std::vector<std::string> path);
		const std::vector<std::string> &getCgiPath() const;

		void setCgiExtension(std::vector<std::string> extension);
		const std::vector<std::string> &getCgiExtension() const;

		void setMaxBodySize(std::string parametr);
		const unsigned long &getMaxBodySize() const;

		std::string getPrintMethods() const;

	private:
		std::string					path;
		std::string					root;
		bool						autoindex;
		std::string					index;
		std::vector<bool>			_methods; // GET POST DELETE
		std::string					_return;
		std::string					_alias;
		std::vector<std::string>	cgi_path;
		std::vector<std::string>	cgi_extension;
		unsigned long				client_max_body_size;
};

