#include "scanner.h"
#include "options.h"

#include <iostream>

#define INSIDE(OBJECT, SET) SET.find(OBJECT) != SET.end()

using std::cout;
using std::cerr;

const char kPlainChar[] = { '\n', '\t', ' ' };

Scanner::Scanner(string source_file_name, Dictionary * dictionary) {
	try {
		source_file_.open(source_file_name);
	}
	catch (ifstream::failure e) {
		cerr << "error: 无法打开文件：\"" << source_file_name << "\"\n";
	}
	dictionary_ = dictionary;
	for (char c = '0'; c <= '9'; ++c) {
		digits_.insert(c);
	}
	for (char c = 'a'; c <= 'z'; ++c) {
		letters_.insert(c);
	}
	for (char c = 'A'; c <= 'Z'; ++c) {
		letters_.insert(c);
	}
	letters_.insert('_');
	const set<string> * text_set = dictionary_->get_text_set();
	for (auto it = text_set->cbegin(); it != text_set->cend(); ++it) {
		if (INSIDE(it->at(0), letters_)) {
			words_.insert(*it);
		}
		else if (INSIDE(it->at(0), digits_)) {
			cerr << "error: numbers are not surppoted in dictionary\n";
		}
		else {
			symbols_.insert(*it);
			symbols_start_.insert(it->at(0));
		}
	}
	plain_char_.insert(kPlainChar, kPlainChar + sizeof(kPlainChar) / sizeof(char));
	go_back_ = false;
}

Token Scanner::NextToken() {
	if (!source_file_.is_open()) {
		return Token();  // 文件没有正确打开，输出空Token
	}
	string buffer = "";  // 缓冲
	char current_char;  // 当前指向的字符

	try {
		while (!source_file_.eof()) {
			if (go_back_) {
				go_back_ = false;
				current_char = backward_;
			}
			else {
				source_file_.get(current_char);
			}
			if (INSIDE(current_char, symbols_start_)) {	
				buffer = current_char;
				while (INSIDE(buffer, symbols_) && !source_file_.eof()) {
					source_file_.get(current_char);
					buffer += current_char;
				}
				if (INSIDE(buffer, symbols_)) {
					return Token(dictionary_->text_to_code(buffer));
				}
				else {
					go_back_ = true;
					backward_ = current_char;
					return Token(dictionary_->text_to_code(buffer.substr(0, buffer.length() - 1)));
				}
			}
			else if (INSIDE(current_char, digits_)) {
				buffer = current_char;
				source_file_.get(current_char);
				while (INSIDE(current_char, digits_)) {
					buffer += current_char;
					if(!source_file_.get(current_char)) break;
				}
				go_back_ = true;
				backward_ = current_char;
				return Token(DICT_INT_CODE, buffer);
			}
			else if (INSIDE(current_char, plain_char_)) {
				continue;
			}
			else if (INSIDE(current_char, letters_)){
				buffer = current_char;
				source_file_.get(current_char);
				while (INSIDE(current_char, letters_) || INSIDE(current_char, digits_)) {
					buffer += current_char;
					if(!source_file_.get(current_char)) break;
				}
				go_back_ = true;
				backward_ = current_char;
				if (INSIDE(buffer, words_)) {
					return Token(dictionary_->text_to_code(buffer));
				}
				else {
					return Token(DICT_ID_CODE, buffer);
				}
			}
			else {
				cerr << "error: Encountered Unexpected Char: " << current_char << "(" << (int)current_char << ")\n";
			}
		}
	}
	catch (ifstream::failure e) {
		cerr << "error: 读取文件时发生错误\n";
	}

	Token token;
	return token;
}
