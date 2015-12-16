#include "IncrementOperation.h"

IncrementOperation::IncrementOperation(const OperationString &source) : Operation(source)
{

}

vector<AssemblyInstruction> IncrementOperation::getInstructions()
{
	vector<AssemblyInstruction> instructions;
	RegistersManager* rm = RegistersManager::getInstance();
	if(source.operands.size() != 1) {
		return instructions;
	}
	string operand = source.operands[0];
	string target = source.target;

	if(rm->isTempRegister(operand) || rm->isNumber(operand)) {
		throw invalid_argument("lvalue required as increment operand");
	}

	if(operand == target) {
		instructions.push_back("addiu\t" + rm->decodeOperand(target) + ", " + rm->decodeOperand(operand) + ", " + "1");
	} else {
		instructions.push_back("addiu\t" + rm->decodeOperand(target) + ", " + rm->decodeOperand(operand) + ", " + "0");
		instructions.push_back("addiu\t" + rm->decodeOperand(operand) + ", " + rm->decodeOperand(operand) + ", " + "1");
	}

	return instructions;
}


