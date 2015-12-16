#ifndef BITWISEANDOPERATION_H
#define BITWISEANDOPERATION_H
#include "Operation.h"

class BitwiseAndOperation : public Operation
{
public:
	BitwiseAndOperation(const OperationString& source);

	virtual vector<AssemblyInstruction> getInstructions() override;
	void performImmediate(vector<AssemblyInstruction> &instructions, const string &target, const string &reg, int val);
};

#endif // BITWISEANDOPERATION_H
