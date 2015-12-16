#include "MultiplicationAssignmentOperation.h"

MultiplicationAssignmentOperation::MultiplicationAssignmentOperation(const OperationString &source) : MultiplicationOperation(source)
{

}

vector<AssemblyInstruction> MultiplicationAssignmentOperation::getInstructions()
{
	if(!validateAssignment()) {
		throw invalid_argument("lvalue required as left operand of assignment");
	}
	return MultiplicationOperation::getInstructions();
}


