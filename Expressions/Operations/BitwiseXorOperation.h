#ifndef BITWISEXOROPERATION_H
#define BITWISEXOROPERATION_H
#include "Operation.h"

class BitwiseXorOperation : public Operation
{
public:
	BitwiseXorOperation(const OperationString& source);

	virtual vector<AssemblyInstruction> getInstructions() override;
	void performImmediate(vector<AssemblyInstruction> &instructions, const string &target, const string &reg, int val);
};

#endif // BITWISEXOROPERATION_H
