#include "CodeAnalyzer.h"

CodeAnalyzer::CodeAnalyzer()
{
	m_fout.open("results.txt");
}

CodeAnalyzer::~CodeAnalyzer()
{
	m_fout.close();
}

void CodeAnalyzer::AnalyzeCode(const std::string& currFile)
{
	LineCounter line_counter(currFile);
	line_counter.StartCounting();

	std::lock_guard<std::mutex> lck(m_mtx);
	UpdateTotalLinesNumber(line_counter);
	line_counter.SaveResults(m_fout);
	line_counter.NullifyLinesValues();
}

void CodeAnalyzer::UpdateTotalLinesNumber(const LineCounter& line_counter)
{
	m_total_blank_lines += line_counter.get_blank_lines();
	m_total_code_lines += line_counter.get_code_lines();
	m_total_comment_lines += line_counter.get_comment_lines();
	++m_total_files;
}

void CodeAnalyzer::SaveTotalResult()
{
	m_fout << "Total number of analyzed files: " << m_total_files << "\n";
	m_fout << "Total blank lines number: " << m_total_blank_lines << "\n";
	m_fout << "Total comment lines number: " << m_total_comment_lines << "\n";
	m_fout << "Total code lines number: " << m_total_code_lines << "\n";
	m_fout << "Execution time: " << m_execution_time << " milliseconds \n";
}

void CodeAnalyzer::set_execution_time(const clock_t time)
{
	m_execution_time = time;
}
