#pragma once

#include <string>
#include <map>
#include <set>

using std::string;
using std::map;
using std::set;

// ������text��code��name֮�����ת��
// text�������е�д��
// code��int���͵ı��루��ţ�
// name��һ���������������
// ����
//		����break������
//		text��break
//		code��1
//		name��BREAK
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