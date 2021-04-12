#ifndef FILE_ANALAYSER_H
#define FILE_ANALAYSER_H

#include "Prog.h"

bool IsComment(std::string input_line);
bool CheckLine(std::string input_line, std::string reg_expr);
std::vector<std::string> ProcessLine(std::string input_line, std::string reg_expr, std::string str);
Prog AnalyseFile(std::ifstream& f);

#endif