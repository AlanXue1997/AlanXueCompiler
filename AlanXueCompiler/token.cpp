#include "token.h"
#include "options.h"

Token::Token() {
	code_ = TOKEN_IS_EMPTY;  // û�����࣬TOKENΪ��
}

Token::Token(int code) {
	code_ = code;
}

Token::Token(int code, std::string attribution) {
	code_ = code;
	attribution_ = attribution;
}

void Token::set_code(int code) {
	code_ = code;
}

int Token::get_code() {
	return code_;
}

bool Token::is_empty() {
	return code_ == TOKEN_IS_EMPTY;
}
