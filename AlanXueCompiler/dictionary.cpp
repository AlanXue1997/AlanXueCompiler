#include "dictionary.h"
#include "options.h"

#include <iostream>
#include <fstream>

using std::ifstream;
using std::cerr;

Dictionary::Dictionary(string dictionary_name) {
	ifstream dictionary_file(dictionary_name);
	if(dictionary_file){
		string name; // used for output/log
		string text; // used for writing code
		int code = DICT_START_CODE;  // an index
		while (dictionary_file >> name >> text) {
			text_to_code_[text] = code;
			name_to_code_[name] = code;
			code_to_name_[code] = name;
			text_set_.insert(text);
			code++;
		}
		initialized_correctly_ = true;
	}
	else{
		initialized_correctly_ = false;
		cerr << "error: 无法打开文件：\"" << dictionary_name << "\"\n";
	}
}

bool Dictionary::initialized_correctly() {
	return initialized_correctly_;
}

// TO-DO: 还有好多出错的情况没有考虑到

int Dictionary::text_to_code(string text) {
	if (text_to_code_.find(text) != text_to_code_.end()) {
		return text_to_code_[text];
	}
	else {
		return DICT_UNKNOW_CODE;
	}
}
int Dictionary::name_to_code(string name) {
	if (name_to_code_.find(name) != name_to_code_.end()) {
		return name_to_code_[name];
	}
	else {
		return DICT_UNKNOW_CODE;
	}
}
string Dictionary::code_to_name(int code) {
	if (code_to_name_.find(code) != code_to_name_.end()) {
		return code_to_name_[code];
	}
	else {
		return DICT_UNKNOW_NAME;
	}
}

const set<string> * Dictionary::get_text_set() {
	return &text_set_;
}
