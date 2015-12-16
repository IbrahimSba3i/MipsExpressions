#ifndef BITWISESHIFTRIGHTOPERATION_H
#define BITWISESHIFTRIGHTOPERATION_H
#include "Operation.h"

class BitwiseShiftRightOperation : public Operation
{
public:
	BitwiseShiftRightOperation(const OperationString& source);
	
	virtual vector<AssemblyInstruction> getInstructions() override;
};

#endif // BITWISESHIFTRIGHTOPERATION_H
