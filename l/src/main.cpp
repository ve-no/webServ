#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "../inc/main.hpp"

#define RED_BOLD "\033[1;31m"
#define GREEN_BOLD "\033[1;32m"
#define YELLOW_BOLD "\033[1;33m"
#define BLUE_BOLD "\033[1;34m"
#define MAGENTA_BOLD "\033[1;35m"
#define WHITE_BOLD "\033[1;37m"
#define RESET "\033[0m"

#define RESPONSE_200 "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: 485\r\n\r\n<!DOCTYPE html>\r\n<html lang='en'>\r\n<head>\r\n<meta charset='UTF-8'>\r\n<meta name='viewport' content='width=device-width, initial-scale=1.0'>\r\n<title>KAWKAWA3</title>\r\n<style>\r\n*{margin:0;padding:0;box-sizing:border-box;}\r\nbody {\r\nwidth: 100%;\r\nheight: 100vh;\r\ndisplay: flex;\r\nalign-items: center;\r\njustify-content: center;\r\nbackground-color: #2e2e2e;\r\ncolor: #fff;\r\n}\r\nh1 {\r\nfont-family: 'Courier New', Courier, monospace;\r\n}\r\n</style>\r\n</head>\r\n<body>\r\n<h1>KAWKAWA</h1>\r\n</body>\r\n</html>"
#define RESPONSE_404 "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\nContent-Length: 491\r\n\r\n<!DOCTYPE html>\r\n<html lang='en'>\r\n<head>\r\n<meta charset='UTF-8'>\r\n<meta name='viewport' content='width=device-width, initial-scale=1.0'>\r\n<title>Document</title>\r\n<style>\r\n*{margin:0;padding:0;box-sizing:border-box;}\r\nbody {\r\nwidth: 100%;\r\nheight: 100vh;\r\ndisplay: flex;\r\nalign-items: center;\r\njustify-content: center;\r\nbackground-color: #2e2e2e;\r\ncolor: #fff;\r\n}\r\nh1 {\r\nfont-family: 'Courier New', Courier, monospace;\r\n}\r\n</style>\r\n</head>\r\n<body>\r\n<h1>404 Not Found</h1>\r\n</body>\r\n</html>"
#define RESPONSE_500 "HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/html\r\nContent-Length: 503\r\n\r\n<!DOCTYPE html>\r\n<html lang='en'>\r\n<head>\r\n<meta charset='UTF-8'>\r\n<meta name='viewport' content='width=device-width, initial-scale=1.0'>\r\n<title>Document</title>\r\n<style>\r\n*{margin:0;padding:0;box-sizing:border-box;}\r\nbody {\r\nwidth: 100%;\r\nheight: 100vh;\r\ndisplay: flex;\r\nalign-items: center;\r\njustify-content: center;\r\nbackground-color: #2e2e2e;\r\ncolor: #fff;\r\n}\r\nh1 {\r\nfont-family: 'Courier New', Courier, monospace;\r\n}\r\n</style>\r\n</head>\r\n<body>\r\n<h1>500 Internal Server Error</h1>\r\n</body>\r\n</html>"
void handleClientRequest(int client_sock, std::vector<ServConf> servers);

void handleErrorAndExit(const char* errorMessage, int sockfd = -1) {
    std::cerr << RED_BOLD << errorMessage << RESET << std::endl;
    if (sockfd != -1) {
        close(sockfd);
    }
    exit(1);
}

int createServerSocket() {
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        handleErrorAndExit("Socket error");
    }
    return server_sock;
}

void setSocketReuseOption(int server_sock) {
    int reuse = 1;
    if (setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
        handleErrorAndExit("Setsockopt error", server_sock);
    }
}

void bindSocketToAddress(int server_sock, const in_addr_t ip_address, const	uint16_t port) {
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = ip_address;
    server_addr.sin_port = htons(port);

    if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        handleErrorAndExit("Bind error", server_sock);
    }
}

void startListening(int server_sock, std::string ip_address, const	uint16_t port) {
    if (listen(server_sock, 5) < 0) {
        handleErrorAndExit("Listen error", server_sock);
    }
    std::cout << GREEN_BOLD << "Mini web server is listening on http://" << ip_address << ":" << port << RESET << std::endl;
}

void mini_webserver(std::vector<ServConf> servers) {
    const in_addr_t ip_address = servers[0].getHost();
    // std::cout << ip_address << std::endl;

    const	uint16_t port = servers[0].getPort();
    std::string ip = servers[0].getIP();
    std::cout << "hi" << ip << std::endl;
    std::cout << port << std::endl;
    std::vector<Location> loc = servers[0].getLocations();
// std::cout << loc[0].loc_name << std::endl;

    int server_sock = createServerSocket();
    setSocketReuseOption(server_sock);
    bindSocketToAddress(server_sock, ip_address, port);
    std::cout << "hello  " << servers[0].getIP() << std::endl;
    startListening(server_sock, servers[0].getIP(), port);

    while (true) {
        std::cout << std::endl << YELLOW_BOLD << "Waiting for connection..." << RESET << std::endl << std::endl;

        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_len);

        if (client_sock < 0) {
            std::cerr << RED_BOLD << "Accept error" << RESET << std::endl;
            continue;
        }
        handleClientRequest(client_sock, servers);
    }

    close(server_sock);
}

