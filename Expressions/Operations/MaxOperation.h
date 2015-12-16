#ifndef MAXOPERATION_H
#define MAXOPERATION_H
#include "Operation.h"

class MaxOperation : public Operation
{
public:
	MaxOperation(const OperationString& source);
	
	virtual vector<AssemblyInstruction> getInstructions() override;
};

#endif // MAXOPERATION_H
