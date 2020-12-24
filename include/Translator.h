#pragma once
#include <iostream>
#include "ustack.h"
#include "Term.h"
#include <string>


class Translator
{
private:
	std::string s;
	Vector<Term*> lecksem;
	Stack<Term*> postfix;

	void lexical_control();	
	void bracket_control();	
	void syntax_control();	
	void postfix_translator();	
	void calculator();

	double result = 0;
public:
	Translator() { s = '0'; };
	Translator(std::string temp){
		s = temp;
	}
	~Translator(){
	for (int i = 0; i < lecksem.GetSize(); i++)
		delete lecksem[i];
	};
	double solve() { 
		void lexical_control();
		void bracket_control();
		void syntax_control();
		void postfix_translator();
		void calculator();
		return result;
	};
};

void Translator::lexical_control() {
	size_t StringSize = s.size();
	for(int i = 0; (StringSize > 0)&&(s[i] != '='); i++) {
		if((s[i] == '+') || (s[i] == '-') || (s[i] == '*') || (s[i] == '/')){
			lecksem.push_back(new OPERATOR(s[i]));
			StringSize--;
			i++;
		}
		else if ((s[i] == '(') || (s[i] == ')')){
			lecksem.push_back(new BRACKET(s[i]));
			StringSize--;
			i++;
		}
		else if (s[i] >= '0' && s[i] <= '9') {		 
			size_t TempLenght;						 
			double Temp;							 
			Temp = std::stod(s, &TempLenght);
			lecksem.push_back(new NUMBER(Temp));
			StringSize -= TempLenght;
			i += TempLenght;
		}
		else if (s[i] == ' '){
			StringSize--;
			i++;
		}
		else {
			std::cout << "Incorrect_symbol in possition: " << s.size() - StringSize + 1 << std::endl;
			throw;
		}
	}
}	

void Translator::bracket_control(){
Stack<char> S;
	for (int i = 0; i < s.length(); i++ )
	{
		std::cout << s[i] << " ";
		
		switch (s[i]) {

		case '(':
			S.push(0);
			break;   

		case ')':

			if (S.IsEmpty())
				throw "There is problem with )";
			else
				if (S.Top() != 0)
				{
					throw "There is problem with )";
					break;
				}
				else
					S.pop();
			break; 


		case '[':
			S.push(1);
			break; 

		case ']':

			if (S.IsEmpty())
				throw "There is problem with ]";
			else
				if (S.Top() != 1)
				{
					throw "There is problem with ]";
					break;
				}
				else
					S.pop();
			break; 

		case '{':
			S.push(2);
			break; 

		case '}':

			if (S.IsEmpty())
				throw "There is problem with }";
			else
				if (S.Top() != 2)
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
	bool flag = true;
int t;
/*
if ((lecksem.GetSize() > 0) && (lecksem[0]->GetType() == TermType::Operator))
	if (((OPERATOR*)(lecksem[0]))->Priority() == 1)	
		flag = false;	
	else lecksem.push_back(new NUMBER(0));
	*/

for (int i = 0; lecksem.GetSize() > 0 && i < lecksem.GetSize() - 1 && flag == true; i++) {
	t = 0;
	switch (lecksem[i]->GetType()) {
	case(TermType::Number):
		t = i + 1;
		if (((lecksem[t])->GetType() == TermType::Number) || ((lecksem[t])->GetType() == TermType::OpBracket))
			flag = false;
		break;
	case(TermType::Operator):
		t = i + 1;
		if (((lecksem[t])->GetType() == TermType::Operator) || ((lecksem[t])->GetType() == TermType::ClBracket))
			flag = false;
		break;
	case(TermType::OpBracket):
		t = i + 1;
		if ((lecksem[t])->GetType() == TermType::ClBracket)
		{
			flag = false;
			break;
		}
		if ((lecksem[t]->GetType()) == TermType::Operator)
		{
			if (((OPERATOR*)(lecksem[t]))->Priority() == 1)
			{
				flag = false;
				break;
			}
			else {
				lecksem.push_back(new NUMBER(0));
				i++;
			}
		}
		break;
	case(TermType::ClBracket):
		t = i + 1;
		if ((lecksem[t]->GetType() == TermType::Number) || (lecksem[t]->GetType() == TermType::OpBracket))
			flag = false;
		break;

	}
}
if (lecksem.GetSize() == 0)
	throw "Entered string is empty";

	if ((flag == true) && (lecksem.GetSize() > 0) && (lecksem[lecksem.GetSize() - 1]->GetType() == TermType::Operator))
		flag = false;
	if (flag == false)
		throw "Syntax_Error";
}


void Translator::postfix_translator() {
Term* Z;
int f;
Stack<Term*> S;
	for (int i = 0; i < lecksem.GetSize(); i++){
		
		switch (lecksem[i]->GetType())
		{
		case (TermType::Number):  
		
			postfix.push(lecksem[i]);
			break;
		case (TermType::OpBracket): 
				//S.push(lecksem[i]);
				break;

		case (TermType::ClBracket): 
			if (S.IsEmpty() != 1) {
				f = 0;
				while (!f) {
					Z = S.Top();
					S.pop();
					if (((BRACKET*)(Z))->GetType() == TermType::OpBracket)
						f = 1;
					else {
						postfix.push(Z);
					}
				}
			}
			break;

		case (TermType::Operator):   
			while (S.IsEmpty() != 1) {
				Z = S.Top();
				S.pop();
				if (((OPERATOR*)(Z))->Priority() >= ((OPERATOR*)(lecksem[i]))->Priority()) {
					postfix.push(Z);
					
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

	while (S.IsEmpty() != 1) {
		postfix.push(S.Top());
		S.pop();
		
	}
}



void Translator::calculator(){
Stack<double> S;
for (int i = 0; i < postfix.GetSize(); i++)
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