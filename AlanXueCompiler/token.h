#pragma once

#include <string>

class Token {
private:
	int code_;  // 种别码
	std::string attribution_;  // 属性值
public:
	Token();
	Token(int code);
	Token(int code, std::string attribution);
	void set_code(int code);
	int get_code();
	bool is_empty();
};