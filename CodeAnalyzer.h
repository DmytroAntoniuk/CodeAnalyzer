#pragma once

#include<string>
#include<filesystem>
#include<iostream>
#include<fstream>
#include <streambuf>
#include <vector>
#include <thread>
#include<mutex>

#include "LineCounter.h"

class CodeAnalyzer
{
public:
	CodeAnalyzer();
	~CodeAnalyzer();
	void AnalyzeCode(const std::string& currFile);
	void SaveTotalResult();
	void set_execution_time(const clock_t time);

private:
	void UpdateTotalLinesNumber(const LineCounter& line_counter);
	
	int m_total_blank_lines = 0;
	int m_total_comment_lines = 0;
	int m_total_code_lines = 0;
	int m_total_files = 0;
	clock_t m_execution_time = 0;
	std::ofstream m_fout;
	std::mutex m_mtx;
};

