#pragma once
#ifndef ORQUERY_H
#define ORQUERY_H

class OrQuery : public BinaryQuery
{
	friend Query operator|(const Query&, const Query&);
	OrQuery(const Query &left, const Query &right) : 
		BinaryQuery(left, right, "|") {	}

	QueryResult eval(const TextQuery&) const;
};

inline Query operator|(const Query &lhs, const Query &rhs)
{
	return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}

inline QueryResult OrQuery::eval(const TextQuery &text) const
{
	auto right = rhs.eval(text), left = lhs.eval(text);

	auto ret_lines = std::make_shared<std::set<line_no>>(left.begin(), left.end());

	ret_lines->insert(right.begin(), right.end());

	return QueryResult(rep(), ret_lines, left.get_file());
}
#endif // !ORQUERY_H
