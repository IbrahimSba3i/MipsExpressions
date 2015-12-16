#include "ExpressionParser.h"


ExpressionParser::ExpressionParser(const string & source, unsigned int flags)
{
	s.setSource(source);
	this->flags = flags;
	registersManager = RegistersManager::getInstance();
	assemblyCode = AssemblyCodeBase::getInstance();
	isNegativeFlag = false;
	initializeSymbolsDescription();
}

ExpressionParser::ExpressionParser(const ExpressionParser & other)
{
	s = other.s;
	flags = other.flags;
	assemblyCode = AssemblyCodeBase::getInstance();
	registersManager = RegistersManager::getInstance();
	isNegativeFlag = false;
	initializeSymbolsDescription();
}

void ExpressionParser::initializeSymbolsDescription()
{
	SymbolDescription symbols;

	symbols.associativity = LEFT;
	symbols.type = BINARY;
	symbols.push_back(",");
	symbolsDescription.push_back(symbols);
	symbols.clear();

	symbols.associativity = RIGHT;
	symbols.type = BINARY;
	symbols.push_back("=");
	symbols.push_back("+=");
	symbols.push_back("-=");
	symbols.push_back("*=");
	symbols.push_back("/=");
	symbols.push_back("%=");
	symbols.push_back("<<=");
	symbols.push_back(">>=");
	symbols.push_back("&=");
	symbols.push_back("^=");
	symbols.push_back("|=");
	symbolsDescription.push_back(symbols);
	symbols.clear();

	symbols.associativity = LEFT;
	symbols.type = BINARY;
	symbols.push_back("||");
	symbolsDescription.push_back(symbols);
	symbols.clear();

	symbols.associativity = LEFT;
	symbols.type = BINARY;
	symbols.push_back("&&");
	symbolsDescription.push_back(symbols);
	symbols.clear();

	symbols.associativity = LEFT;
	symbols.type = BINARY;
	symbols.push_back("|");
	symbolsDescription.push_back(symbols);
	symbols.clear();

	symbols.associativity = LEFT;
	symbols.type = BINARY;
	symbols.push_back("^");
	symbolsDescription.push_back(symbols);
	symbols.clear();

	symbols.associativity = LEFT;
	symbols.type = BINARY;
	symbols.push_back("&");
	symbolsDescription.push_back(symbols);
	symbols.clear();

	symbols.associativity = LEFT;
	symbols.type = BINARY;
	symbols.push_back("==");
	symbols.push_back("!=");
	symbolsDescription.push_back(symbols);
	symbols.clear();

	symbols.associativity = LEFT;
	symbols.type = BINARY;
	symbols.push_back("<=");
	symbols.push_back(">=");
	symbols.push_back("<");
	symbols.push_back(">");
	symbolsDescription.push_back(symbols);
	symbols.clear();

	symbols.associativity = LEFT;
	symbols.type = BINARY;
	symbols.push_back("<<");
	symbols.push_back(">>");
	symbolsDescription.push_back(symbols);
	symbols.clear();

	symbols.associativity = LEFT;
	symbols.type = BINARY;
	symbols.push_back("+");
	symbols.push_back("-");
	symbolsDescription.push_back(symbols);
	symbols.clear();

	symbols.associativity = LEFT;
	symbols.type = BINARY;
	symbols.push_back("*");
	symbols.push_back("/");
	symbols.push_back("%");
	symbolsDescription.push_back(symbols);
	symbols.clear();

	symbols.associativity = RIGHT;
	symbols.type = UNARY;
	symbols.push_back("--");
	symbols.push_back("++");
	symbols.push_back("-");
	symbols.push_back("+");
	symbols.push_back("~");
	symbols.push_back("!");
	symbolsDescription.push_back(symbols);
	symbols.clear();

	symbols.associativity = LEFT;
	symbols.type = UNARY;
	symbols.push_back("--");
	symbols.push_back("++");
	symbolsDescription.push_back(symbols);
	symbols.clear();
}

bool ExpressionParser::getNoCommasFlag() const
{
	return (flags & 1);
}


ExpressionParser::~ExpressionParser()
{

}

void ExpressionParser::parse()
{
	string resultRegister = parseBinaryOperator(getNoCommasFlag());
	if(registersManager->isTempRegister(resultRegister))
		registersManager->releaseTempRegister(resultRegister);
	parseWhitespaces();
	if(!s.isFinished()) {
		throw invalid_argument("Expression Not Correct");
	}
}

