#pragma once

#include <filesystem>
#include <string>
#include <vector>

class FileHandler
{
public:
	std::vector<std::string> m_files;
	std::string m_root_directory;
	const std::vector<std::string> m_file_extensions { ".cpp", ".c", ".h", ".hpp" };
	FileHandler(const std::string& path);
	void SearchForFiles();

};

