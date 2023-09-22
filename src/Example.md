# mini-webserv docs:

```cpp
void handleErrorAndExit(const char* errorMessage, int sockfd = -1) {
    std::cerr << RED_BOLD << errorMessage << RESET << std::endl;
    if (sockfd != -1) {
        close(sockfd);
    }
    exit(1);
}
```

This function handles errors. It prints the given `errorMessage` in red to the standard error stream (usually the console). If a socket file descriptor (`sockfd`) is provided, it closes the socket and exits the program with an error code.

```cpp
int createServerSocket() {
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        handleErrorAndExit("Socket error");
    }
    return server_sock;
}
```

This function creates a socket for the server to listen for incoming connections. It uses the `socket` system call to create a socket with the following characteristics:
- `AF_INET` specifies IPv4.
- `SOCK_STREAM` specifies a TCP socket.
- `0` specifies the default protocol.

If the socket creation fails (returns a value less than 0), it calls `handleErrorAndExit` to handle the error. Otherwise, it returns the socket file descriptor.

```cpp
void setSocketReuseOption(int server_sock) {
    int reuse = 1;
    if (setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
        handleErrorAndExit("Setsockopt error", server_sock);
    }
}
```

This function sets the `SO_REUSEADDR` socket option on the server socket. This option allows reusing the same address and port even if the server has recently closed. It uses the `setsockopt` system call. If it encounters an error, it calls `handleErrorAndExit` to handle the error.

```cpp
void bindSocketToAddress(int server_sock, const char* ip_address, int port) {
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip_address);
    server_addr.sin_port = htons(port);

    if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        handleErrorAndExit("Bind error", server_sock);
    }
}
```

This function binds the server socket to a specific IP address and port. It does the following:
- Creates a `struct sockaddr_in` called `server_addr` to hold socket address information.
- Sets the address family to `AF_INET` (IPv4).
- Sets the IP address to the provided `ip_address`.
- Sets the port number to the provided `port`.

Then, it uses the `bind` system call to associate the server socket with this address. If it encounters an error, it calls `handleErrorAndExit` to handle the error.

```cpp
void startListening(int server_sock, const char* ip_address, int port) {
    if (listen(server_sock, 5) < 0) {
        handleErrorAndExit("Listen error", server_sock);
    }
    std::cout << GREEN_BOLD << "Mini web server is listening on http://" << ip_address << ":" << port << RESET << std::endl;
}
```

This function makes the server socket start listening for incoming connections. It uses the `listen` system call to set the socket in listening mode with a maximum backlog of 5 pending connections. If it encounters an error, it calls `handleErrorAndExit` to handle the error. It also prints a message indicating that the server is listening on a specific IP address and port.

```cpp
void handleClientRequest(int client_sock) {
    char buffer[30000] = {0};
    read(client_sock, buffer, 30000);
    std::cout << buffer << std::endl;

    const char* response = RESPONSE_200;
    send(client_sock, response, strlen(response), 0);
    close(client_sock);
}
```

This function handles a client's request after accepting a connection. It does the following:
- Declares a character array `buffer` to store the client's request.
- Reads data from the `client_sock` socket into the `buffer`.
- Prints the content of the `buffer` to the console.
- Defines an HTTP response message as `response`.
- Sends the `response` to the client using the `send` system call.
- Closes the `client_sock` socket to terminate the connection with the client.

```cpp
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
```

This is the main function of the web server. Here's what it does:
- Defines the server's IP address as "127.0.0.1" and the port as 5000.
- Calls `createServerSocket` to create the server socket.
- Calls `setSocketReuseOption` to set the `SO_REUSEADDR` socket option.
- Calls `bindSocketToAddress` to bind the server socket to the specified IP address and port.
- Calls `startListening` to make the server socket start listening for incoming connections.

Then, it enters an infinite loop where it continuously waits for and handles incoming connections from clients. It displays a "Waiting for connection..." message on the console while waiting. If an error occurs during connection acceptance, it prints an error message and continues waiting for the next connection. When a connection is accepted, it calls `handleClientRequest` to handle the client's request. Finally, it closes the server socket when the program exits.