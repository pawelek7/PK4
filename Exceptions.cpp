#include "Exceptions.h"

BadVectorSize::BadVectorSize(const char* reason)
{
	this->error_message = reason;
}

const char* BadVectorSize::what() const throw()
{
	return this->error_message.c_str();
}