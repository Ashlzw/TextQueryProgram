#pragma once
#ifndef QUERY_H
#define QUERY_H

#include <string>
#include <iostream>
#include <memory>
#include <algorithm>
#include <iterator>

#include "Query_base.h"
#include "WordQuery.h"

class Query
{
	friend Query operator~(const Query &);
	friend Query operator|(const Query &, const Query &);
	friend Query operator&(const Query &, const Query &);
	friend std::ostream &operator<<(std::ostream &os, const Query &query);
public:
	Query(const std::string &s) : q(new WordQuery(s)) { }
	QueryResult eval(const TextQuery &t) const { return q->eval(t); }
	std::string rep() const 
	{
		return q->rep(); 
	}
private:
	Query(std::shared_ptr<Query_base> query) : q(query) { }
	std::shared_ptr<Query_base> q;
};

#include "NotQuery.h"
#include "BinaryQuery.h"
#include "AndQuery.h"
#include "OrQuery.h"
#endif // !QUERY_H
