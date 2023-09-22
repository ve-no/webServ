#ifndef SERVERCONFIG_HPP
#define SERVERCONFIG_HPP

#include "../inc/Webserv.hpp"

static std::string	serverParametrs[] = {"server_name", "listen", "root", "index", "allow_methods", "client_body_buffer_size"};

class Location;
class ServerConfig
{
private:
    uint16_t _port;
    in_addr_t _host;
    std::string _serverName;
    std::string _root;
    unsigned long _clientMaxBodySize;
    std::string _defaultIndex;
    bool _enableAutoindex;
    std::map<short, std::string> _customErrorPages;
    std::vector<Location> _locations;
    struct sockaddr_in _serverAddress;
    int _listenSocketFd;

public:
    ServerConfig();
    ~ServerConfig();
    ServerConfig(const ServerConfig &other);
    ServerConfig &operator=(const ServerConfig &rhs);

    void InitializeErrorPages();

    void SetServerName(std::string serverName);
    void SetHost(std::string hostParameter);
    void SetRoot(std::string rootDirectory);
    void SetListenSocketFd(int fd);
    void SetPort(std::string portParameter);
    void SetClientMaxBodySize(std::string sizeParameter);
    void SetErrorPages(std::vector<std::string> &errorPages);
    void SetDefaultIndex(std::string indexFilename);
    void SetLocation(std::string locationName, std::vector<std::string> parameters);
    void SetAutoindex(std::string autoindex);

    bool IsValidHost(std::string host) const;
    bool IsValidErrorPages();
    int IsValidLocation(Location &location) const;

    const std::string &GetServerName();
    const uint16_t &GetPort();
    const in_addr_t &GetHost();
    const size_t &GetClientMaxBodySize();
    const std::vector<Location> &GetLocations();
    const std::string &GetRoot();
    const std::map<short, std::string> &GetErrorPages();
    const std::string &GetDefaultIndex();
    const bool &IsAutoindexEnabled();
    const std::string &GetErrorPagePath(short key);
    const std::vector<Location>::iterator GetLocationByKey(std::string key);

    static void CheckToken(std::string &parameter);
    bool CheckLocations() const;

    void SetupServer();
    int GetListenSocketFd();
};

#endif
