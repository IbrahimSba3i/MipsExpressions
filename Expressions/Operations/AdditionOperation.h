#ifndef ADDITIONOPERATION_H
#define ADDITIONOPERATION_H
#include "Operation.h"

class AdditionOperation : public Operation
{
public:
	AdditionOperation(const OperationString& source);
	
	virtual vector<AssemblyInstruction> getInstructions() override ;
};

#endif // ADDITIONOPERATION_H
