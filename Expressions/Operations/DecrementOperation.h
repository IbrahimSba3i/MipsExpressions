#ifndef DECREMENTOPERATION_H
#define DECREMENTOPERATION_H
#include "Operation.h"

class DecrementOperation : public Operation
{
public:
	DecrementOperation(const OperationString& source);
	
	virtual vector<AssemblyInstruction> getInstructions() override;
};

#endif // DECREMENTOPERATION_H
