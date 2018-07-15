#include "gtest/gtest.h"
#include "../AlanXueCompiler/scanner.h"
#include "../AlanXueCompiler/options.h"

class ScannerTest : public ::testing::Test {
protected:
	Dictionary dictionary_;
	Scanner scanner = Scanner("source_code.txt", &dictionary_);
};

TEST_F(ScannerTest, NormalCase) {
	EXPECT_EQ(scanner.NextToken().get_code(), dictionary_.text_to_code("int"));
	EXPECT_EQ(scanner.NextToken().get_code(), DICT_ID_CODE);
	EXPECT_EQ(scanner.NextToken().get_code(), dictionary_.text_to_code("("));
	EXPECT_EQ(scanner.NextToken().get_code(), dictionary_.text_to_code(")"));
	EXPECT_EQ(scanner.NextToken().get_code(), dictionary_.text_to_code("{"));
	EXPECT_EQ(scanner.NextToken().get_code(), dictionary_.text_to_code("int"));
	EXPECT_EQ(scanner.NextToken().get_code(), DICT_ID_CODE);
	EXPECT_EQ(scanner.NextToken().get_code(), dictionary_.text_to_code(";"));
	EXPECT_EQ(scanner.NextToken().get_code(), dictionary_.text_to_code("for"));
	EXPECT_EQ(scanner.NextToken().get_code(), dictionary_.text_to_code("("));

	EXPECT_EQ(scanner.NextToken().get_code(), DICT_ID_CODE);
	EXPECT_EQ(scanner.NextToken().get_code(), dictionary_.text_to_code("="));
	EXPECT_EQ(scanner.NextToken().get_code(), DICT_INT_CODE);
	EXPECT_EQ(scanner.NextToken().get_code(), dictionary_.text_to_code(";"));

	EXPECT_EQ(scanner.NextToken().get_code(), DICT_ID_CODE);
	EXPECT_EQ(scanner.NextToken().get_code(), dictionary_.text_to_code("<"));
	EXPECT_EQ(scanner.NextToken().get_code(), DICT_INT_CODE);
	EXPECT_EQ(scanner.NextToken().get_code(), dictionary_.text_to_code(";"));

	EXPECT_EQ(scanner.NextToken().get_code(), DICT_ID_CODE);
	EXPECT_EQ(scanner.NextToken().get_code(), dictionary_.text_to_code("="));
	EXPECT_EQ(scanner.NextToken().get_code(), DICT_ID_CODE);
	EXPECT_EQ(scanner.NextToken().get_code(), dictionary_.text_to_code("+"));
	EXPECT_EQ(scanner.NextToken().get_code(), DICT_INT_CODE);

	EXPECT_EQ(scanner.NextToken().get_code(), dictionary_.text_to_code(")"));

	EXPECT_EQ(scanner.NextToken().get_code(), dictionary_.text_to_code("{"));
	EXPECT_EQ(scanner.NextToken().get_code(), DICT_ID_CODE);
	EXPECT_EQ(scanner.NextToken().get_code(), dictionary_.text_to_code("="));
	EXPECT_EQ(scanner.NextToken().get_code(), DICT_ID_CODE);
	EXPECT_EQ(scanner.NextToken().get_code(), dictionary_.text_to_code("+"));
	EXPECT_EQ(scanner.NextToken().get_code(), DICT_ID_CODE);
	EXPECT_EQ(scanner.NextToken().get_code(), dictionary_.text_to_code(";"));
	EXPECT_EQ(scanner.NextToken().get_code(), dictionary_.text_to_code("}"));

	EXPECT_EQ(scanner.NextToken().get_code(), dictionary_.text_to_code("return"));
	EXPECT_EQ(scanner.NextToken().get_code(), DICT_INT_CODE);
	EXPECT_EQ(scanner.NextToken().get_code(), dictionary_.text_to_code(";"));
	EXPECT_EQ(scanner.NextToken().get_code(), dictionary_.text_to_code("}"));
	EXPECT_EQ(scanner.NextToken().get_code(), TOKEN_IS_EMPTY);
}