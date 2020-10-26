#include<iostream>
#include <ctime>

#include "CodeAnalyzer.h"
#include "FileHandler.h"

int main()
{
	clock_t execution_start = clock();

	std::string path = "D:\\SSITA";
	FileHandler file_handler(path);
	file_handler.SearchForFiles();

	CodeAnalyzer code_analyzer;
	std::vector<std::thread> threads;
	for (size_t i = 0; i < file_handler.m_files.size(); ++i)
	{
		threads.emplace_back(std::thread(&CodeAnalyzer::AnalyzeCode, std::ref(code_analyzer), file_handler.m_files[i]));
	}
	for (std::thread& thread : threads)
	{
		if (thread.joinable())	
			thread.join();
	}

	clock_t execution_finish = clock();
	code_analyzer.set_execution_time(execution_finish - execution_start);
	code_analyzer.SaveTotalResult();
}