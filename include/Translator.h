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

	double solve();
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
		else if ((s[i] >= '0' && s[i] <= '9')||(s[i] =='.')) {
			size_t Temp1Lenght;
			double Temp2Lenght = 0.1;
			int flag = 0;  //показатель, что началась дробная часть
			double Temp1 = 0.0;  //целая часть
			double Temp2 = 0.0;  //дробная часть
			if ((s[i] == '.') && (flag == 0))
				throw "lexical error - . without whole part";

			/*
			while ((s[i] != '.') && (flag == 0)) {
				Temp1 = 10.0*Temp1 + double(std::stod(&s[i]));
				StringSize--;
				i++;
			}

			if (s[i] == '.'){
				flag = 1;
				i++;
				}

			while (s[i] >= '0' && s[i] <= '9') {
				Temp2 += Temp2Lenght * double(std::stod(&s[i]));
				Temp2Lenght = Temp2Lenght * 0.1;
				StringSize--;
				i++;
			}

			if ((s[i] == '.')&&(flag == 1))
				throw "You cannot put 2 dots in a number";
			*/

			/*
			while (flag == 0)
				if (s[i] >= '0' && s[i] <= '9') {
					Temp1 = 10.0 * Temp1 + double(std::stod(&s[i]));
					StringSize--;
					i++;
				}
				else {
					flag = 1;
					i++;
					StringSize--;
				}
			if (flag == 1)
				while (s[i] >= '0' && s[i] <= '9') {
					Temp2 = Temp2 + Temp2Lenght * double(std::stod(&s[i]));
					Temp2Lenght = Temp2Lenght * 0.1;
					StringSize--;
					i++;
				}

			*/

			while (((s[i] >= '0' && s[i] <= '9') || (s[i] == '.')) && (flag == 0)) {
				if (s[i] >= '0' && s[i] <= '9') {
					
					Temp1 = std::stod(&s[i], &Temp1Lenght);
					StringSize -= Temp1Lenght;
					i += Temp1Lenght;
				}
				else if (s[i] == '.') {
					flag = 1;
					i++;
					StringSize--;
					break;
				}
			}
			while ((s[i] >= '0' && s[i] <= '9')&&(flag == 1)){
				Temp1Lenght = 0;
				Temp2 = std::stod(&s[i], &Temp1Lenght);
				for (int j=0; j< Temp1Lenght; j++)
					Temp2Lenght = Temp2Lenght * 0.1;
				Temp2 *= Temp1Lenght;
				StringSize-= Temp1Lenght;
				i += Temp1Lenght;
				}
			if ((s[i] == '.') && (flag == 1))
					throw "You cannot put 2 . in 1 number";
					
			
			Temp1 += Temp2;
			lecksem.push_back(new NUMBER(Temp1));
		}

		else 
			throw "Incorrect_symbol ";
	}
	

}	

void Translator::bracket_control(){
lexical_control();
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
bracket_control();
bool flag = true;
int t;

if ((lecksem.size() > 0) && (lecksem[0]->GetType() == TermType::Operator))
	if (((OPERATOR*)(lecksem[0]))->Priority() == 2)	 
		throw "Syntax_Error";
	else lecksem.insert(lecksem.begin(), new NUMBER(0));
	
for (size_t i = 0; (lecksem.size() > 0) && (i < lecksem.size() - 1) && (flag == true); i++) {
	t = i + 1;
	switch (lecksem[i]->GetType()) {
	case(TermType::Number):
		
		if ((lecksem[t])->GetType() == TermType::OpBracket)
			throw "Syntax_Error";
		break;

	case(TermType::Operator):
		if (((lecksem[t])->GetType() == TermType::Operator) || ((lecksem[t])->GetType() == TermType::ClBracket))
			throw "Syntax_Error";

	case(TermType::OpBracket):
		if (((lecksem[t])->GetType() == TermType::ClBracket))
			throw "Syntax_Error";
		if (((lecksem[t]->GetType()) == TermType::Operator) && (((OPERATOR*)(lecksem[t]))->Priority() == 1))
		{
			lecksem.insert(lecksem.begin() + t, new NUMBER(0));
			i++;
			break;
		}
		else break;

	case(TermType::ClBracket):
		if ((lecksem[t]->GetType() == TermType::Number) || (lecksem[t]->GetType() == TermType::OpBracket))
			throw "Syntax_Error";
	}
}
/*
if ((flag == true) && (lecksem.size() > 0) && (lecksem[lecksem.size() - 1]->GetType() == TermType::Operator))
	flag = false;
if (flag == false)
	throw "Syntax_Error";
*/
}




void Translator::postfix_translator() {
syntax_control();
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
postfix_translator();
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

double Translator::solve(){
	calculator();
	return result;
};