#include "QueryResult.h"

std::ostream & print(std::ostream &os, const QueryResult &qr)
{
	os << qr.sought << " occurs " << qr.lines->size() << " "
		<< make_plural(qr.lines->size(), "time", "s") << std::endl;

	for (auto num : *qr.lines)
	{
		os << "\t(line " << num + 1 << ") " << *(qr.file->begin() + num) << std::endl;
	}

	return os;
	// TODO: insert return statement here
}
