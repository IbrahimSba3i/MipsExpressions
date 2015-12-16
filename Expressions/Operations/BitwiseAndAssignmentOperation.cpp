#include "BitwiseAndAssignmentOperation.h"

BitwiseAndAssignmentOperation::BitwiseAndAssignmentOperation(const OperationString &source) : BitwiseAndOperation(source)
{

}

vector<AssemblyInstruction> BitwiseAndAssignmentOperation::getInstructions()
{
	if(!validateAssignment()) {
		throw invalid_argument("lvalue required as left operand of assignment");
	}
	return BitwiseAndOperation::getInstructions();
}


