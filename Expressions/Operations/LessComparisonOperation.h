#ifndef LESSCOMPARISONOPERATION_H
#define LESSCOMPARISONOPERATION_H
#include "Operation.h"

class LessComparisonOperation : public Operation
{
public:
	LessComparisonOperation(const OperationString& source);
	
	virtual vector<AssemblyInstruction> getInstructions() override;
};

#endif // LESSCOMPARISONOPERATION_H
