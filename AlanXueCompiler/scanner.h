#pragma once

#include "token.h"
#include "dictionary.h"

#include <string>
#include <fstream>
#include <set>

using std::string;
using std::ifstream;
using std::set;

class Scanner {
private:
    ifstream source_file_;
	Dictionary * dictionary_;
	set<string> symbols_;
	set<string> words_;
	set<char> symbols_start_;
	set<char> plain_char_;
	set<char> digits_;
	set<char> letters_;
	char backward_;
	bool go_back_;
public:
    Scanner(string source_file_name, Dictionary * dictionary);
    Token NextToken();
};