#ifndef INCORRECTSYMBOL_H
#define INCORRECTSYMBOL_H
#include <stdexcept>
#include <string>

using namespace std;

class IncorrectSymbol : public exception
{
	char c;
	string msg;
public:
	explicit IncorrectSymbol(char c, const string &msg);
	explicit IncorrectSymbol(char c, const char* msg);
	explicit IncorrectSymbol(char c);

	char gotSymbol() const;

	virtual ~IncorrectSymbol() throw();

	virtual const char* what() const throw();
};

#endif // INCORRECTSYMBOL_H
