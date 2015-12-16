#include "CommaOperation.h"

CommaOperation::CommaOperation(const OperationString &source) : Operation(source)
{

}

vector<AssemblyInstruction> CommaOperation::getInstructions()
{
	vector<AssemblyInstruction> instructions;
	RegistersManager* rm = RegistersManager::getInstance();

	if(source.operands.size() != 2) {
		return instructions;
	}

	string secondOperand = source.operands[1];
	string v0 = rm->decodeOperand(source.target);
	string s0 = rm->decodeOperand(secondOperand);

	instructions.push_back("addiu\t" + v0 + ", " + s0 + ", " + "0");

	return instructions;
}


