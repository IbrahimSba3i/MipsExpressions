#ifndef BITWISESHIFTRIGHTASSIGNMENTOPERATION_H
#define BITWISESHIFTRIGHTASSIGNMENTOPERATION_H
#include "BitwiseShiftRightOperation.h"

class BitwiseShiftRightAssignmentOperation : public BitwiseShiftRightOperation
{
public:
	BitwiseShiftRightAssignmentOperation(const OperationString& source);

	virtual vector<AssemblyInstruction> getInstructions() override;
};

#endif // BITWISESHIFTRIGHTASSIGNMENTOPERATION_H
