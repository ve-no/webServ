#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <functional>
#include <sstream>

#include "./RequestParser.hpp"

typedef void (*CallbackFunction)(const std::string& key, const std::string& value);

class Request
{
	public:
		Request();
		Request(const Request& other);
		~Request();
	
		Request& operator=(const Request& other);
		
		void parse(const std::string& request);
	
		void setMethod(const std::string& method);
		void setPath(const std::string& path);
		void setVersion(const std::string& version);
		void setBody(const std::string& body);
		void setHeader(const std::string& key, const std::string& value);
		void setQuery(const std::string& key, const std::string& value);
		void setCookie(const std::string& key, const std::string& value);
	
		const std::string& getMethod() const;
		const std::string& getPath() const;
		const std::string& getVersion() const;
		const std::string& getBody() const;
		const std::string& getHeader(const std::string& key) const;
		const std::string& getQuery(const std::string& key) const;
		const std::string& getCookie(const std::string& key) const;
	
		bool hasHeader(const std::string& key) const;
		bool hasQuery(const std::string& key) const;
		bool hasCookie(const std::string& key) const;
	
		void removeHeader(const std::string& key);
		void removeQuery(const std::string& key);
		void removeCookie(const std::string& key);
	
		void clearHeaders();
		void clearQueries();
		void clearCookies();
	
		void forEachHeader(CallbackFunction callback) const;
    	void forEachQuery(CallbackFunction callback) const;
    	void forEachCookie(CallbackFunction callback) const;
	
	private:
		std::string m_method;
		std::string m_path;
		std::string m_version;
		std::string m_body;
		std::map<std::string, std::string> m_headers;
		std::map<std::string, std::string> m_queries;
		std::map<std::string, std::string> m_cookies;
};
