#ifndef BITWISEOROPERATION_H
#define BITWISEOROPERATION_H
#include "Operation.h"

class BitwiseOrOperation : public Operation
{
public:
	BitwiseOrOperation(const OperationString& source);

	virtual vector<AssemblyInstruction> getInstructions() override;
	void performImmediate(vector<AssemblyInstruction> &instructions, const string &target, const string &reg, int val);
};

#endif // BITWISEOROPERATION_H
