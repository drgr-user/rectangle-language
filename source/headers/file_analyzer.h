#ifndef FILE_ANALAYZER_H
#define FILE_ANALAYZER_H

#include "Prog.h"

bool is_comment(std::string input_line);
bool check_line(std::string input_line, std::string reg_expr);
std::vector<std::string> process_line(std::string input_line, std::string reg_expr, std::string str);
Prog analyze_file(std::ifstream& f);

#endif