int ExpressionParser::isNextSymbol(const string& op)
{
	int currentCursor = s.getCursor();
	string nextOp;
	for(int i=0; i<op.length(); i++) {
		if(!s.isFinished())
			nextOp += s.getNext();
	}
	s.setCursor(currentCursor);
	if (nextOp == op) {
		return nextOp.size();
	} else {
		return 0;
	}
}

string ExpressionParser::getNextSymbol(int count) {
	string nextOp;
	for(int i=0; i<count; i++) {
		nextOp += s.getNext();
	}
	return nextOp;
}

int ExpressionParser::isNextOneOf(const vector<string>& symbols)
{
	int count = 0;
	for(int i=0; i<symbols.size(); i++) {
		if(isNextSymbol(symbols[i]))
			return symbols[i].size();
	}
	return 0;
}

string ExpressionParser::parseNextOperator(int precedenceInv)
{
	if(precedenceInv == symbolsDescription.size()) {
		return parseFactor();
	} else if(symbolsDescription[precedenceInv].type == BINARY) {
		return parseBinaryOperator(precedenceInv);
	} else if(symbolsDescription[precedenceInv].type == UNARY) {
		return parseUnaryOperator(precedenceInv);
	} else {
		return "";
	}
}

string ExpressionParser::parseBinaryOperator(int precedenceInv) {

	if(symbolsDescription[precedenceInv].associativity == LEFT) {
		string firstOperand = parseNextOperator(precedenceInv + 1);
		string otherOperand;
		int charsCount = 0;
		while(!s.isFinished() && (charsCount = isNextOneOf(symbolsDescription[precedenceInv]))) {
			string symbol = getNextSymbol(charsCount);
			try {
				otherOperand = parseNextOperator(precedenceInv + 1);
			} catch(IncorrectSymbol& e) {
				Utility::println(e.what());
				s.moveBackward(symbol.size());
				return firstOperand;
			}

			vector<string> args;
			args.push_back(firstOperand);
			args.push_back(otherOperand);
			if(registersManager->isTempRegister(firstOperand)) {
				assemblyCode->add(OperationsFactory::getOperation(OperationString(firstOperand, symbol, args)));
			} else {
				string temp = registersManager->getNextTempRegister();
				assemblyCode->add(OperationsFactory::getOperation(OperationString(temp, symbol, args)));
				firstOperand = temp;
			}
			if(registersManager->isTempRegister(otherOperand)) {
				registersManager->releaseTempRegister(otherOperand);
			}
		}
		return firstOperand;
	}
	else {
		string operand = parseNextOperator(precedenceInv + 1);
		int charsCount = 0;
		string symbol, leftOperand;
		stack<pair<string, string> > S;
		while(!s.isFinished() && (charsCount = isNextOneOf(symbolsDescription[precedenceInv]))) {
			symbol = getNextSymbol(charsCount);
			S.push(make_pair(operand, symbol));
			operand = parseNextOperator(precedenceInv + 1);
		}

		while(!S.empty()) {
			leftOperand = S.top().first;
			symbol = S.top().second;
			S.pop();
			vector<string> args;
			args.push_back(leftOperand);
			args.push_back(operand);
			assemblyCode->add(OperationsFactory::getOperation(OperationString(leftOperand, symbol, args)));
			operand = leftOperand;
		}
		return operand;
	}
}

string ExpressionParser::parseUnaryOperator(int precedenceInv)
{
	if(symbolsDescription[precedenceInv].associativity == RIGHT) {
		parseWhitespaces();
		int charsCount = 0;
		string symbol;
		stack<string> S;
		while(!s.isFinished() && (charsCount = isNextOneOf(symbolsDescription[precedenceInv]))) {
			symbol = getNextSymbol(charsCount);
			S.push(symbol);
			if(symbol == "-") {
				isNegativeFlag = true;
			}
			parseWhitespaces();
		}

		string operand = parseNextOperator(precedenceInv + 1);
		string target = operand;

		while(!S.empty()) {
			symbol = S.top();
			S.pop();
			if((isNegativeFlag && symbol == "-") || symbol == "+") {
				continue;
			}
			if(!registersManager->isTempRegister(target) && symbol != "++" && symbol != "--") {
				target = registersManager->getNextTempRegister();
				assemblyCode->add(OperationsFactory::getOperation(OperationString(target, symbol, Utility::stringToVector(operand))));
			}
			else {
				assemblyCode->add(OperationsFactory::getOperation(OperationString(target, symbol, Utility::stringToVector(target))));
			}
		}
		isNegativeFlag = false;
		return target;
	}
	else {
		parseWhitespaces();
		int charsCount = 0;
		string symbol;
		string operand = parseNextOperator(precedenceInv + 1);
		string target = operand;
		while(!s.isFinished() && (charsCount = isNextOneOf(symbolsDescription[precedenceInv]))) {
			symbol = getNextSymbol(charsCount);
			parseWhitespaces();
			if(!registersManager->isTempRegister(target)) {
				target = registersManager->getNextTempRegister();
				assemblyCode->add(OperationsFactory::getOperation(OperationString(target, symbol, Utility::stringToVector(operand))));
			}
			else {
				assemblyCode->add(OperationsFactory::getOperation(OperationString(target, symbol, Utility::stringToVector(target))));
			}
		}
		return target;
	}
}



