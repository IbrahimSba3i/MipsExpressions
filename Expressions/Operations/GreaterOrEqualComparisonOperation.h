#ifndef GREATEROREQUALCOMPARISONOPERATION_H
#define GREATEROREQUALCOMPARISONOPERATION_H
#include "Operation.h"

class GreaterOrEqualComparisonOperation : public Operation
{
public:
	GreaterOrEqualComparisonOperation(const OperationString& source);
	
	virtual vector<AssemblyInstruction> getInstructions() override;
};

#endif // GREATEROREQUALCOMPARISONOPERATION_H
