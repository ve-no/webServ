#include "../../inc/Request.hpp"
#include "../../inc/RequestParser.hpp"


Request::Request()
{
}

Request::Request(const Request& other)
{
    m_method = other.m_method;
    m_path = other.m_path;
    m_version = other.m_version;
    m_body = other.m_body;
    m_headers = other.m_headers;
    m_queries = other.m_queries;
    m_cookies = other.m_cookies;
}

Request::~Request()
{
}

Request& Request::operator=(const Request& other)
{
    m_method = other.m_method;
    m_path = other.m_path;
    m_version = other.m_version;
    m_body = other.m_body;
    m_headers = other.m_headers;
    m_queries = other.m_queries;
    m_cookies = other.m_cookies;
    return *this;
}

void Request::parse(const std::string& request)
{
	RequestParser parser;
	parser.parse(request, *this);
}

void Request::setMethod(const std::string& method)
{
	m_method = method;
}

void Request::setPath(const std::string& path)
{
	m_path = path;
}

void Request::setVersion(const std::string& version)
{
	m_version = version;
}

void Request::setBody(const std::string& body)
{
	m_body = body;
}

void Request::setHeader(const std::string& key, const std::string& value)
{
	m_headers[key] = value;
}

void Request::setQuery(const std::string& key, const std::string& value)
{
	m_queries[key] = value;
}

void Request::setCookie(const std::string& key, const std::string& value)
{
	m_cookies[key] = value;
}

const std::string& Request::getMethod() const
{
	return m_method;
}

const std::string& Request::getPath() const
{
	return m_path;
}

const std::string& Request::getVersion() const
{
	return m_version;
}

const std::string& Request::getBody() const
{
	return m_body;
}

const std::string& Request::getHeader(const std::string& key) const
{
	return m_headers.at(key);
}

const std::string& Request::getQuery(const std::string& key) const
{
	return m_queries.at(key);
}

const std::string& Request::getCookie(const std::string& key) const
{
	return m_cookies.at(key);
}

bool Request::hasHeader(const std::string& key) const
{
	return m_headers.find(key) != m_headers.end();
}

bool Request::hasQuery(const std::string& key) const
{
	return m_queries.find(key) != m_queries.end();
}

bool Request::hasCookie(const std::string& key) const
{
	return m_cookies.find(key) != m_cookies.end();
}

void Request::removeHeader(const std::string& key)
{
	m_headers.erase(key);
}

void Request::removeQuery(const std::string& key)
{
	m_queries.erase(key);
}

void Request::removeCookie(const std::string& key)
{
	m_cookies.erase(key);
}

void Request::clearHeaders()
{
	m_headers.clear();
}

void Request::clearQueries()
{
	m_queries.clear();
}

void Request::clearCookies()
{
	m_cookies.clear();
}

void Request::forEachHeader(CallbackFunction callback) const
{
    for (std::map<std::string, std::string>::const_iterator it = m_headers.begin(); it != m_headers.end(); ++it)
    {
        callback(it->first, it->second);
    }
}

void Request::forEachQuery(CallbackFunction callback) const
{
    for (std::map<std::string, std::string>::const_iterator it = m_queries.begin(); it != m_queries.end(); ++it)
    {
        callback(it->first, it->second);
    }
}

void Request::forEachCookie(CallbackFunction callback) const
{
    for (std::map<std::string, std::string>::const_iterator it = m_cookies.begin(); it != m_cookies.end(); ++it)
    {
        callback(it->first, it->second);
    }
}