#include "ConfigFile.hpp"

ConfigFile::ConfigFile() {}

ConfigFile::~ConfigFile() {}

// define is path is directory or file
int ConfigFile::getTypePath(std::string const path) {
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
int ConfigFile::accessFile(std::string const path, int mode) {
	if (access(path.c_str(), mode) == -1)
		return -1;
	return 0;
}

// Read file to string
std::string ConfigFile::fileToString(std::string path) {
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

int ConfigFile::isReadableAndExist(std::string const path, std::string const index) {
	int		type;
	// int		access;

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

