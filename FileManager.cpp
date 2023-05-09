

#include "FileManager.h"


std::regex FileManager::only_directory_path_regex = std::regex("^(?:(?:[a-zA-Z]:)?\\\\)?(?:[^\\\\\n]+\\\\)*[^\\\\\n]+\\\\$");
std::regex FileManager::full_path_with_file = std::regex("(^(?:[a-zA-Z]:)?\\\\?(?:\\\\.{1,2}\\\\)?(?:[^\\\\/:*?\"<>|\\r\\n]+\\\\)*[^\\\\/:*?\"<>|\\r\\n]+\\.[a-zA-Z0-9]{1,4}$)");


void FileManager::FilePathGuide()
{
	std::wcout
		<< "********CORRECT THE PATH********" << std::endl
		<< "\t======= File Path Guide =======" << std::endl
		<< L"C:\\\\exampleDirectory\\\\path.txt" << std::endl
		<< L".\\\\exampleDirectory\\\\path.txt" << std::endl
		<< L"\\\\exampleDirectory\\\\path.txt" << std::endl
		<< L"exampleDirectory\\\\path.txt" << std::endl
		<< L"path.json" << std::endl
		<< L"..\\\\parentDirectory\\\\path.txt" << std::endl << std::endl;

}

void FileManager::FolderPathGuide()
{
	std::wcout
		<< "********CORRECT THE PATH********" << std::endl
		<< "\t======= Folder Path Guide =======" << std::endl
		<< L"C:\\\\parentDirectory\\\\path\\\\" << std::endl
		<< L"\\\\parentDirectory\\\\path\\\\" << std::endl
		<< L"..\\\\parentDirectory\\\\path\\\\" << std::endl
		<< L"exampleDirectory\\\\path\\\\" << std::endl
		<< L"..\\\\path\\\\" << std::endl
		<< L"path\\\\" << std::endl << std::endl;

}

//create a file specify path with its name or just name if saving in same directory
//you should specify path like defined below
// C:\\exampleDirectory\\me.txt
bool FileManager::createFile(const std::string& filename)
{
	if (!std::regex_match(filename, full_path_with_file))
	{
		FileManager::FilePathGuide(); return false;
	}
	std::ofstream file(filename);
	if (file.is_open()) {
		file.close();
		return true;
	}
	return false;
}

//delete a file provide its complete path or just name if in the same directory
//you should specify path like defined below
// C:\\exampleDirectory\\me.txt
bool FileManager::deleteFile(const std::string& filename)
{
	if (!std::regex_match(filename, full_path_with_file))
	{
		FileManager::FilePathGuide(); return false;
	}
	if (std::remove(filename.c_str()) == 0) {
		return true;
	}
	return false;
}

//check whether a file exists on a specific location or not
//you should specify path like defined below
// C:\\exampleDirectory\\me.txt
bool FileManager::fileExists(const std::string& filename)
{
	if (!std::regex_match(filename, full_path_with_file))
	{
		FileManager::FilePathGuide(); return false;
	}
	std::ifstream file(filename);
	if (file.good()) {
		file.close();
		return true;
	}
	return false;
}

//read contents of the file as string
//will return a vector<string> variable
//you should specify path like defined below
// C:\\exampleDirectory\\me.txt
std::vector<std::string> FileManager::readLines(const std::string& filename)
{
	if (!std::regex_match(filename, full_path_with_file))
	{
		FileManager::FilePathGuide(); return std::vector<std::string>();
	}
	std::vector<std::string> lines;
	std::ifstream file(filename);
	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			lines.push_back(line);
		}
		file.close();
	}
	return lines;
}

//write content to a file provide as vector<string>
//you should specify path like defined below
// C:\\exampleDirectory\\me.txt
bool FileManager::writeLines(const std::string& filename, const std::vector<std::string>& lines)
{
	if (!std::regex_match(filename, full_path_with_file))
	{
		FileManager::FilePathGuide(); return false;
	}
	std::ofstream file(filename);
	if (file.is_open()) {
		for (const auto& line : lines) {
			file << line << '\n';
		}
		file.close();
		return true;
	}
	return false;
}

//to copy a file to specific destination
//you should specify path like defined below
// C:\\exampleDirectory\\me.txt
bool FileManager::copyFile(const std::string& filename, const std::string& directorypath)
{
	if (std::regex_match(filename, full_path_with_file) == false)
	{
		FileManager::FilePathGuide(); return false;
	}
	if (std::regex_match(directorypath, only_directory_path_regex) == false)
	{
		FileManager::FolderPathGuide(); return false;
	}
	std::string command = "copy " + std::string(filename) + " " + std::string(directorypath);
	if (FileManager::fileExists(filename))
	{
		if (std::system(command.c_str()) == 0)
			return true;
		else
			return false;
	}
	return false;
}

//a utility function 
std::string FileManager::getLastDirectory(const std::string& path)
{
	std::stringstream ss(path);
	std::vector<std::string> directories;

	std::string directory;
	while (std::getline(ss, directory, '\\')) {
		directories.push_back(directory);
	}
	// Return the last directory name in the path
	return directories.back();
}

//copy a directory to a directory
//you should specify path like defined below
// C:\\exampleDirectory\\    ...
bool FileManager::copyDirectory(const std::string& source_directory_path, const std::string& destination_directory_path)
{
	if (!std::regex_match(source_directory_path, only_directory_path_regex) && !std::regex_match(destination_directory_path, only_directory_path_regex))
	{
		FileManager::FolderPathGuide(); return false;
	}

	std::string directory_name = getLastDirectory(source_directory_path);

	//create directory name in the destination path first
	std::string creatingDestination = destination_directory_path + directory_name + "\\";
	if (FileManager::createDirectory(creatingDestination)) //creating destination point as folder then below we will copy the contents
	{

		std::string command = "Xcopy " + source_directory_path + " " + creatingDestination + " /E/H/C/I";

		if (std::system(command.c_str()) == 0)
		{
			return true;
		}
		return false;
	}

	return false;
}

//create a directory
//you should specify path like defined below
// C:\\exampleDirectory\\    ...
bool FileManager::createDirectory(const std::string& directorypath)
{
	std::cout << directorypath << std::endl;
	if (!std::regex_match(directorypath, only_directory_path_regex))
	{
		FileManager::FolderPathGuide(); return false;
	}

	std::string command = "mkdir " + std::string(directorypath);
	if (std::system(command.c_str()) == 0)
	{
		return true;
	}
	return false;
}

//create a directory with all of its content
//you should specify path like defined below
// C:\\exampleDirectory\\     ...
bool FileManager::deleteDirectory(const std::string& directorypath)
{
	std::cout << directorypath << std::endl;
	if (!std::regex_match(directorypath, only_directory_path_regex))
	{
		FileManager::FolderPathGuide(); return false;
	}

	std::string command = "rmdir /s /q " + std::string(directorypath);
	if (std::system(command.c_str()) == 0)
	{
		return true;
	}
	return false;
}


