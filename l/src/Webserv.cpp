#include "../inc/main.hpp"

Webserv::Webserv()
{
    config_path = "./conf/webserv.conf";
    if (parse_config(config_path))
         throw std::runtime_error("Config file not found");
}

Webserv::Webserv(std::string conf)
{
    config_path = conf;
    if (parse_config(config_path))
        throw std::runtime_error("Config file not found");
}

Webserv::Webserv(const Webserv &other)
{
    config_path = other.config_path;
    config_size = other.config_size;
    config = new std::string[config_size];
    for (int i = 0; i < config_size; i++)
        config[i] = other.config[i];
}

Webserv &Webserv::operator=(const Webserv &other)
{
    if (this == &other)
        return (*this);
    config_path = other.config_path;
    config_size = other.config_size;
    delete [] config;
    config = new std::string[config_size];
    for (int i = 0; i < config_size; i++)
        config[i] = other.config[i];
    return (*this);
}

Webserv::~Webserv()
{
    delete [] config;
}

// Config parsing
int Webserv::parse_config(const std::string& conf)
{
    int i = 0;
    std::string line;
    std::ifstream file(conf.c_str());

    if (!file.is_open())
        return 1;

    while (getline(file, line))
        i++;

    config_size = i;
    config = new std::string[i];
    file.close();
    file.open(conf.c_str());
    i = 0;

    while (getline(file, line))
    {
        config[i] = line;
        i++;
    }

    file.close();
    return 0;
}

std::string* Webserv::get_config() const
{
	return config;
}

int Webserv::get_config_size() const
{
	return config_size;
}

// utils functions for split config file
std::vector<std::string> ft_split(const std::string& s) {
	std::vector<std::string> tokens;
	std::string token;
	std::stringstream ss(s);
	while (ss >> token)
		tokens.push_back(token);
	return tokens;
}

std::vector<std::string> splitParametrs(std::string line, std::string sep)
{
	std::vector<std::string>	str;
	size_t		start, end;

	start = end = 0;
	while (1)
	{
		end = line.find_first_of(sep, start);
		if (end == std::string::npos)
			break;
		std::string tmp = line.substr(start, end - start);
		str.push_back(tmp);
		start = line.find_first_not_of(sep, end);
		if (start == std::string::npos)
			break;
	}
	return (str);
}
