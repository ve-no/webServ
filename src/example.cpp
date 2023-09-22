#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define RED_BOLD "\033[1;31m"
#define GREEN_BOLD "\033[1;32m"
#define YELLOW_BOLD "\033[1;33m"
#define BLUE_BOLD "\033[1;34m"
#define MAGENTA_BOLD "\033[1;35m"
#define WHITE_BOLD "\033[1;37m"
#define RESET "\033[0m"

#define RESPONSE_200 "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: 485\r\n\r\n<!DOCTYPE html>\r\n<html lang='en'>\r\n<head>\r\n<meta charset='UTF-8'>\r\n<meta name='viewport' content='width=device-width, initial-scale=1.0'>\r\n<title>KAWKAWA3</title>\r\n<style>\r\n*{margin:0;padding:0;box-sizing:border-box;}\r\nbody {\r\nwidth: 100%;\r\nheight: 100vh;\r\ndisplay: flex;\r\nalign-items: center;\r\njustify-content: center;\r\nbackground-color: #2e2e2e;\r\ncolor: #fff;\r\n}\r\nh1 {\r\nfont-family: 'Courier New', Courier, monospace;\r\n}\r\n</style>\r\n</head>\r\n<body>\r\n<h1>KAWKAWA</h1>\r\n</body>\r\n</html>"
#define RESPONSE_404 "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\nContent-Length: 491\r\n\r\n<!DOCTYPE html>\r\n<html lang='en'>\r\n<head>\r\n<meta charset='UTF-8'>\r\n<meta name='viewport' content='width=device-width, initial-scale=1.0'>\r\n<title>Document</title>\r\n<style>\r\n*{margin:0;padding:0;box-sizing:border-box;}\r\nbody {\r\nwidth: 100%;\r\nheight: 100vh;\r\ndisplay: flex;\r\nalign-items: center;\r\njustify-content: center;\r\nbackground-color: #2e2e2e;\r\ncolor: #fff;\r\n}\r\nh1 {\r\nfont-family: 'Courier New', Courier, monospace;\r\n}\r\n</style>\r\n</head>\r\n<body>\r\n<h1>404 Not Found</h1>\r\n</body>\r\n</html>"

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

void bindSocketToAddress(int server_sock, const char* ip_address, int port) {
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip_address);
    server_addr.sin_port = htons(port);

    if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        handleErrorAndExit("Bind error", server_sock);
    }
}

void startListening(int server_sock, const char* ip_address, int port) {
    if (listen(server_sock, 5) < 0) {
        handleErrorAndExit("Listen error", server_sock);
    }
    std::cout << GREEN_BOLD << "Mini web server is listening on http://" << ip_address << ":" << port << RESET << std::endl;
}

void handleClientRequest(int client_sock) {
    char buffer[30000] = {0};
    read(client_sock, buffer, 30000);
    std::cout << buffer << std::endl;

    const char* response = RESPONSE_200;
    send(client_sock, response, strlen(response), 0);
    close(client_sock);
}

void mini_webserver() {
    const char* ip_address = "127.0.0.1";
    int port = 5000;

    int server_sock = createServerSocket();
    setSocketReuseOption(server_sock);
    bindSocketToAddress(server_sock, ip_address, port);
    startListening(server_sock, ip_address, port);

    while (true) {
        std::cout << std::endl << YELLOW_BOLD << "Waiting for connection..." << RESET << std::endl << std::endl;

        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_len);

        if (client_sock < 0) {
            std::cerr << RED_BOLD << "Accept error" << RESET << std::endl;
            continue;
        }

        handleClientRequest(client_sock);
    }

    close(server_sock);
}

int main()
{
    mini_webserver();
    return 0;
}
