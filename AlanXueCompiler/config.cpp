#include "config.h"

#include <iostream>
#include <fstream>

using std::ifstream;
using std::cerr;
using std::stoi;

// ��̬��Ա���ⲿ���壬��д�����LNK200����

int Config::dict_start_index_;

void Config::init(string config_file_name) {
	ifstream config_file;
	try {
		config_file.open(config_file_name);
	}
	catch (ifstream::failure e) {
		cerr << "error: �޷����ļ���\"" << config_file_name << "\"\n";
	}
	string option_name;  // ѡ������
	string option_value;  // ѡ��ֵ
	while (config_file >> option_name >> option_value) {  // ÿ�ζ�ȡһ��ѡ�����ɺ�һ��ѡ��ֵ���м��ÿհ��ַ����ո��Ʊ�������з����ָ�
		if (option_name == "DICT_START_INDEX") {
			dict_start_index_ = stoi(option_value);
		}
	}
}

int Config::get_dict_start_index() {
	return dict_start_index_;
}