string ExpressionParser::parseFactor()
{
	string resultFactor = "";
	parseWhitespaces();
	if(s.isFinished())
		throw invalid_argument("Expression Not Correct");
	if(s.peekNext() == '(') {
		s.moveForward();
		resultFactor = parseBinaryOperator(0);
		parseWhitespaces();
		if(s.isFinished() || s.peekNext() != ')') {
			throw invalid_argument("Expression Not Correct");
		}
		else {
			s.moveForward();
			parseWhitespaces();
		}
	} else if(isdigit(s.peekNext())) {
		int number = parseNumber(isNegativeFlag);
		resultFactor = Utility::intToString(number);
	} else if(Utility::isVariableCharacter(s.peekNext())) {
		string variable = parseVariable();
		if(!s.isFinished() && s.peekNext() == '(') {
			// it's a function and not a variable
			s.moveForward();
			vector<string> variablesList = parseVariablesList();

			if(s.isFinished() || s.peekNext() != ')') {
				throw invalid_argument("Expression Not Correct");
			}

			s.moveForward();
			parseWhitespaces();
			string operand = registersManager->getNextTempRegister();
			assemblyCode->add(OperationsFactory::getOperation(OperationString(operand, variable, variablesList)));
			resultFactor = operand;
		} else {
			// it's a normal variable
			resultFactor = variable;
		}
	} else {
		if(Utility::isOperatorCharacter(s.peekNext()))
			throw IncorrectSymbol(s.peekNext());
		else
			throw invalid_argument("Expression Not Correct");
	}
	return resultFactor;
}

vector<string> ExpressionParser::parseVariablesList() {
	vector<string> variablesList;
	string variable = parseNextOperator(1);
	parseWhitespaces();
	if(variable.size() > 0) {
		variablesList.push_back(variable);
	} else {
		throw invalid_argument("Expression Not Correct");
	}

	while(!s.isFinished() && s.peekNext() == ',') {
		s.moveForward();
		variable = parseNextOperator(1);
		parseWhitespaces();
		if(variable.size() > 0) {
			variablesList.push_back(variable);
		} else {
			throw invalid_argument("Expression Not Correct");
		}
	}
	return variablesList;
}


void ExpressionParser::parseWhitespaces()
{
	while(!s.isFinished() && s.peekNext() == ' ') {
		s.moveForward();
	}
}

string ExpressionParser::parseVariable()
{
	string variableName = "";
	while(!s.isFinished() && (Utility::isVariableCharacter(s.peekNext()) || Utility::isDigit(s.peekNext()))) {
		variableName += s.peekNext();
		s.moveForward();
	}
	parseWhitespaces();
	return variableName;
}

int ExpressionParser::parseNumber(bool isNegative)
{
	int base = 10;
	if(!s.isFinished()) {
		if(s.peekNext() == '0') {
			s.moveForward();
			if(s.peekNext() == 'x' || s.peekNext() == 'X') {
				base = 16;
				s.moveForward();
			} else if(s.peekNext() == 'b') {
				base = 2;
				s.moveForward();
			} else if(s.peekNext() >= '0' && s.peekNext() <= '7') {
				base = 8;
				s.moveForward();
			} else {
				throw invalid_argument("Expression Not Correct");
			}

		}
	}
	int maxInt = 0x7fffffff;
	int minInt = 0x80000000;
	int num = 0;
	while(!s.isFinished() && Utility::isDigit(s.peekNext(), base)) {
		int digit = s.peekNext() - int('0');
		if(!isNegative) {
			if(num > (maxInt - digit)/base) {
				throw out_of_range("number is too large");
			}
		} else {
			if(num > (minInt + digit)/-base) {
				throw out_of_range("number is too large");
			}
		}
		num = num * base + digit;
		s.moveForward();
	}
	parseWhitespaces();
	num = (isNegative? -num:num);
	return num;
}
