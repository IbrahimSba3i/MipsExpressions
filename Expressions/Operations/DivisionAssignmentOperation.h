#ifndef DIVISIONASSIGNMENTOPERATION_H
#define DIVISIONASSIGNMENTOPERATION_H
#include "DivisionOperation.h"

class DivisionAssignmentOperation : public DivisionOperation
{
public:
	DivisionAssignmentOperation(const OperationString& source);

	virtual vector<AssemblyInstruction> getInstructions() override;
};

#endif // DIVISIONASSIGNMENTOPERATION_H
