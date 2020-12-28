#include "Translator.h"
#include <gtest.h>

TEST(TTranslator, can_create_empty_class) {
	std::string str;
	ASSERT_NO_THROW(Translator a(str));
};

TEST(TTranslator, can_create_not_empty_class) {
	std::string str;
	str = "1+2";
	ASSERT_NO_THROW(Translator a(str));
};

TEST(TTranslator, can_check_for_right_bracketing) {
	std::string str;
	str = "(1+2)";
	Translator A(str);
	ASSERT_NO_THROW(A.bracket_control());
};

TEST(TTranslator, can_check_for_wrong_bracketing) {
	std::string str;
	str = "(1+2)}";
	Translator A(str);
	ASSERT_ANY_THROW(A.bracket_control());
};

TEST(TTranslator, can_check_for_lexical) {
	std::string str;
	str = "1";
	Translator A(str);
	ASSERT_NO_THROW(A.lexical_control());
	/*try
	{
		A.lexical_control();
	}
	catch (const char* message) {
		std::cout << message << std::endl;
	}*/
};

TEST(TTranslator, can_work_with_decimal_numbers) {
	std::string str;
	str = "(1.2+2)";
	Translator A(str);
	ASSERT_NO_THROW(A.lexical_control());

};

TEST(TTranslator, can_check_for_syntax) {
	std::string str;
	str = "++(11 +2)++";
	Translator A(str);
	ASSERT_ANY_THROW(A.syntax_control());
};

TEST(TTranslator, can_solve_not_easy_expressions) {
	std::string str("1.1*10");
	Translator A(str);
	double temp = A.solve();
	EXPECT_EQ(11, temp);
};


TEST(TTranslator, can_solve_easy_expressions) {
	std::string str("1+2");
	Translator A(str);
	/*
	try
	{
		A.solve();
	}
	catch (const char* message) {
		std::cout << message << std::endl;
	}*/
	double temp = A.solve();
	EXPECT_EQ(3, temp);
};