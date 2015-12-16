#include "BitwiseShiftRightAssignmentOperation.h"

BitwiseShiftRightAssignmentOperation::BitwiseShiftRightAssignmentOperation(const OperationString &source) : BitwiseShiftRightOperation(source)
{

}

vector<AssemblyInstruction> BitwiseShiftRightAssignmentOperation::getInstructions()
{
	if(!validateAssignment()) {
		throw invalid_argument("lvalue required as left operand of assignment");
	}
	return BitwiseShiftRightOperation::getInstructions();
}


