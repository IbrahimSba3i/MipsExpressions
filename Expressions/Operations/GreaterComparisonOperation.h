#ifndef GREATERCOMPARISONOPERATION_H
#define GREATERCOMPARISONOPERATION_H
#include "Operation.h"

class GreaterComparisonOperation : public Operation
{
public:
	GreaterComparisonOperation(const OperationString& source);
	
	virtual vector<AssemblyInstruction> getInstructions() override;
};

#endif // GREATERCOMPARISONOPERATION_H
