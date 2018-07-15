#include "gtest/gtest.h"
#include "../AlanXueCompiler/dictionary.h"
#include "../AlanXueCompiler/options.h"

#include <string>
#include <fstream>

using std::string;
using std::ifstream;

class DictionaryTest : public ::testing::Test {
protected:
	Dictionary dict_default_;
	Dictionary dict_given_ = Dictionary("another_dictionary.txt");
	Dictionary dict_nonexist_ = Dictionary("_nonexist_dictionary_.txt");;
};

TEST_F(DictionaryTest, InitFiles) {
	EXPECT_EQ(dict_default_.initialized_correctly(), true) << "initialize default file(\"dictionary.txt\") failed, make sure the file exists in WORKSPACE";
	EXPECT_EQ(dict_given_.initialized_correctly(), true) << "initialize given file \"another_dictionary.txt\" failed, make sure the file exists in WORKSPACE";
	EXPECT_EQ(dict_nonexist_.initialized_correctly(), false) << "initialize nonexist file \"_nonexist_dictionary_.txt\" succeed, make sure the file doesn't exist in WORKSPACE";
}

TEST_F(DictionaryTest, HandleDict) {
	string text;
	string name;
	ifstream dictionary("dictionary.txt");
	int count = 0;
	while (dictionary >> name >> text) {
		count++;
	}
	dictionary.close();
	dictionary.open("dictionary.txt");
	while (dictionary >> name >> text) {
		int code = dict_default_.name_to_code(name);
		EXPECT_GE(dict_default_.name_to_code(name), DICT_START_CODE) << "'" << name << "'�� code(" << code << ") ��Ҫ���ڵ��� DICT_START_CODE(" << DICT_START_CODE << ")";
		EXPECT_LT(dict_default_.name_to_code(name), DICT_START_CODE+count) << "'" << name << "'�� code(" << code << ") ��ҪС�� DICT_START_CODE + �ֵ��йؼ��ֵĸ���(" << (DICT_START_CODE + 2) << ")";
		EXPECT_EQ(dict_default_.code_to_name(code), name) << "[" << name << ", " << text << "] Dictionary::code_to_name(" << code << ")����\"" << dict_default_.code_to_name(code) << "\"������Dictionary::name_to_code(\"" << name << "\")����" << code << "�����˲�һ��";
		EXPECT_EQ(dict_default_.text_to_code(text), code) << "[" << name << ", " << text << "] Dictionary::text_to_code(\"" << text << "\")����" << dict_default_.code_to_name(code) << "������Dictionary::name_to_code(\"" << name << "\")����" << code << "�����˲�һ��";
	}
}

TEST_F(DictionaryTest, HandleUnknown) {
	EXPECT_EQ(dict_default_.name_to_code("unknow_name"), DICT_UNKNOW_CODE);
	EXPECT_EQ(dict_default_.text_to_code("unknow_text"), DICT_UNKNOW_CODE);
	EXPECT_EQ(dict_default_.code_to_name(0x7FFFFFFF), "");
}