#include "../inc/main.hpp"

// #define TEMP_ROOT_PATH "/nfs/homes/aachhoub/Desktop/webserv"

// #define TEMP_ROOT_PATH "/home/astro/Desktop/webserverx"
#define TEMP_ROOT_PATH "/home/venom/Desktop/webServer_42/l"
// #define TEMP_ROOT_PATH "/nfs/homes/ibouchaf/Desktop/webserv"
#define REQ_PATH "/"

// void Config_Loc::parseConfig()
// {
//     client_max_body_size = 100;

//     Location location1;
//     location1.loc_name = REQ_PATH;
//     location1.methods.push_back("GET");
//     location1.methods.push_back("POST");
//     location1.methods.push_back("DELETE");
//     location1.root = TEMP_ROOT_PATH;
//     location1.upload = "/var/www/uploads";
//     //location1.client_max_body_size = 100;
//     location1.auto_index = "ON";
//     //location1.Return = "/redirect";
//     location1.cgi_path = "/cgi-bin";
//     location1.Index.push_back("index.html");
//     // location1.Index.push_back("index.php");

//     std::vector<std::string> error_codes;
//     error_codes.push_back("404");
//     error_codes.push_back("405");
//     error_codes.push_back("503");
//     error_codes.push_back("504");
//     std::string error_path = "/Response/status_codes";

//     location1.error_page.push_back(std::make_pair(error_codes, error_path));


//     Location location2;
//     location2.loc_name = "/upload";
//     location2.methods.push_back("GET");
//     location2.root = TEMP_ROOT_PATH;
//     location2.upload = "/var/www/uploads";
//     //location2.client_max_body_size = 50;
//     location2.auto_index = "off";
//     location2.Return = "/redirect2";
//     location2.cgi_path = "/cgi-bin";
//     location2.Index.push_back("index.html");

//     location2.error_page.push_back(std::make_pair(error_codes, error_path));

//     locations.push_back(location1);
//     locations.push_back(location2);
// }

char *strjoin(char *dest, char *src, int dest_len, int src_len)
{
	char *ret = (char *)calloc(1, dest_len + src_len + 1);
	int i = 0;
	int j = 0;
	while (i < dest_len)
	{
		ret[i] = dest[i];
		i++;
	}
	while (j < src_len)
	{
		ret[i + j] = src[j];
		j++;
	}
	ret[i + j] = '\0';
	free(dest);
	return ret;
}

#define BUFFER_SIZE 1024

void handleClientRequest(int client_sock, std::vector<ServConf> servers) {
	// PARSING LOC STARTS
    // Config_Loc config_file;
	// config_file.parseConfig();
    // PARSING LOC ENDS
    Request req;

	char *request = (char *)calloc(1, 1);
	int request_len = 0;
	char buffer[BUFFER_SIZE + 1];
	bool read_flag = true;
	bool close_flag = false;
	while (true)
	{
		int bytes_read = recv(client_sock, buffer, BUFFER_SIZE, 0);
		buffer[bytes_read] = '\0';
		request = strjoin(request, buffer, request_len, bytes_read);
		request_len += bytes_read;
        if (bytes_read < 0)
        {
			read_flag = false;
            break;
        }

        if (bytes_read == 0)
        {
			close_flag = true;
            break;
        }

        if (bytes_read != 0)
        {
            req.parse(buffer, bytes_read);
            if (req.parsingCompleted() || req.errorCode() != 0)
                break;
        }
	}
	try {
		// Third Step (Response generation)
		Response res(req, servers);
		res.respond();
		if (req.getErrorCode() != 0)
			res.set_response(res.generateErrorResponse(req.getErrorCode()));
		else if (close_flag)
			res.set_response(res.generateErrorResponse(400));
		else if (!read_flag)
			res.set_response(res.generateErrorResponse(500));
		std::string response_string = res.get_response();
		const char* response = response_string.c_str();
		size_t total = 0;
        int bytesleft = response_string.length();
        int n;
        while (total < response_string.length())
        {
            n = send(client_sock, response + total, bytesleft, 0);
            if (n == -1) {break;}
            total += n;
            bytesleft -= n;
        }
    	close(client_sock);
	}
	catch (std::exception& e) {

		const char* response = RESPONSE_500;
		send(client_sock, response, strlen(response), 0);
    	close(client_sock);
		std::cout << e.what() << std::endl;
	}
}

#include "../inc/main.hpp"

int main(int argc, char **argv)
{
    std::string config_file_path;
    if (argc == 2)
        config_file_path = argv[1];
    else
        config_file_path = "./conf/default.conf";
    try {
        ParseConfigFile config_file;
        config_file.parseConfigFile(config_file_path);
        mini_webserver(config_file.getServers());
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
