#ifndef SUBTRACTIONASSIGNMENTOPERATION_H
#define SUBTRACTIONASSIGNMENTOPERATION_H
#include "SubtractionOperation.h"

class SubtractionAssignmentOperation : public SubtractionOperation
{
public:
	SubtractionAssignmentOperation(const OperationString& source);

	virtual vector<AssemblyInstruction> getInstructions() override;
};

#endif // SUBTRACTIONASSIGNMENTOPERATION_H
