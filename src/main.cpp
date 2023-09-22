#include "../inc/main.hpp"

// int main(int ac, char **av)
// {
// 	try
// 	{
// 		Webserv webserv;
// 		if (ac == 2)
// 			webserv = Webserv(av[1]);

// 		int i = 0;
// 		while (i < webserv.get_config_size())
// 		{
// 			std::cout << webserv.get_config()[i] << std::endl;
// 			i++;
// 		}
// 	}
// 	catch (std::exception &e)
// 	{
// 		std::cout << e.what() << std::endl;
// 	}
// 	return (0);
// }

// Define callback functions for printing headers, queries, and cookies
void printHeaderCallback(const std::string& key, const std::string& value) {
    std::cout << "\t" << key << ": " << value << std::endl;
}

void printQueryCallback(const std::string& key, const std::string& value) {
    std::cout << "\t" << key << ": " << value << std::endl;
}

void printCookieCallback(const std::string& key, const std::string& value) {
    std::cout << "\t" << key << ": " << value << std::endl;
}

void print_request(const Request& req)
{
    std::cout << "Method: " << req.getMethod() << std::endl;
    std::cout << "Path: " << req.getPath() << std::endl;
    std::cout << "Version: " << req.getVersion() << std::endl;
    std::cout << "Body: " << req.getBody() << std::endl;
    std::cout << "Headers:" << std::endl;
    req.forEachHeader(printHeaderCallback);
    std::cout << "Queries:" << std::endl;
    req.forEachQuery(printQueryCallback);
    std::cout << "Cookies:" << std::endl;
    req.forEachCookie(printCookieCallback);
}


int main()
{
	// example request string
	std::string request = "GET / HTTP/1.1\r\nHost: localhost:8080\r\nUser-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:84.0) Gecko/20100101 Firefox\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n";

	Request req;
	req.parse(request);
	print_request(req);
	return (0);
}