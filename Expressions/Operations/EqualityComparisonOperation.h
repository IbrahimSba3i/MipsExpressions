#ifndef EQUALITYCOMPARISONOPERATION_H
#define EQUALITYCOMPARISONOPERATION_H
#include "Operation.h"

class EqualityComparisonOperation : public Operation
{
public:
	EqualityComparisonOperation(const OperationString& source);
	
	virtual vector<AssemblyInstruction> getInstructions() override;
};

#endif // EQUALITYCOMPARISONOPERATION_H
