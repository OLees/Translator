#pragma once
#include "ustack.h"
#include <iostream>


enum TermType { Number, OpBracket, ClBracket, Operator };


class Term {
public:
	virtual int  GetType() = 0;
	virtual void Print() = 0;
};


class NUMBER : public Term {
private:
	double value;
public:
	NUMBER(double temp){
		value = temp;
	}

	int GetType() {
		return TermType::Number;
	}

	void Print(){
		std::cout << value;
	}

	double GetValue(){
		return value;
	}
};


class BRACKET : public Term {
private:
	char c;
public:
	BRACKET(char temp){
		c = temp;
	}
	int GetType(){
		if (c == '(') 
			return TermType::OpBracket;
		else return TermType::ClBracket;
	}

	void Print() {
		std::cout << c;
	}
};

class OPERATOR : public Term {
private:
	char op;
public:
	OPERATOR(char temp) {
		op = temp;
	}

	int GetType() {
		return TermType::Operator;
	}
	void Print() {
		std::cout << op;
	}
	int Priority() {
		if ((op >= '0')&&(op <= '9'))
			return 0;
		else
		if ((op == '+') || (op == '-'))
			return 1;
		else
			if ((op == '*') || (op == '/'))
				return 2;
			else throw "Unknown operator";
	}

	char GetOperator(){
		return op;
	}
};
	
	
	