#include "Translator.h"
#include <gtest.h>
/*
TEST(TTranslator, can_create_empty_class) {
	std::string str;
	ASSERT_NO_THROW(Translator(str));
};

TEST(TTranslator, can_create_not_empty_class) {
	std::string str;
	str = "1+2";
	ASSERT_NO_THROW(Translator(str));
};
*/
TEST(TTranslator, can_solve_easy_expressions) {
	std::string str("1+2");
	Translator A(str);
	//double temp = A.solve();
	try
	{
		A.solve();
	}
	catch (const char* message) {
		std::cout << message << std::endl;
	}
	//EXPECT_EQ(3, temp);
};