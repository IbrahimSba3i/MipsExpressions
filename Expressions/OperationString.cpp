#include "OperationString.h"

OperationString::OperationString()
{
	
}

OperationString::OperationString(const string &target, const string &operation, const vector<string> &operands)
{
	this->target = target;
	this->operation = operation;
	this->operands = operands;
}

string OperationString::toString() const
{
	string result = "Target: " + target + "\nOperation: " + operation + "\nOperands: " + operands[0];
	for(int i=1; i<operands.size(); i++) {
		result += ", " + operands[i];
	}
	result += "\n";
	return result;
}
