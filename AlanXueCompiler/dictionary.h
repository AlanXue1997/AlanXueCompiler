#pragma once

#include <string>
#include <map>
#include <set>

using std::string;
using std::map;
using std::set;

// 用来在text、code、name之间进行转换
// text：代码中的写法
// code：int类型的编码（序号）
// name：一个用于输出的名字
// 例：
//		对于break保留字
//		text：break
//		code：1
//		name：BREAK
class Dictionary {
private:
	map<string, int> text_to_code_;
	map<string, int> name_to_code_;
	map<int, string> code_to_name_;
	set<string> text_set_;
	bool initialized_correctly_;
public:
	Dictionary(string dictionary_name = "dictionary.txt");
	bool initialized_correctly();
	int text_to_code(string text);
	int name_to_code(string name);
	string code_to_name(int code);
	const set<string> * get_text_set();
};