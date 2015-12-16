#ifndef BITWISESHIFTLEFTOPERATION_H
#define BITWISESHIFTLEFTOPERATION_H
#include "Operation.h"

class BitwiseShiftLeftOperation : public Operation
{
public:
	BitwiseShiftLeftOperation(const OperationString& source);
	
	virtual vector<AssemblyInstruction> getInstructions() override;
};

#endif // BITWISESHIFTLEFTOPERATION_H
