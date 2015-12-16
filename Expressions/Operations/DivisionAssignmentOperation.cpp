#include "DivisionAssignmentOperation.h"

DivisionAssignmentOperation::DivisionAssignmentOperation(const OperationString &source) : DivisionOperation(source)
{

}

vector<AssemblyInstruction> DivisionAssignmentOperation::getInstructions()
{
	if(!validateAssignment()) {
		throw invalid_argument("lvalue required as left operand of assignment");
	}
	return DivisionOperation::getInstructions();
}


