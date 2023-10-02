#include "Webserv.hpp"

// test for config file parsing

int main (int ac, char **av) {

	// if (ac != 2) {
	// 	std::cout << "Usage: ./webserv <config_file>" << std::endl;
	// 	return 1;
	// }
	// else {
		char* conf = NULL;
		if (ac == 2)
			conf = av[1];
		std::string config_file;
		conf ? config_file = conf : config_file = "conf/default.conf";
		ParseConfigFile parse;
		try {
			parse.parseConfigFile(config_file);
		}
		catch (std::exception &e) {
			std::cout << e.what() << std::endl;
			return 1;
		}
		parse.print();
}
// }
