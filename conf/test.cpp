#include <iostream>
#include <fstream>
#include <string>
#include <map>

int main() {
    std::ifstream configFile("webserv.conf"); // Replace with your config file path
    std::map<std::string, std::string> configMap;

    if (configFile.is_open()) {
        std::string line;
        std::string currentSection; // To keep track of the current section

        while (std::getline(configFile, line)) {
            // Remove leading and trailing whitespaces
            if (line.find("#") != std::string::npos)
                line.erase(line.find("#"));
            line.erase(0, line.find_first_not_of(" \t"));
            line.erase(line.find_last_not_of(" \t") + 1);

            // Skip empty lines and comments
            if (line.empty() || line[0] == '#') {
                continue;
            }

            // Check if the line defines a new section
            if (line[0] == '[' && line[line.size() - 1] == ']') {
                currentSection = line.substr(1, line.size() - 2);
                continue;
            }
            

            // Split the line into key and value
            size_t separatorPos = line.find(' ');
            if (separatorPos != std::string::npos) {
                std::string key = line.substr(0, separatorPos);
                std::string value = line.substr(separatorPos + 1);
                std::cout << "separatorPos: " << key   << std::endl;

                // Store the key-value pair in the map with the section as a prefix
                if (!currentSection.empty()) {
                    key = currentSection + "." + key;
                }

                configMap[key] = value;
            }
        }

        configFile.close();
    } else {
        std::cerr << "Error opening config file." << std::endl;
        return 1;
    }

    // Access and print values from the map
    std::cout << "Listening port: " << configMap["server.listen"] << std::endl;
    std::cout << "Root folder: " << configMap["server.root"] << std::endl;

    return 0;
}
