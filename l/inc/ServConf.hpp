#pragma once


// #include "Webserv.hpp"
# include "main.hpp"

class Location;

enum error_pages
{
	SUCCESS = 200,
	BAD_REQUEST = 400,
	UNAUTHORIZED = 401,
	FORBIDDEN = 403,
	NOT_FOUND = 404,
	METHOD_NOT_ALLOWED = 405,
	REQUEST_ENTITY_TOO_LARGE = 413,
	INTERNAL_SERVER_ERROR = 500,
	NOT_IMPLEMENTED = 501,
	BAD_GATEWAY = 502,
	SERVICE_UNAVAILABLE = 503,
	GATEWAY_TIMEOUT = 504,
	HTTP_VERSION_NOT_SUPPORTED = 505,
};

class ServConf
{
	public:
		ServConf();
		~ServConf();
		ServConf(const ServConf &other);
		ServConf &operator=(const ServConf & rhs);

		void	setServerName(std::string server_name);
		const	std::string	&getServerName();

		void	setHost(std::string parametr);
		const	in_addr_t &getHost();

		void	setRoot(std::string root);
		const	std::string	&getRoot();

		void	setFd(int);
		int		getFd();

		void	setListen(std::string parametr);
		const	uint16_t	&getPort();

		void	setClientMaxBodySize(std::string parametr);
		const	size_t &getClientMaxBodySize();

		void	setErrorPages(std::vector<std::string> &parametr);
		const	std::map<error_pages, std::string>&getErrorPages();

		void	setIndex(std::string index);
		const	std::string	&getIndex();

		void	setLocation(std::string nameLocation, std::vector<std::string> parametr);
		const	std::vector<Location>	&getLocations();

		void	setAutoindex(std::string autoindex);
		const	bool	&getAutoindex();


		const	std::string	&getPathErrorPage(error_pages key);
		const	std::vector<Location>::iterator	getLocationKey(std::string key);
		int			isValidLocation(Location &location) const;
		static void	checkToken(std::string &parametr);
		bool		checkLocaitons() const;
		bool		isValidErrorPages();
		static int getTypePath(std::string const path);
		static int accessFile(std::string const path, int mode);
		static std::string	fileToString(std::string path);
		static int isReadableAndExist(std::string const path, std::string const index);

	private:
		uint16_t							port;
		in_addr_t							host;
		std::string							nameServer;
		std::string							root;
		unsigned long						clientMaxBodySize;
		std::string							index;
		bool								autoindex;
		std::map<error_pages, std::string>	_errorPages;
		std::vector<Location> 				locations;
		struct sockaddr_in 					serveraddress;
		int									listenFd;
		std::string							uploadPath;
};

