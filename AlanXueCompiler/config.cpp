#include "config.h"

#include <iostream>
#include <fstream>

using std::ifstream;
using std::cerr;
using std::stoi;

// 静态成员的外部定义，不写会出现LNK200错误

int Config::dict_start_index_;

void Config::init(string config_file_name) {
	ifstream config_file;
	try {
		config_file.open(config_file_name);
	}
	catch (ifstream::failure e) {
		cerr << "error: 无法打开文件：\"" << config_file_name << "\"\n";
	}
	string option_name;  // 选项名称
	string option_value;  // 选项值
	while (config_file >> option_name >> option_value) {  // 每次读取一个选项名成和一个选项值，中间用空白字符（空格、制表符、换行符）分割
		if (option_name == "DICT_START_INDEX") {
			dict_start_index_ = stoi(option_value);
		}
	}
}

int Config::get_dict_start_index() {
	return dict_start_index_;
}