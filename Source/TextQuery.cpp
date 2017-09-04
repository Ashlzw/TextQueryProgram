#include "TextQuery.h"

#include <iostream>

typedef std::map<std::string, std::shared_ptr<std::set<TextQuery::line_no>>> wmType;

typedef wmType::const_iterator wmIter;

typedef std::shared_ptr<std::set<TextQuery::line_no>> lineType;

typedef std::set<TextQuery::line_no>::const_iterator lineIter;

TextQuery::TextQuery(std::ifstream &is) : file(new std::vector<std::string>)
{
	std::string text;
	while (std::getline(is, text))
	{
		file->push_back(text);
		int n = file->size() - 1;
		std::istringstream line(text);
		std::string word;
		while (line >> word)
		{
			word = cleanup_str(word);
			lineType &lines = wm[word];
			if (!lines)
			{
				lines.reset(new std::set<line_no>);
			}
			lines->insert(n);
		}
	}
}

QueryResult TextQuery::query(const std::string &sought) const
{
	static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);

	wmIter loc = wm.find(sought);
	if (loc == wm.end())
		return QueryResult(sought, nodata, file);
	else
		return QueryResult(sought, loc->second, file);
}

void TextQuery::display_map()
{
	wmIter iter = wm.begin(), iter_end = wm.end();

	for (; iter != iter_end; ++iter)
	{
		std::cout << "word: " << iter->first << " {";

		lineType text_locs = iter->second;
		lineIter loc_iter = text_locs->begin(),
			loc_iter_end = text_locs->end();
	
		while (loc_iter != loc_iter_end)
		{
			std::cout << *loc_iter;

			if (++loc_iter != loc_iter_end)
			{
				std::cout << ", ";
			}
		}

		std::cout << "}\n";
	}

	std::cout << std::endl;
}

std::string TextQuery::cleanup_str(const std::string &word)
{
	std::string ret;
	for (std::string::const_iterator it = word.begin();
				it != word.end(); ++it)
	{
		if (!ispunct(*it))
		{
			ret += tolower(*it);
		}
	}

	return ret;
}
