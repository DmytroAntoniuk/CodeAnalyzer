#pragma once
#include <string>
#include <fstream>
#include <iostream>

class LineCounter
{
public:
	LineCounter(const std::string& path);
	void StartCounting();
	void CountBlankLines();
	void CountCommentLines();
	void CountCodeLines();
	void NullifyLinesValues();
	void ParseFileData();
	void SaveResults(std::ofstream& fout);
	const int& get_blank_lines() const;
	const int& get_comment_lines() const;
	const int& get_code_lines() const;

private:
	int m_blank_lines = 0;
	int m_comment_lines = 0;
	int m_code_lines = 0;
	std::string m_file_data = "";
	std::string m_file_path;

};

