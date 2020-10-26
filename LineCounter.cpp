#include "LineCounter.h"

LineCounter::LineCounter(const std::string& path):m_file_path(path)
{
}

void LineCounter::StartCounting()
{
	ParseFileData();
	CountBlankLines();
	CountCommentLines();
	CountCodeLines();
}

void LineCounter::CountBlankLines()
{
	char prevChar = '\n';
	for (size_t i = 0; i < m_file_data.size(); ++i)
	{
		if (m_file_data[i] == '\n' && prevChar == '\n')
			++m_blank_lines;
		prevChar = m_file_data[i];
	}
}

void LineCounter::CountCommentLines()
{
	bool in_line_comment = false;
	bool in_multiline_comment = false;
	char curr_char = m_file_data[0];
	char prev_char = m_file_data[0];
	int length = m_file_data.length();
	int curr_index = 0;
	while (curr_index < length - 1)
	{
		if (!in_line_comment && !in_multiline_comment && prev_char == '/' && curr_char == '/')
		{
			++m_comment_lines;
			in_line_comment = true;
		}
		else if (!in_line_comment && !in_multiline_comment && prev_char == '/' && curr_char == '*	')
		{
			++m_comment_lines;
			in_multiline_comment = true;
		}
		else if (in_line_comment && curr_char == '\n')
		{
			in_line_comment = false;
		}
		else if (in_multiline_comment && prev_char == '\n')
		{
			++m_comment_lines;
		}
		else if (in_multiline_comment && prev_char == '*' && curr_char == '/')
		{
			in_multiline_comment = false;
		}

		prev_char = m_file_data[curr_index];
		++curr_index;
		curr_char = m_file_data[curr_index];
	}
}

void LineCounter::CountCodeLines()
{
	int length = m_file_data.size();
	for (int i = 0; i < length; ++i)
	{
		if (m_file_data[i] == '\n')
			++m_code_lines;
	}
	if (m_file_data[length - 1] != '\n') ++m_code_lines;
}

void LineCounter::NullifyLinesValues()
{
	m_blank_lines = 0;
	m_comment_lines = 0;
	m_code_lines = 0;
}

void LineCounter::ParseFileData()
{
	std::ifstream file(m_file_path);
	m_file_data = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

void LineCounter::SaveResults(std::ofstream& fout)
{
	fout << m_file_path << "\n";
	fout << "Blank lines number: " << m_blank_lines << "\n";
	fout << "Comment lines number: " << m_comment_lines << "\n";
	fout << "Code lines number: " << m_code_lines << "\n";
}

const int& LineCounter::get_blank_lines() const
{
	return m_blank_lines;
}

const int& LineCounter::get_comment_lines() const
{
	return m_comment_lines;
}

const int& LineCounter::get_code_lines() const 
{
	return m_code_lines;
}
