#include "headers/file_analyzer.h"
#include<fstream>

//Semantic Analysis
bool color_range_is_valid(std::string str_val) {
	int value;
	std::stringstream(str_val) >> value;
	if (0 <= value && value <= 255) {
		return true;
	}
	else {
		return false;
	}
}

bool is_positive(std::string str_val) {
	int value;
	std::stringstream(str_val) >> value;
	if (value > 0) {
		return true;
	}
	else {
		return false;
	}
}

bool is_comment(std::string input_line) {
	if (input_line.size() >= 2 && input_line[0] == '/' && input_line[1] == '/') {
		return true;
	}
	else {
		return false;
	}
}

bool check_line(std::string input_line, std::string reg_expr) {
	std::regex str_expr(reg_expr);
	if (std::regex_match(input_line, str_expr)) {
		return true;
	}
	else {
		return false;
	}
}

//Lexical Analysis
std::vector<std::string> process_line(std::string input_line, std::string reg_expr, std::string str) {
	std::regex str_expr(reg_expr);
	std::smatch smt;
	std::vector<std::string> parts;
	std::regex_match(input_line, smt, str_expr);
	for (int i = 0; i< smt.size(); i++) {
		parts.push_back(smt[i]);
	}
	return parts;
}

//Syntax and Semantic Analysis
Prog analyze_file(std::ifstream& recfile) {

	bool init_stage = false;
	bool work_area_set = false;
	bool move_stage = false;

	Prog app;

	const std::string workarea_reg = "workarea[\\s]*=[\\s]*\\{[\\s]*([-]*[0-9]+|[+]*[0-9]+)[\\s]*,[\\s]*([-]*[0-9]+|[+]*[0-9]+)[\\s]*,[\\s]*([+]*[0-9]+)[\\s]*\\}[\\s]*";
	const std::string rec_reg = "rectangle[\\s]*=[\\s]*\\{[\\s]*([-]*[0-9]+|[+]*[0-9]+)[\\s]*,[\\s]*([-]*[0-9]+|[+]*[0-9]+)[\\s]*,[\\s]*([-]*[0-9]+|[+]*[0-9]+)[\\s]*,[\\s]*([-]*[0-9]+|[+]*[0-9]+)[\\s]*,[\\s]*([+]*[0-9]+)[\\s]*,[\\s]*(\\w+)[\\s]*\\}[\\s]*";
	const std::string move_reg = "(\\w+)\\.(\\w+)[\\s]*=[\\s]*([-]*[0-9]+|[+]*[0-9]+)";

	std::string error_msg = "Error at line ";

	std::string input_text;
	int line_counter = 0;
	int file_counter = 0;

	while (std::getline(recfile, input_text)) {
		line_counter += 1;

		//looking for #init
		if (!init_stage) {
			if (input_text == "#init") {
				/*std::cout << "Initializing\n";*/
				init_stage = true;
			}
			else if (!is_comment(input_text)) {
				error_msg += std::to_string(line_counter);
				throw std::invalid_argument(error_msg);
			}
		}

		//looking for workarea, rectangle or #move
		else if (init_stage && !move_stage) {

			if (input_text == "#move") {
				/*std::cout << "\nMoving stage is started.\n";*/
				move_stage = true;
				app.update_workarea();
			}
			else {
				if (check_line(input_text, workarea_reg)) {
					std::vector<std::string> smt = process_line(input_text, workarea_reg, "workarea");
					if (!is_positive(smt[1]) || !is_positive(smt[2]) || !color_range_is_valid(smt[3])) {
						error_msg += std::to_string(line_counter);
						throw std::invalid_argument(error_msg);
					}
					bool make_wa_result = app.make_workarea(smt);
					if (!make_wa_result) {
						error_msg += std::to_string(line_counter);
						throw std::invalid_argument(error_msg);
					}
				}
				else if (check_line(input_text, rec_reg)) {
					std::vector<std::string> smt = process_line(input_text, rec_reg, "rec");
					if (!is_positive(smt[3]) || !is_positive(smt[4]) || !color_range_is_valid(smt[5])) {
						error_msg += std::to_string(line_counter);
						throw std::invalid_argument(error_msg);;
					}
					bool add_rec_result = app.add_rec(smt);
					if (!add_rec_result) {
						error_msg += std::to_string(line_counter);
						throw std::invalid_argument(error_msg);
					}
				}
				else if (is_comment(input_text)) {
					/*std::cout << "\nComment.\n";*/
				}
				else {
					error_msg += std::to_string(line_counter);
					throw std::invalid_argument(error_msg);
				}
			}
		}

		//looking for moves
		else if (move_stage) {
			if (check_line(input_text, move_reg)) {
				std::vector<std::string> smt = process_line(input_text, move_reg, "move");
				int rec_new_value;
				std::stringstream(smt[3]) >> rec_new_value;
				bool update_result = app.update_rec(smt[1], smt[2], rec_new_value);
				if (!update_result) {
					error_msg += std::to_string(line_counter);
					throw std::invalid_argument(error_msg);
				}
				app.update_workarea();
			}
			else if (is_comment(input_text)) {
				/*std::cout << "\nComment.\n";*/
			}
			else {
				error_msg += std::to_string(line_counter);
				throw std::invalid_argument(error_msg);
			}

		}
	}

	return app;
}