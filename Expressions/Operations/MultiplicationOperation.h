#ifndef MULTIPLICATIONOPERATION_H
#define MULTIPLICATIONOPERATION_H
#include "Operation.h"

class MultiplicationOperation : public Operation
{
public:
	MultiplicationOperation(const OperationString& source);

	virtual vector<AssemblyInstruction> getInstructions() override;
	vector<AssemblyInstruction> peformMultiplicationByAddition(string reg, int val);
	vector<AssemblyInstruction> peformMultiplicationBySubtraction(string reg, int val);
	vector<AssemblyInstruction> peformMultiplicationByLoading(string reg, int val);
	vector<AssemblyInstruction> getBestMultiplicationWay(string reg, int val);
	vector<AssemblyInstruction> addBinaryMultiplicationCode(string firstOperand, string secondOperand);
};

#endif // MULTIPLICATIONOPERATION_H
