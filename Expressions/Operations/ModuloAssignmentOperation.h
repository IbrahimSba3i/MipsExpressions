#ifndef MODULOASSIGNMENTOPERATION_H
#define MODULOASSIGNMENTOPERATION_H
#include "ModuloOperation.h"

class ModuloAssignmentOperation : public ModuloOperation
{
public:
	ModuloAssignmentOperation(const OperationString& source);

	virtual vector<AssemblyInstruction> getInstructions() override;
};

#endif // MODULOASSIGNMENTOPERATION_H
