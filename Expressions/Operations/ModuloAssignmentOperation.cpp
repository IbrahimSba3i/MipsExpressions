#include "ModuloAssignmentOperation.h"

ModuloAssignmentOperation::ModuloAssignmentOperation(const OperationString &source) : ModuloOperation(source)
{

}

vector<AssemblyInstruction> ModuloAssignmentOperation::getInstructions()
{
	if(!validateAssignment()) {
		throw invalid_argument("lvalue required as left operand of assignment");
	}
	return ModuloOperation::getInstructions();
}


