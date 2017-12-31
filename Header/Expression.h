#pragma once
#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <iostream>
#include <string>
#include "Query.h"

class Expression
{
public:
    Expression(const std::string &word) : _is_word(true), _is_single_opr(false), _word(word), _opr(0), _left(0), _right(0) {}
    Expression(char opr, Expression *left, Expression *right) : _is_word(false), _is_single_opr(false), _word(), _opr(opr), _left(left), _right(right) {}
    Expression(char opr, Expression *expr) : _is_word(false), _is_single_opr(true), _word(), _opr(opr), _left(expr), _right(0) {}
	~Expression()
	{
		if (_left)delete _left;
		if (_right)delete _right;
	}

	void debug_expression()
	{
		if (_is_word)
		{
			std::cout << _word;
		}
		else if (_is_single_opr)
		{
			std::cout << _opr;
			_left->debug_expression();
		}
		else
		{
			std::cout << "(" << _opr << " ";
			_left->debug_expression();
			std::cout << " ";
			_right->debug_expression();
			std::cout << ")";
		}
	}

	std::string test_expression()
	{
		std::string ret;
		if (_is_word)
		{
			ret.append(_word);
		}
		else if (_is_single_opr)
		{
			ret.push_back(_opr);
			ret.append(_left->test_expression());
		}
		else
		{
			ret.push_back('(');
			ret.push_back(_opr);
			ret.push_back(' ');
			ret.append(_left->test_expression());
			ret.push_back(' ');
			ret.append(_right->test_expression());
			ret.push_back(')');
		}

		return ret;
	}

	Query test_eval()
	{
		if (_is_word)
		{
			return Query(_word);
		}
		else if (_is_single_opr)
		{
			return ~Query(_left->test_eval());
		}
		else
		{
			if (_opr == '&')
				return _left->test_eval() & _right->test_eval();
			else
				return _left->test_eval() | _right->test_eval();
		}
	}
private:
    bool _is_word;
    bool _is_single_opr;
    std::string _word;
    char _opr;
    Expression *_left;
    Expression *_right;
};

class ExprParseException
{
public:
	ExprParseException(const char * const start, const std::string &error) : _error(error), _start(start) {};

private:
	std::string _error;
	const char* _start;
};

Expression *get_word(const char *&str);
Expression *get_term(const char *&str);
Expression *get_factor1(const char *&str);
Expression *get_factor2(const char *&str);
Expression *get_expr(const char *&str);

#endif