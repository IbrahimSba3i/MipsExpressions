#include "SubtractionAssignmentOperation.h"

SubtractionAssignmentOperation::SubtractionAssignmentOperation(const OperationString &source) : SubtractionOperation(source)
{

}

vector<AssemblyInstruction> SubtractionAssignmentOperation::getInstructions()
{
	if(!validateAssignment()) {
		throw invalid_argument("lvalue required as left operand of assignment");
	}
	return SubtractionOperation::getInstructions();
}


