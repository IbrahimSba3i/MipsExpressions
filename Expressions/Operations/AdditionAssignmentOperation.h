#ifndef ADDITIONASSIGNMENTOPERATION_H
#define ADDITIONASSIGNMENTOPERATION_H
#include "AdditionOperation.h"

class AdditionAssignmentOperation : public AdditionOperation
{
public:
	AdditionAssignmentOperation(const OperationString& source);

	virtual vector<AssemblyInstruction> getInstructions() override;
};

#endif // ADDITIONASSIGNMENTOPERATION_H
