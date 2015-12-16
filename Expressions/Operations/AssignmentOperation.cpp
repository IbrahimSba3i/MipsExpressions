#include "AssignmentOperation.h"

AssignmentOperation::AssignmentOperation(const OperationString &source) : Operation(source)
{

}

vector<AssemblyInstruction> AssignmentOperation::getInstructions()
{
	if(!validateAssignment()) {
		throw invalid_argument("lvalue required as left operand of assignment");
	}

	RegistersManager* rm = RegistersManager::getInstance();
	vector<AssemblyInstruction> instructions;

	string target = source.target;
	string operand = source.operands[1];

	if(rm->isNumber(operand)) {
		int val = Utility::stringToInt(rm->decodeOperand(operand));
		loadToRegister(instructions, val, target);
	} else if(!rm->isTempRegister(operand)) {
		moveToRegister(instructions, operand, target);
	} else {
		// Temp register
		AssemblyCodeBase* codeBase = AssemblyCodeBase::getInstance();

		bool succeeded = codeBase->replaceTargetInLast(rm->decodeOperand(operand), rm->decodeOperand(target));
		if(!succeeded) {
			moveToRegister(instructions, operand ,target);
		}
	}

	return instructions;
}


