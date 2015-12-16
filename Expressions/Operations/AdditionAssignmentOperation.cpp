#include "AdditionAssignmentOperation.h"

AdditionAssignmentOperation::AdditionAssignmentOperation(const OperationString &source) : AdditionOperation(source)
{

}

vector<AssemblyInstruction> AdditionAssignmentOperation::getInstructions()
{
	if(!validateAssignment()) {
		throw invalid_argument("lvalue required as left operand of assignment");
	}
	return AdditionOperation::getInstructions();
}


