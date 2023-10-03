#pragma once
#include "main.hpp"

class ServConf;
class Location;
class Response {
	public:
		bool		_isDirHasIndexFiles;

	    // Constructors
	    Response(Request& req, std::vector<ServConf> config_file);
		// Response();

		// Check if the resource is found or not
		std::string isResourceFound(const std::string& fullPath);

		// Generate a response for a given resource
		std::string generateResponse(std::string fullPath, int flag, ServConf server);

		// Check if the directory has index files
		bool isDirHasIndexFiles(const std::string& directory, const std::string& indexFiles);

		// std::string	getContentTypeFromExtension(const std::string& filePath);
		// int buildResponse(Request& req, const Config_Loc& Config_file);
		// slowly slowly

		// Setter and Getter
		void set_response(std::string response);
		std::string get_response();

		void setPath(std::string path);
		std::string getPath();

		void settype(std::string type);
		std::string gettype();

    	void setHeader(const std::string& key, const std::string& value);
		const std::string& getHeader(const std::string& key) const ;

    	void setBody(const std::string& body);
    	const std::string& getBody() const;

    	void setStatus(int statusCode, const std::string& statusText);
    	int getStatusCode() const;

    	const std::string& getStatusText() const;

		// Get the complete HTTP response as a string
   		std::string toString();

		// Response main method (tkhari9a)
		int respond();

		// Get the content type from the extension
		std::string getContentTypeFromExtension(const std::string& filePath);
		std::string getContentType();

		bool isResourceDeletable(const std::string& resourcePath);
		bool deleteResource(const std::string& resourcePath);

		int MethodNotAllowed(const Location& loc);

		std::string generateUniqueFilename();
		bool saveDataToFile(const std::string& filePath, const std::string& data);
		bool fileExists(const std::string& f);
		std::string parseBoundary(std::string &body, std::string &boundary);
		void SaveDataToFile(const std::string& filePath, const std::string& data);
		void AppendDataToFile(const std::string& filePath, const std::string& data);
		int myFind(std::string src, std::string target);
		std::string decodePath(std::string path);
		std::string statusTextGen(int code);
		std::string generateErrorResponse(int code);

	private:
		Request		&_req;
		std::vector<ServConf>	_Config_file;

		std::string	contentType;
		std::string _type;
		// bool	_autoindex;
		std::string _response;
		std::string _path;
		std::string statusText;
		int statusCode;
		std::string body;
   		std::map<std::string, std::string> headers;
};
