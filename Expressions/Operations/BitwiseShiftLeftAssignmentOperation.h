#ifndef BITWISESHIFTLEFTASSIGNMENTOPERATION_H
#define BITWISESHIFTLEFTASSIGNMENTOPERATION_H
#include "BitwiseShiftLeftOperation.h"

class BitwiseShiftLeftAssignmentOperation : public BitwiseShiftLeftOperation
{
public:
	BitwiseShiftLeftAssignmentOperation(const OperationString& source);

	virtual vector<AssemblyInstruction> getInstructions() override;
};

#endif // BITWISESHIFTLEFTASSIGNMENTOPERATION_H
