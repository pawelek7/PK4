#ifndef Article_hpp
#define Article_hpp

#include <string>

enum class TypeOfNewspaper
{
	NEW_GAME = 0, REGULAR = 1, EVENT = 2
};

struct TemplateNewspaper
{
	std::string title;
	std::string text;
	std::string date;
};


#endif // !Article_hpp