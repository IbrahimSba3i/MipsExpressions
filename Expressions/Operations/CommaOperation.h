#ifndef COMMAOPERATION_H
#define COMMAOPERATION_H
#include "Operation.h"

class CommaOperation : public Operation
{
public:
	CommaOperation(const OperationString& source);
	
	virtual vector<AssemblyInstruction> getInstructions() override;
};

#endif // COMMAOPERATION_H
