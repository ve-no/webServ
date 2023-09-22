#include "../../inc/RequestParser.hpp"

// parsing the request using a state mechanism
RequestParser::RequestParser() : m_state(START)
{
}

RequestParser::RequestParser(const RequestParser& other)
{
	m_state = other.m_state;
	m_buffer = other.m_buffer;
	m_key = other.m_key;
	m_value = other.m_value;
}

RequestParser::~RequestParser()
{
}

RequestParser& RequestParser::operator=(const RequestParser& other)
{
	m_state = other.m_state;
	m_buffer = other.m_buffer;
	m_key = other.m_key;
	m_value = other.m_value;
	return *this;
}

void	RequestParser::parseMethod(const std::string& request, Request& req)
{
	req.setMethod(request);
	m_state = PATH;
}

void	RequestParser::parsePath(const std::string& request, Request& req)
{
	req.setPath(request);
	m_state = VERSION;
}

void	RequestParser::parseVersion(const std::string& request, Request& req)
{
	req.setVersion(request);
	m_state = HEADER;
}

void	RequestParser::parseHeaderKey(const std::string& request, Request& req)
{
	(void)req;
	size_t pos = request.find(": ");
	if (pos == std::string::npos)
	{
		m_state = ERROR;
		return ;
	}
	m_key = request.substr(0, pos);
	m_buffer = request.substr(pos + 2);
	m_state = HEADER_VALUE;
}

void	RequestParser::parseHeaderValue(const std::string& request, Request& req)
{
	size_t pos = request.find("\r\n");
	if (pos == std::string::npos)
	{
		m_state = ERROR;
		return ;
	}
	m_value = request.substr(0, pos);
	req.setHeader(m_key, m_value);
	m_buffer = request.substr(pos + 2);
	m_state = HEADER;
}

void	RequestParser::parseBody(const std::string& request, Request& req)
{
	req.setBody(request);
	m_state = START;
}

// void	RequestParser::parseStart(const std::string& request, Request& req)
// {
// 	(void)req;
// 	size_t pos = request.find("\r\n\r\n");
// 	if (pos == std::string::npos)
// 	{
// 		m_state = ERROR;
// 		return ;
// 	}
// 	m_buffer = request.substr(pos + 4);
// 	m_state = BODY;
// }

void	RequestParser::parseError(const std::string& request, Request& req)
{
	(void)request;
	(void)req;
	std::cout << "Error" << std::endl;
}

void	RequestParser::parseHeaders(const std::string& request, Request& req)
{
	size_t pos = request.find("\r\n");
	if (pos == std::string::npos)
	{
		m_state = ERROR;
		return ;
	}
	std::string header = request.substr(0, pos);
	if (header.empty())
	{
		m_buffer = request.substr(pos + 2);
		m_state = START;
		return ;
	}
	m_buffer = request.substr(pos + 2);
	parseHeaderKey(header, req);
}

void splitString(const std::string& input, char delimiter, std::vector<std::string>& result) {
    std::istringstream stream(input);
    std::string token;
    
    while (std::getline(stream, token, delimiter)) {
        result.push_back(token);
    }
}

void	RequestParser::parseStart(const std::string& request, Request& req)
{
	// gets a string in the format: METHOD PATH VERSION
	// splits the string into a vector of strings
	std::vector<std::string> parts;
	char delimiter = ' ';
	splitString(request, delimiter, parts);

	// if the vector has less than 3 parts, the request is invalid
	if (parts.size() < 3)
	{
		m_state = ERROR;
		return ;
	}

	// set the method, path, and version of the request
	parseMethod(parts[0], req);
	parsePath(parts[1], req);
	parseVersion(parts[2], req);
}

void	RequestParser::parse(const std::string& request, Request& req)
{
	(void)req;
	// const char *req_s = request.c_str();
	char delimiter = '\n';
    std::vector<std::string> parts;

	splitString(request, delimiter, parts);
	for (size_t i = 0; i < parts.size(); i++)
	{
		switch (m_state)
		{
			case START:
				parseStart(parts[i], req);
				break ;
			case HEADER:
				parseHeaders(parts[i], req);
				break ;
			case HEADER_KEY:
				parseHeaderKey(parts[i], req);
				break ;
			case HEADER_VALUE:
				parseHeaderValue(parts[i], req);
				break ;
			case BODY:
				parseBody(parts[i], req);
				break ;
			default:
				break ;
		}
	}
}
