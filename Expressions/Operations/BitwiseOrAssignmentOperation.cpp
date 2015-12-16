#include "BitwiseOrAssignmentOperation.h"

BitwiseOrAssignmentOperation::BitwiseOrAssignmentOperation(const OperationString &source) : BitwiseOrOperation(source)
{

}

vector<AssemblyInstruction> BitwiseOrAssignmentOperation::getInstructions()
{
	if(!validateAssignment()) {
		throw invalid_argument("lvalue required as left operand of assignment");
	}
	return BitwiseOrOperation::getInstructions();
}


