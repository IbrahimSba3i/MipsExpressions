#ifndef BITWISEINVOPERATION_H
#define BITWISEINVOPERATION_H
#include "Operation.h"

class BitwiseInvOperation : public Operation
{
public:
	BitwiseInvOperation(const OperationString& source);
	
	virtual vector<AssemblyInstruction> getInstructions() override;
};

#endif // BITWISEINVOPERATION_H
