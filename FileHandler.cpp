#include "FileHandler.h"

FileHandler::FileHandler(const std::string& path): m_root_directory(path)
{
}

void FileHandler::SearchForFiles()
{
	for (const auto& entry : std::filesystem::recursive_directory_iterator(m_root_directory))
	{
		if (!entry.is_directory())
		{
			if (std::find(m_file_extensions.begin(), m_file_extensions.end(), entry.path().extension()) != m_file_extensions.end())
			{
				m_files.push_back(entry.path().string());
			}
		}
	}
}