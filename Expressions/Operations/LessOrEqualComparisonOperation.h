#ifndef LESSOREQUALCOMPARISONOPERATION_H
#define LESSOREQUALCOMPARISONOPERATION_H
#include "Operation.h"

class LessOrEqualComparisonOperation : public Operation
{
public:
	LessOrEqualComparisonOperation(const OperationString& source);
	
	virtual vector<AssemblyInstruction> getInstructions() override;
};

#endif // LESSOREQUALCOMPARISONOPERATION_H
