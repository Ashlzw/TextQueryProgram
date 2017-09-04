#include "Query.h"
#include "TextQuery.h"
#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>

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

bool get_word(string &word)
{
	return !(!(cin >> word) || word == "q");
}

bool get_words(string &lhs, string &rhs)
{
	string line;
	if (!getline(cin, line))
		return false;
	size_t pos = line.find_first_of(' ');
	if (pos == string::npos || pos == 0)
		return false;
	lhs = string(line.begin(), line.begin() + pos);
	if (lhs == "q")
		return false;
	rhs = string(line.begin() + pos + 1, line.end());

	return true;
}

int main()
{
	TextQuery file = TextQuery(ifstream("storyDataFile"));
	do {
#if 0
		string sought;
		if (!get_word(sought)) break;

		Query name(sought);
		QueryResult results = name.eval(file);
		cout << "\nExecuting Query for: " << name << endl;
		print(cout, results) << endl;
#endif
#if 0
		string sought;
		if (!get_word(sought)) break;

		Query notq = ~Query(sought);
		QueryResult results = notq.eval(file);
		cout << "\nExecuting Query for: " << notq << endl;
		print(cout, results) << endl;
#endif
#if 1
		string sought1, sought2;
		if (!get_words(sought1, sought2)) break;

		Query andq = Query(sought1) & Query(sought2);
		cout << "\nExecuting query for: " << andq << endl;
		QueryResult results = andq.eval(file);
		print(cout, results);

		results = Query(sought1).eval(file);
		cout << "\nExecuted query: " << Query(sought1) << endl;
		print(cout, results);

		results = Query(sought2).eval(file);
		cout << "\nExecuted query: " << Query(sought2) << endl;
		print(cout, results);
#endif
#if 0
		string sought1, sought2, sought3;
		if (!get_words(sought1, sought2)) break;
		cout << "\nenter third word: ";
		cin >> sought3;
		Query q = Query(sought1) & Query(sought2)
			| Query(sought3);
		cout << "\nExecuting Query for: " << q << endl;
		const QueryResult results = q.eval(file);
		print(cout, results);
#endif

	} while (true);

	return 0;
}