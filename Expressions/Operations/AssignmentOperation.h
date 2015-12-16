#ifndef ASSIGNMENTOPERATION_H
#define ASSIGNMENTOPERATION_H
#include "Operation.h"
#include "../../System/AssemblyCodeBase.h"

class AssignmentOperation : public Operation
{
public:
	AssignmentOperation(const OperationString& source);

	virtual vector<AssemblyInstruction> getInstructions() override;
};

#endif // ASSIGNMENTOPERATION_H
