#ifndef LOGICALOROPERATION_H
#define LOGICALOROPERATION_H
#include "Operation.h"

class LogicalOrOperation : public Operation
{
public:
	LogicalOrOperation(const OperationString& source);
	
	virtual vector<AssemblyInstruction> getInstructions() override;
};

#endif // LOGICALOROPERATION_H
