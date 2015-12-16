#ifndef BITWISEXORASSIGNMENTOPERATION_H
#define BITWISEXORASSIGNMENTOPERATION_H
#include "BitwiseXorOperation.h"

class BitwiseXorAssignmentOperation : public BitwiseXorOperation
{
public:
	BitwiseXorAssignmentOperation(const OperationString& source);

	virtual vector<AssemblyInstruction> getInstructions() override;
};

#endif // BITWISEXORASSIGNMENTOPERATION_H
