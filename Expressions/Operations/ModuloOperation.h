#ifndef MODULOOPERATION_H
#define MODULOOPERATION_H
#include "Operation.h"

class ModuloOperation : public Operation
{
public:
	ModuloOperation(const OperationString& source);

	virtual vector<AssemblyInstruction> getInstructions() override;
	void addDivisionCode(vector<AssemblyInstruction> &instructions, const string &num, const string &den, bool firstIsNum, bool secondIsNum, int numericalValue);
	void divideNumbers(vector<AssemblyInstruction> &instructions, const string &num, const string &den, bool firstIsNum, bool secondIsNum, int numericalValue);
};

#endif // MODULOOPERATION_H
