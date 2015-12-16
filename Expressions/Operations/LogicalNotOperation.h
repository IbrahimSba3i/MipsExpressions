#ifndef LOGICALNOTOPERATION_H
#define LOGICALNOTOPERATION_H
#include "Operation.h"

class LogicalNotOperation : public Operation
{
public:
	LogicalNotOperation(const OperationString& source);
	
	virtual vector<AssemblyInstruction> getInstructions() override;
};

#endif // LOGICALNOTOPERATION_H
