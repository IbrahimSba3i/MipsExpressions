#ifndef POWOPERATION_H
#define POWOPERATION_H
#include "Operation.h"
#include "../../System/AssemblyCodeBase.h"
#include "MultiplicationOperation.h"

class PowOperation : public Operation
{
public:
	PowOperation(const OperationString& source);

	virtual vector<AssemblyInstruction> getInstructions() override;
	void addPowCode(vector<AssemblyInstruction> &instructions, string base, string exp, string target);
	void multiplyNumbers(vector<AssemblyInstruction> &instructions, string first, string second, string target);
};

#endif // POWOPERATION_H
