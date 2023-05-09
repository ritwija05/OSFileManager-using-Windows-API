#pragma once
#ifndef FILE_MANAGER_H 
#define FILE_MANAGER_H 

#include <iostream>
#include<conio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <regex>
#include <windows.h>


class FileManager {
public:
	static std::regex only_directory_path_regex;
	static std::regex full_path_with_file;
public:
	static void FilePathGuide();

	static void FolderPathGuide();

	static std::string getLastDirectory(const std::string& path);

	static bool createFile(const std::string& filename);

	static bool deleteFile(const std::string& filename);

	static bool copyFile(const std::string& filename, const std::string& directorypath);

	static bool fileExists(const std::string& filename);

	static std::vector<std::string> readLines(const std::string& filename);

	static bool writeLines(const std::string& filename, const std::vector<std::string>& lines);

	static bool createDirectory(const std::string& directorypath);

	static bool deleteDirectory(const std::string& directorypath);

	static bool copyDirectory(const std::string& source_directory_path, const std::string& destination_directory_path);
};



#endif 