#pragma once
#include <iostream>
#include "ustack.h"
#include "Term.h"
#include <string>
#include <vector>


class Translator
{
private:
	std::string s;
	std::vector<Term*> lecksem;
	std::vector<Term*> postfix;
	double result = 0;
public:
	Translator() { s = '0'; };
	Translator(std::string temp){
		s = temp;
	}
	~Translator(){
	for (int i = 0; i < lecksem.size(); i++)
		delete lecksem[i];
	};

	void lexical_control();
	void bracket_control();
	void syntax_control();
	void postfix_translator();
	void calculator();

	double solve() { 
		void calculator();
		return result;
	};
};

void Translator::lexical_control() {
	
	size_t StringSize = s.size();
	for (int i = 0; (StringSize > 0) && (s[i] != '='); ) {
		if ((s[i] == '+') || (s[i] == '-') || (s[i] == '*') || (s[i] == '/')) {
			lecksem.push_back(new OPERATOR(s[i]));
			StringSize--;
			i++;
		}
		else if ((s[i] == '(') || (s[i] == ')')) {
			lecksem.push_back(new BRACKET(s[i]));
			StringSize--;
			i++;
		}
		else if (s[i] == ' ') {
			StringSize--;
			i++;
		}

		else if (s[i] >= '0' && s[i] <= '9') {
			size_t TempLenght = 0;
			double Temp = 0;
			Temp = std::stod(&s[i]);
			i++;
			while (s[i] >= '0' && s[i] <= '9') {
				Temp = 10 * Temp + std::stod(&s[i]);
				TempLenght++;
				StringSize--;
				i++;
			}
			lecksem.push_back(new NUMBER(Temp));
		}

		else 
			throw "Incorrect_symbol ";
	}
	

}	

void Translator::bracket_control(){
	void lexical_control();
Stack<char> S;
	for (size_t i = 0; i < s.size(); i++ )
	{
		std::cout << s[i] << " ";
		
		switch (s[i]) {

		case '(':
			S.push('(');
			break;   

		case ')':

			if (S.IsEmpty())
				throw "There is problem with )";
			else
				if (S.Top() != '(')
				{
					throw "There is problem with )";
					break;
				}
				else
					S.pop();
			break; 


		case '[':
			S.push('[');
			break; 

		case ']':

			if (S.IsEmpty())
				throw "There is problem with ]";
			else
				if (S.Top() != '[')
				{
					throw "There is problem with ]";
					break;
				}
				else
					S.pop();
			break; 

		case '{':
			S.push('{');
			break; 

		case '}':

			if (S.IsEmpty())
				throw "There is problem with }";
			else
				if (S.Top() != '{')
				{
					throw "There is problem with }";
					break;
				}
				else
					S.pop();
			break; 

		}

	}
	std::cout << std::endl;
	if (S.IsEmpty() != 1)
		throw "There is uneven number of op/cl brackets";
}


