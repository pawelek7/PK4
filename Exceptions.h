#ifndef Exceptions_hpp
#define Exceptions_hpp

#include <exception>
#include <string>

class BadVectorSize : public std::exception
{
	std::string error_message = "bad vector size";

public:
	BadVectorSize(const char* reason);
	const char* what() const throw();
};

#endif // !Exceptions_hpp
