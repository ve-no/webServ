#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <cstring>

#include "./Request.hpp"

class Request;

// parsing the request using a state mechanism
class RequestParser {
	public:
		RequestParser();
		RequestParser(const RequestParser& other);
		~RequestParser();

		RequestParser& operator=(const RequestParser& other);

		void parse(const std::string& request, Request& req);

		void parseMethod(const std::string& request, Request& req);
		void parsePath(const std::string& request, Request& req);
		void parseVersion(const std::string& request, Request& req);
		void parseHeaderKey(const std::string& request, Request& req);
		void parseHeaderValue(const std::string& request, Request& req);
		// void parseQueryKey(const std::string& request, Request& req);
		// void parseQueryValue(const std::string& request, Request& req);
		// void parseCookieKey(const std::string& request, Request& req);
		// void parseCookieValue(const std::string& request, Request& req);
		void parseBody(const std::string& request, Request& req);
		void parseStart(const std::string& request, Request& req);
		void parseError(const std::string& request, Request& req);

		void parseHeaders(const std::string& request, Request& req);
		// void parseQueries(const std::string& request, Request& req);
		// void parseCookies(const std::string& request, Request& req);

	private:
		enum State {
			START,
			// METHOD,
			PATH,
			VERSION,
			HEADER,
			HEADER_KEY,
			HEADER_VALUE,
			// QUERY_KEY,
			// QUERY_VALUE,
			// COOKIE_KEY,
			// COOKIE_VALUE,
			BODY,
			ERROR
		};

		State m_state;
		std::string m_buffer;
		std::string m_key;
		std::string m_value;
};