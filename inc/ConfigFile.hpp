#ifndef CONFIGFILE_HPP
#define CONFIGFILE_HPP

#include "Webserv.hpp"

class ConfigFile {
	private:
		std::string		_config_path;
		std::string		*_config;
		int				_config_size;

	public:

		ConfigFile();
		ConfigFile(std::string conf);
		ConfigFile(const ConfigFile &other);
		ConfigFile &operator=(const ConfigFile &other);
		~ConfigFile();


		void			setConfigPath(std::string path);
		std::string		getConfigPath() const;
		void			setConfig(std::string *config);
		std::string		*getConfig() const;
		void			setConfigSize(int size);
		int				getConfigSize() const;

		void			parseConfig();
		void			parseServer(std::string *config, int *i, Server *server);
		void			parseLocation(std::string *config, int *i, Location *location);
		void			parseErrorPage(std::string *config, int *i, Server *server);
		void			parseCgi(std::string *config, int *i, Location *location);
		void			parseAutoIndex(std::string *config, int *i, Location *location);
		void			parseUploadDir(std::string *config, int *i, Location *location);
		void			parseMaxBodySize(std::string *config, int *i, Location *location);
		void			parseMethods(std::string *config, int *i, Location *location);
		void			parseIndex(std::string *config, int *i, Location *location);
		void			parseRoot(std::string *config, int *i, Location *location);
};

#endif
