#include "ConfigParser.hpp"

ConfigParser::ConfigParser()
{
	_nb_server = 0;
}

ConfigParser::~ConfigParser()
{
}

int ConfigParser::createCluster(const std::string &config_file)
{
	std::ifstream configFile(config_file.c_str()); // Replace with your config file path
	std::string content;
	std::string line;

	if (configFile.is_open()) {
		while (std::getline(configFile, line)) {
			content += line;
			content += "\n";
		}
		configFile.close();
	} else {
		std::cerr << "Error opening config file." << std::endl;
		return 1;
	}
	if (content.find("#") != std::string::npos)
		content.erase(content.find("#"));
	content.erase(0, content.find_first_not_of(" \t"));
	content.erase(content.find_last_not_of(" \t") + 1);
	splitServers(content);
	checkServers();
	return 0;
}

void ConfigParser::splitServers(std::string &content)
{
	size_t start = 0;
	size_t end = 0;

	while (end < content.size())
	{
		start = findStartServer(end, content);
		end = findEndServer(start, content);
		_server_config.push_back(content.substr(start, end - start));
	}
}

void ConfigParser::removeComments(std::string &content)
{
	size_t pos = 0;
	size_t start = 0;
	size_t end = 0;

	while (pos < content.size())
	{
		if (content[pos] == '#')
		{
			start = pos;
			end = pos;
			while (content[end] != '\n')
				end++;
			content.erase(start, end - start);
		}
		pos++;
	}
}

void ConfigParser::removeWhiteSpace(std::string &content)
{
	size_t pos = 0;
	size_t start = 0;
	size_t end = 0;

	while (pos < content.size())
	{
		if (content[pos] == '\n')
		{
			start = pos;
			end = pos;
			while (content[end] == '\n')
				end++;
			content.erase(start, end - start - 1);
		}
		pos++;
	}
}

size_t ConfigParser::findStartServer(size_t start, std::string &content)
{
	size_t pos = start;

	while (pos < content.size())
	{
		if (content[pos] == '{')
			return (pos + 1);
		pos++;
	}
	return (pos);
}

size_t ConfigParser::findEndServer(size_t start, std::string &content)
{
	size_t pos = start;
	size_t nb_bracket = 1;

	while (pos < content.size())
	{
		if (content[pos] == '{')
			nb_bracket++;
		else if (content[pos] == '}')
			nb_bracket--;
		if (nb_bracket == 0)
			return (pos);
		pos++;
	}
	return (pos);
}

void ConfigParser::createServer(std::string &config, ServerConfig &server)
{
	size_t pos = 0;
	size_t start = 0;
	size_t end = 0;

	while (pos < config.size())
	{
		if (config[pos] == ';')
		{
			end = pos;
			server.setServerConfig(config.substr(start, end - start));
			start = end + 1;
		}
		pos++;
	}
}

void ConfigParser::checkServers()
{
	size_t pos = 0;
	size_t start = 0;
	size_t end = 0;
	ServerConfig server;

	while (pos < _server_config.size())
	{
		start = 0;
		end = 0;
		while (end < _server_config[pos].size())
		{
			if (_server_config[pos][end] == ';')
			{
				server.setServerConfig(_server_config[pos].substr(start, end - start));
				start = end + 1;
			}
			end++;
		}
		_servers.push_back(server);
		pos++;
	}
}

std::vector<ServerConfig> ConfigParser::getServers()
{
	return (_servers);
}

int ConfigParser::stringCompare(std::string str1, std::string str2, size_t pos)
{
	size_t i = 0;

	while (i < str1.size() && i < str2.size())
	{
		if (str1[i] != str2[i + pos])
			return (0);
		i++;
	}
	return (1);
}

int ConfigParser::print()
{
	size_t pos = 0;
	size_t start = 0;
	size_t end = 0;

	while (pos < _server_config.size())
	{
		std::cout << "SERVER " << pos << std::endl;
		start = 0;
		end = 0;
		while (end < _server_config[pos].size())
		{
			if (_server_config[pos][end] == ';')
			{
				std::cout << _server_config[pos].substr(start, end - start) << std::endl;
				start = end + 1;
			}
			end++;
		}
		pos++;
	}
	return (0);
}
