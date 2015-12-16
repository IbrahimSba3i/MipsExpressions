#ifndef MINOPERATION_H
#define MINOPERATION_H
#include "Operation.h"

class MinOperation : public Operation
{
public:
	MinOperation(const OperationString& source);
	
	virtual vector<AssemblyInstruction> getInstructions() override;
};

#endif // MINOPERATION_H
