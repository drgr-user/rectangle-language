#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <regex>
#include <unordered_map>
#include <list>

#include "Rec.h"
#include "WorkArea.h"


class Prog {
private:

	WorkArea work_area;
	std::vector<Rec> rectangles;
	std::unordered_map<std::string, int> map_rec_index{};

	const std::unordered_map<std::string, int> map_p{
		{ "top", 1 },
		{ "left", 2 },
		{ "height", 3 },
		{ "width", 4 },
	};

	std::list<int> rec_seq;

public:
	WorkArea GetWorkarea() {
		return this->work_area;
	}

	bool MakeWorkarea(std::vector<std::string>  smt) {

		int height, width, color;
		std::stringstream(smt[1]) >> height;
		std::stringstream(smt[2]) >> width;
		std::stringstream(smt[3]) >> color;

		WorkArea* wa = new WorkArea(height, width, color);
		this->work_area = *wa;
		delete wa;

		return true;
	}

	void ColorWorkarea(Rec rec) {
		for (int top = rec.top; top <= rec.down; top++) {
			if (top < 0 || top > work_area.height - 1) {
				continue;
			}
			else {
				for (int left = rec.left; left <= rec.right; left++) {
					if (left < 0 || left > work_area.width - 1) {
						continue;
					}
					else {
						work_area.matrice[top][left] = rec.color;
					}
				}
			}
		}

		/*std::cout << "\nColored Workarea for " << rec.name << ": " << rec.color.color << std::endl;*/
	}

	bool UpdateWorkarea() {
		std::list<int> ::iterator it;
		int rectangle_index;
		Rec rectangle;

		for (int i = 0; i < this->work_area.height; i++) {
			for (int j = 0; j < this->work_area.width; j++) {
				this->work_area.matrice[i][j] = this->work_area.color;
			}
		}

		for (it = this->rec_seq.begin(); it != this->rec_seq.end(); ++it) {
			rectangle_index = *it;
			rectangle = this->rectangles[rectangle_index];
			ColorWorkarea(rectangle);
		}
		return true;
	}

	bool AddRectangle(std::vector<std::string>  smt) {

		int top, left, height, width, color;
		std::string name;
		std::stringstream(smt[1]) >> top;
		std::stringstream(smt[2]) >> left;
		std::stringstream(smt[3]) >> height;
		std::stringstream(smt[4]) >> width;
		std::stringstream(smt[5]) >> color;
		std::stringstream(smt[6]) >> name;

		Rec* rec = new Rec(top, left, height, width, color, name);
		this->rectangles.push_back(*rec);
		std::pair<std::string, int> new_rec_pair(name, this->rectangles.size() - 1);
		map_rec_index.insert(new_rec_pair);
		this->rec_seq.push_back(this->rectangles.size() - 1);
		delete rec;

		return true;
	}


	bool UpdateRectangle(std::string rec_name, std::string property_name, int new_value) {

		auto it = this->map_p.find(property_name);
		static const auto map_p_end = map_p.end();
		if (it == map_p_end) {
			return false;
		}
		int property_num = it->second;


		auto it_rec = this->map_rec_index.find(rec_name);
		static const auto map_rec_index_end = map_rec_index.end();
		if (it_rec == map_rec_index_end) {
			return false;
		}
		int rec_index = it_rec->second;


		switch (property_num) {
		case 1:
			this->rectangles[rec_index].top = new_value;
			break;
		case 2:
			this->rectangles[rec_index].left = new_value;
			break;
		case 3:
			if (new_value <= 0) {
				return false;
			}
			this->rectangles[rec_index].height = new_value;
			break;
		case 4:
			if (new_value <= 0) {
				return false;
			}
			this->rectangles[rec_index].width = new_value;
			break;
		default:
			break;
		}
		this->rec_seq.remove(rec_index);
		this->rec_seq.push_back(rec_index);
		return true;
	}

/*	void PrintInfo() {
		std::cout << "\n\t\tChecking Saved Info\n";

		for (int i = 0; i < this->rectangles.size(); i++) {
			std::cout << std::endl << this->rectangles[i].name
				<< "\ttop: " << this->rectangles[i].top << ", left:" << this->rectangles[i].left
				<< ", height: " << this->rectangles[i].height << ", width: "
				<< this->rectangles[i].width << ", color: " << this->rectangles[i].color.color << std::endl;
		}

		std::cout << std::endl << "Workarea\t" << "height: " << this->work_area.height
			<< ", width: " << this->work_area.width << ", color " << this->work_area.color.color << std::endl;

		std::list<int> ::iterator it;
		std::string seq_str = "Rectangles'sequence: ";
		for (it = this->rec_seq.begin(); it != this->rec_seq.end(); ++it) {
			seq_str += std::to_string(*it);
			seq_str += "\t";
		}
		seq_str += "\n";
		std::cout << seq_str;
	}*/

};
