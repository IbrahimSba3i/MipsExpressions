#include "IncorrectSymbol.h"




IncorrectSymbol::IncorrectSymbol(char c, const string &msg)
{
	this->c = c;
	this->msg = msg;
}

IncorrectSymbol::IncorrectSymbol(char c, const char *msg)
{
	this->c = c;
	this->msg = msg;
}

IncorrectSymbol::IncorrectSymbol(char c)
{
	this->c = c;
}

char IncorrectSymbol::gotSymbol() const
{
	return c;
}

IncorrectSymbol::~IncorrectSymbol() throw()
{

}

const char * IncorrectSymbol::what() const  throw()
{
	return (string("Unexpected symbol: '") + c + "' " + msg).c_str();
}


