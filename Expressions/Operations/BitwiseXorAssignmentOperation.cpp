#include "BitwiseXorAssignmentOperation.h"

BitwiseXorAssignmentOperation::BitwiseXorAssignmentOperation(const OperationString &source) : BitwiseXorOperation(source)
{

}

vector<AssemblyInstruction> BitwiseXorAssignmentOperation::getInstructions()
{
	if(!validateAssignment()) {
		throw invalid_argument("lvalue required as left operand of assignment");
	}
	return BitwiseXorOperation::getInstructions();
}


