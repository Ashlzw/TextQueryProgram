#include "Expression.h"

#include <cstdlib>
#include <cstring>

Expression *get_word(const char *&str)
{
    const char *p = str;

    std::string ret;
	bool is_word = false;
    while (*p == ' ') ++p;
    for (int i = 0; true; ++i)
    {
		if ((p[i] <= 'z' && p[i] >= 'a') || (p[i] <= 'Z' && p[i] >= 'A'))
		{
			ret.push_back(p[i]);
			is_word = true;
		}
        else
        {
			if (is_word)
			{
				str = p + i;
				return new Expression(ret);
			}
			else
			{
				throw ExprParseException(p, "Is not a word.");
			}
        }
    }
}

Expression *get_term(const char *&str)
{
	try
	{
		return get_word(str);
	}
	catch (const ExprParseException &e)
	{
		if (*str == '(')
		{
			try
			{
				++str;
				Expression *ret = get_expr(str);
				const char *p = str;
				if (*p == ')')
				{
					str = ++p;
					return ret;
				}
				else
				{
					throw ExprParseException(p, "Need a right paranthesis.");
				}
			}
			catch (const ExprParseException &e1)
			{
				throw e1;
			}
		}
		else
		{
			throw e;
		}
	}

	return nullptr;
}

Expression *get_factor1(const char *&str)
{
	try
	{
		return get_term(str);
	}
	catch (const ExprParseException &e)
	{
		if (*str == '~')
		{
			++str;
			try
			{
				return new Expression('~', get_term(str));
			}
			catch (const ExprParseException &e1)
			{
				throw e1;
			}

		}
		else
		{
			throw e;
		}
	}

    //return *str != '~' ? get_term(str) : new Expression('~', get_term(++str));
}

Expression *get_factor2(const char *&str)
{
	Expression *ret = nullptr;
	try
	{
		ret = get_factor1(str);
	}
	catch (const ExprParseException &e)
	{
		throw e;
	}

    //Expression *ret = get_factor1(str);
	while (true)
	{
		while (*str == ' ') ++str;
		if (*str == '&')
		{
			++str;
			while (*str == ' ') ++str;
			try
			{
				ret = new Expression('&', ret, get_factor1(str));
			}
			catch (const ExprParseException &e)
			{
				throw e;
			}
		}
		else
			break;
	}

    return ret;
}

Expression *get_expr(const char *&str)
{
    Expression *ret = nullptr;
	try
	{
		ret = get_factor2(str);
	}
	catch (const ExprParseException &e)
	{
		throw e;
	}
	while (true)
	{
		while (*str == ' ') ++str;
		if (*str == '|')
		{
			++str;
			while (*str == ' ') ++str;
			try
			{
				ret = new Expression('|', ret, get_factor2(str));
			}
			catch (const ExprParseException &e)
			{
				throw e;
			}
		}
		else
			break;
	}

    return ret;
}