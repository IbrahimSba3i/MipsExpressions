#ifndef BITWISEORASSIGNMENTOPERATION_H
#define BITWISEORASSIGNMENTOPERATION_H
#include "BitwiseOrOperation.h"

class BitwiseOrAssignmentOperation : public BitwiseOrOperation
{
public:
	BitwiseOrAssignmentOperation(const OperationString& source);

	virtual vector<AssemblyInstruction> getInstructions() override;
};

#endif // BITWISEORASSIGNMENTOPERATION_H
