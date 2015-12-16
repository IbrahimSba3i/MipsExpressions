#ifndef BITWISEANDASSIGNMENTOPERATION_H
#define BITWISEANDASSIGNMENTOPERATION_H
#include "BitwiseAndOperation.h"

class BitwiseAndAssignmentOperation : public BitwiseAndOperation
{
public:
	BitwiseAndAssignmentOperation(const OperationString& source);

	virtual vector<AssemblyInstruction> getInstructions() override;
};

#endif // BITWISEANDASSIGNMENTOPERATION_H
