#ifndef SUBTRACTIONOPERATION_H
#define SUBTRACTIONOPERATION_H
#include "Operation.h"

class SubtractionOperation : public Operation
{
public:
	SubtractionOperation(const OperationString& source);
	
	virtual vector<AssemblyInstruction> getInstructions() override ;
};

#endif // SUBTRACTIONOPERATION_H
