#ifndef LOGICALANDOPERATION_H
#define LOGICALANDOPERATION_H
#include "Operation.h"

class LogicalAndOperation : public Operation
{
public:
	LogicalAndOperation(const OperationString& source);
	
	virtual vector<AssemblyInstruction> getInstructions() override;
};

#endif // LOGICALANDOPERATION_H
