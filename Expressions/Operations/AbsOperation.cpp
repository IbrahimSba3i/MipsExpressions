#include "AbsOperation.h"

AbsOperation::AbsOperation(const OperationString &source) : Operation(source)
{
	
}

vector<AssemblyInstruction> AbsOperation::getInstructions()
{
	vector<AssemblyInstruction> instructions;
	
	if(source.operands.size() != 1)
		return instructions;
	
	RegistersManager* rm = RegistersManager::getInstance();
	string reg = rm->decodeOperand(source.operands[0]);
	string out = rm->decodeOperand(source.target);
	
	
	string temp = rm->getNextTempRegister();
	instructions.push_back("sra\t" + rm->decodeOperand(temp) +
						   ", " + reg +
						   ", " + Utility::intToString(31));
	instructions.push_back("xor\t" + out +
						   ", " + reg +
						   ", " + rm->decodeOperand(temp));
	instructions.push_back("sub\t" + out +
						   ", " + out +
						   ", " + rm->decodeOperand(temp));
	rm->releaseTempRegister(temp);
	
	return instructions;
}


