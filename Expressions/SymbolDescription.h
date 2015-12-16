#ifndef SYMBOLDESCRIPTION_H
#define SYMBOLDESCRIPTION_H
#include <vector>
#include <string>

using namespace std;

enum Associativity
{
	LEFT,
	RIGHT
};

enum OperatorType
{
	UNARY,
	BINARY,
	TERNARY
};

class SymbolDescription : public vector<string>
{
public:
	Associativity associativity = LEFT;
	OperatorType type = BINARY;
};

#endif // SYMBOLDESCRIPTION_H
