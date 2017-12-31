#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>

#include "Expression.h"

using std::set;
using std::getline;
using std::string;
using std::map;
using std::vector;
using std::cerr;
using std::cout;
using std::cin;
using std::ifstream;
using std::endl;

static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;

#if 0

#define EXPECT_EQ_BASE(equality, expect, actual) \
	do \
	{ \
		test_count++; \
		if (equality) \
			test_pass++; \
		else \
		{ \
			std::clog << __FILE__ << ":" << __LINE__ << " expect: " << expect << " actual: " << actual << std::endl; \
			main_ret = 1; \
		} \
	} while (0)

#define TEST_EQ_LISP(expect, actual) EXPECT_EQ_BASE(expect == actual, expect, actual)

#define TEST_EXPRESSION(lisp, str) \
	do \
	{ \
		const char *tmp = str; \
		std::string ret = get_expr(tmp)->test_expression(); \
		TEST_EQ_LISP(std::string(lisp), ret); \
	} while (0)

static void test_and()
{
	TEST_EXPRESSION("(& Alice Blob)", "Alice & Blob");
	TEST_EXPRESSION("(& (& Alice Blob) Tom)", "Alice & Blob & Tom");
	TEST_EXPRESSION("(& (& (& Alice Blob) Tom) Jerry)", "Alice & Blob & Tom & Jerry");
}

static void test_or()
{
	TEST_EXPRESSION("(| Alice Blob)", "Alice | Blob");
	TEST_EXPRESSION("(| (| Alice Blob) Tom)", "Alice | Blob | Tom");
	TEST_EXPRESSION("(| (| (| Alice Blob) Tom) Jerry)", "Alice | Blob | Tom | Jerry");
}

static void test_not()
{
	TEST_EXPRESSION("~Alice", "~Alice");
}

static void test_comb()
{
	TEST_EXPRESSION("(| (& Alice Blob) Tom)", "Alice & Blob | Tom");
	TEST_EXPRESSION("(| Tom (& Alice Blob))", "Tom | Alice & Blob");
	TEST_EXPRESSION("(| Tom (& Alice ~Blob))", "Tom | Alice & ~Blob");
	TEST_EXPRESSION("~(| (& Alice Blob) (& Tom Jerry))","~(Alice & Blob | Tom & Jerry)");
	TEST_EXPRESSION("(& (& Alice (| Blob Tom)) Jerry)", "Alice & (Blob | Tom) & Jerry");
	TEST_EXPRESSION("(& (| Alice Blob) (| Tom Jerry))", "(Alice | Blob) & (Tom | Jerry)");
}

static void test_parse()
{
	test_and();
	test_or();
	test_not();
	test_comb();
}

#endif

int main(int argc, char *argv[])
{
	string filename;
	string statement;
	bool inputfile = false;
	TextQuery file;

	while (true)
	{
		cout << "Input Command >: ";
		getline(cin, statement);
		if (statement.size() >= 2)
		{
			const char *stream = statement.c_str();
			Expression *expr = get_expr(stream);
			while (*stream == ' ') ++stream;
			if (*stream)
			{
				delete expr;
			}
			else
			{
				print(cout, expr->test_eval().eval(file));
				delete expr;
			}
		}
		else
		{
			if (statement == "Q" || statement == "q")
				break;
			if (statement == "C" || statement == "c" && statement == "F" || statement == "f")
				inputfile = false;
		}
		if (!inputfile)
		{
			cout << "Input Searched File: ";
			getline(cin, filename);
			file = TextQuery(std::ifstream(filename));
			inputfile = true;
		}
	}

	//std::cout << test_pass << "/" << test_count << " (" << std::setprecision(3) << test_pass * 100.0 / test_count << ") passed" << std::endl;
	return main_ret;
}