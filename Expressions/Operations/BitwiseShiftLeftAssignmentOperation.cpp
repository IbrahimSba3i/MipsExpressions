#include "BitwiseShiftLeftAssignmentOperation.h"

BitwiseShiftLeftAssignmentOperation::BitwiseShiftLeftAssignmentOperation(const OperationString &source) : BitwiseShiftLeftOperation(source)
{

}

vector<AssemblyInstruction> BitwiseShiftLeftAssignmentOperation::getInstructions()
{
	if(!validateAssignment()) {
		throw invalid_argument("lvalue required as left operand of assignment");
	}
	return BitwiseShiftLeftOperation::getInstructions();
}


