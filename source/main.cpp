#include "headers/file_analyzer.h"
#include "headers/jpeg_generator.h"
#include <fstream>
#include <string>

int rectangle_language(std::ifstream& f) {
	try {
		Prog prog = analyze_file(f);
		std::cerr << "File is processed." << std::endl;
		jpeg_generator(prog.get_workarea());
		std::cerr << "Jpeg is exported." << std::endl;
	}
	catch (std::exception e) {
		std::cerr << e.what() << std::endl;
		return -1;
	}
	return 0;
}

int main(int argc, char **argv) {
	std::string f_str;
	if (argc == 1) {
		std::cerr << "not enough input agruments. enter file name: ";
		std::cin >> f_str;
	}
	else if (argc == 2) {
		f_str = argv[1];
	}
	else {
		std::cerr << "too many input arguments.";
		return -1;
	}
	std::ifstream f(f_str);
	int result = rectangle_language(f);
	system("pause");
	return result;
}