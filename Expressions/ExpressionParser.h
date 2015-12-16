#ifndef EXPRESSIONPARSER_H
#define EXPRESSIONPARSER_H
#include "../System/ParsingString.h"
#include "OperationString.h"
#include "OperationsFactory.h"
#include "../System/RegistersManager.h"
#include "SymbolDescription.h"
#include "../System/Utility.h"
#include "../System/AssemblyCodeBase.h"
#include <stdexcept>
#include <vector>
#include <cctype>
#include <string>
#include <sstream>
#include <iostream>
#include <stack>
#include <queue>
#include <cstdlib>
#include "../System/IncorrectSymbol.h"
#ifdef QT_VERSION
	#include <QDebug>
	#include <QString>
#endif

using namespace std;

class ExpressionParser
{
	unsigned int flags;
	ParsingString s;
	RegistersManager* registersManager;
	AssemblyCodeBase* assemblyCode;
	bool isNegativeFlag;
	vector<SymbolDescription> symbolsDescription;

	void initializeSymbolsDescription();
	bool getNoCommasFlag() const;
public:
	const unsigned int NO_COMMA = 0x00000001;


	ExpressionParser(const string& s, unsigned int flags = 0);
	ExpressionParser(const ExpressionParser&other);
	~ExpressionParser();

	void parse();

	string parseFactor();
	string parseVariable();

	int parseNumber(bool isNegative);
	void parseWhitespaces();
	vector<string> parseVariablesList();

	int isNextSymbol(const string &op);
	string getNextSymbol(int count);
	int isNextOneOf(const vector<string> &symbols);

	string parseNextOperator(int precedenceInv);
	string parseBinaryOperator(int precedenceInv);
	string parseUnaryOperator(int precedenceInv);
};

#endif // EXPRESSIONPARSER_H
