#ifndef ABSOPERATION_H
#define ABSOPERATION_H
#include "Operation.h"

class AbsOperation : public Operation
{
public:
	AbsOperation(const OperationString& source);
	
	virtual vector<AssemblyInstruction> getInstructions() override;
};

#endif // ABSOPERATION_H
