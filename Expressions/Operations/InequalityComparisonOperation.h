#ifndef INEQUALITYCOMPARISONOPERATION_H
#define INEQUALITYCOMPARISONOPERATION_H
#include "Operation.h"

class InequalityComparisonOperation : public Operation
{
public:
	InequalityComparisonOperation(const OperationString& source);
	
	virtual vector<AssemblyInstruction> getInstructions() override;
};

#endif // INEQUALITYCOMPARISONOPERATION_H
