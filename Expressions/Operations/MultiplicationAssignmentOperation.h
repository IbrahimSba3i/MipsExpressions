#ifndef MULTIPLICATIONASSIGNMENTOPERATION_H
#define MULTIPLICATIONASSIGNMENTOPERATION_H
#include "MultiplicationOperation.h"

class MultiplicationAssignmentOperation : public MultiplicationOperation
{
public:
	MultiplicationAssignmentOperation(const OperationString& source);

	virtual vector<AssemblyInstruction> getInstructions() override;
};

#endif // MULTIPLICATIONASSIGNMENTOPERATION_H
