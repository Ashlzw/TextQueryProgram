#pragma once
#ifndef MAKE_PLURAL_H
#define MAKE_PLURAL_H

#include <string>

static std::string make_plural(size_t ctr, const std::string &word, const std::string &ending)
{
	return ctr > 1 ? word + ending : word;
}

#endif // !MAKE_PLURAL_H