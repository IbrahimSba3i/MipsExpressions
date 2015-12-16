#ifndef INCREMENTOPERATION_H
#define INCREMENTOPERATION_H
#include "Operation.h"

class IncrementOperation : public Operation
{
public:
	IncrementOperation(const OperationString& source);
	
	virtual vector<AssemblyInstruction> getInstructions() override;
};

#endif // INCREMENTOPERATION_H
