#ifndef DIVISIONOPERATION_H
#define DIVISIONOPERATION_H
#include "Operation.h"

class DivisionOperation : public Operation
{
public:
	DivisionOperation(const OperationString& source);

	virtual vector<AssemblyInstruction> getInstructions() override;
	void addDivisionCode(vector<AssemblyInstruction> &instructions, const string &num, const string &den, bool firstIsNum, bool secondIsNum, int numericalValue);
	void divideNumbers(vector<AssemblyInstruction> &instructions, const string &num, const string &den, bool firstIsNum, bool secondIsNum, int numericalValue);
};

#endif // DIVISIONOPERATION_H
