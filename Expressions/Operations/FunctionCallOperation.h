#ifndef FUNCTIONCALLOPERATION_H
#define FUNCTIONCALLOPERATION_H
#include "Operation.h"

class FunctionCallOperation : public Operation
{
public:
	FunctionCallOperation(const OperationString& source);
	
	virtual vector<AssemblyInstruction> getInstructions() override;
};

#endif // FUNCTIONCALLOPERATION_H