void Translator::syntax_control(){
	void bracket_control();
bool flag = true;
int t;

if ((lecksem.size() > 0) && (lecksem[0]->GetType() == TermType::Operator))
	if (((OPERATOR*)(lecksem[0]))->Priority() == 2)	
		flag = false;	
	else lecksem.insert(lecksem.begin(), new NUMBER(0));
	
for (size_t i = 0; (lecksem.size() > 0) && (i < s.size() - 1) && (flag == true); i++) {
	t = i + 1;
	std::cout << s[i] << " ";
	switch (lecksem[i]->GetType()) {
	case(TermType::Number):
		
		if (((lecksem[t])->GetType() == TermType::Number) || ((lecksem[t])->GetType() == TermType::OpBracket))
			throw "Syntax_Error";
		break;

	case(TermType::Operator):
		if (((lecksem[t])->GetType() == TermType::Operator) || ((lecksem[t])->GetType() == TermType::ClBracket))
			throw "Syntax_Error";
		break;

	case(TermType::OpBracket):
		if (((lecksem[t])->GetType() == TermType::ClBracket))
		{
			throw "Syntax_Error";
			break;
		}
		if (((lecksem[t]->GetType()) == TermType::Operator) && (((OPERATOR*)(lecksem[t]))->Priority() == 0))
		{
			lecksem.insert(lecksem.begin() + t, new NUMBER(0));
			i++;
			break;
		}
		else {	
			throw "Syntax_Error";
			break;
		}
		
		break;

	case(TermType::ClBracket):
		if ((lecksem[t]->GetType() == TermType::Number) || (lecksem[t]->GetType() == TermType::OpBracket))
			throw "Syntax_Error";
		break;

	}
}


if ((flag == true) && (lecksem.size() > 0) && (lecksem[lecksem.size()-1]->GetType() == TermType::Operator))
	throw "Syntax_Error";



/*
bool allright = true;

if (lecksem.size() > 0 && lecksem[0]->GetType() == TermType::Operator)		
	if (((OPERATOR*)(lecksem[0]))->Priority() == 1)			// *, /
	{
		throw "SYNTAX_ERROR";
	}
	else lecksem.insert(lecksem.begin(), new NUMBER(0));
												
for (int i = 0; lecksem.size() > 0 && i < lecksem.size() - 1 && allright == true; i++) {
	int t = i + 1;
	switch (lecksem[i]->GetType()) {
	case(TermType::Number):					
		if (lecksem[t]->GetType() == TermType::Number || lecksem[t]->GetType() == TermType::OpBracket)
		{
			throw "SYNTAX_ERROR";

		}
		break;
	case(TermType::Operator):
		if (lecksem[t]->GetType() == TermType::Operator || lecksem[t]->GetType() == TermType::ClBracket)
		{
			throw "SYNTAX_ERROR";
		}
		break;
	case(TermType::OpBracket):
		if (lecksem[t]->GetType() == TermType::ClBracket)		
		{
			throw "SYNTAX_ERROR";
			break;
		}
		if (lecksem[t]->GetType() == TermType::Operator)		
		{
			if (((OPERATOR*)(lecksem[t]))->Priority() == 1)
			{
				throw "SYNTAX_ERROR";
				break;
			}
			else {
				lecksem.insert(lecksem.begin() + t, new NUMBER(0));	
				i++;	
				
			}
		}
		break;
	case(TermType::ClBracket):
		if (lecksem[t]->GetType() == TermType::Number || lecksem[t]->GetType() == TermType::OpBracket)
		{
			throw "SYNTAX_ERROR";
		}
		break;
	default:
		throw "SYNTAX_ERROR";
	}
}


if (allright == true && lecksem.size() > 0 && lecksem[lecksem.size() - 1]->GetType() == TermType::Operator)	//Мы точно знаем, что там не открывающая скобка(из проверка на скобки). Осталось убедиться, что там не операция
{
	throw "SYNTAX_ERROR";
}

if (allright == false)
throw "SYNTAX_ERROR";

*/
}




void Translator::postfix_translator() {
	void syntax_control();
Term* Z;
int f;
Stack<Term*> S;
	for (size_t i = 0; i < lecksem.size(); i++){
		
		switch (lecksem[i]->GetType())
		{
		case (TermType::Number):
			postfix.push_back(lecksem[i]);
			break;

		case (TermType::OpBracket):
			S.push_back(lecksem[i]);
			break;

		case (TermType::ClBracket):
			f = 0;
			while (f == 0) {
				Z = S.Top();
				S.pop();
				if (Z->GetType() == TermType::OpBracket)
					f = 1;
				else
					postfix.push_back(Z);
			}
			break;

		case (TermType::Operator):
			while (!S.IsEmpty()) {
				Z = S.Top();
				S.pop();
				if (Z->GetType() == TermType::OpBracket)
				{
					S.push(Z);
					break;
				}
				else if (((OPERATOR*)(Z))->Priority() >= ((OPERATOR*)(lecksem[i]))->Priority()) {
					postfix.push_back(Z);
					break;
				}
				else {
					S.push(Z);
					break;
				}
			}
			S.push(lecksem[i]);
			break;


		}

	}

	while (!S.IsEmpty()) {
		postfix.push_back(S.Top());
		S.pop();
		
	}
	if (postfix.size() < 1)
		throw "Your string is too short for calculation";
}



void Translator::calculator(){
	void postfix_translator();
Stack<double> S;
for (int i = 0; i < postfix.size(); i++)
	switch (postfix[i]->GetType()) {
	case(Number):
		S.push(((NUMBER*)(postfix[i]))->GetValue());
		break;
	case(Operator):
		double op2 = S.Top();	
		S.pop();		
		double op1 = S.Top();
		S.pop();
		switch (((OPERATOR*)(postfix[i]))->GetOperator()) {
		case('+'):
			S.push(op1 + op2);	
			break;
		case('-'):
			S.push(op1 - op2);
			break;
		case('*'):
			S.push(op1 * op2);
			break;
		case('/'):
			if (op2 != 0.0)
				S.push(op1 / op2);
			else
				throw "dividing_by_zero";	
			break;
		}
	}
result = S.Top();
}