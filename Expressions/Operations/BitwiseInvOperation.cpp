#include "BitwiseInvOperation.h"

BitwiseInvOperation::BitwiseInvOperation(const OperationString &source) : Operation(source)
{
	
}

vector<AssemblyInstruction> BitwiseInvOperation::getInstructions()
{
	vector<AssemblyInstruction> instructions;
	RegistersManager* rm = RegistersManager::getInstance();
	string src = source.operands[0];
	string out = source.target;
	if(rm->isNumber(src)) {
		int val = ~Utility::stringToInt(rm->decodeOperand(src));
		if(Utility::isBig(val)) {
			instructions.push_back("lui\t" + rm->decodeOperand(out) + 
								   ", " + Utility::intToString((unsigned int)(val) >> 16));
			instructions.push_back("ori\t" + rm->decodeOperand(out) + 
								   ", " + rm->decodeOperand(out) + 
								   ", " + Utility::intToString(val & 0xffff));
		} else {
			instructions.push_back("ori\t" + rm->decodeOperand(out) + 
								   ", " + rm->getRegisterZero() + 
								   ", " + Utility::intToString(val));
		}
	} else {
		instructions.push_back("nor\t" + rm->decodeOperand(out) + 
							   ", " + rm->decodeOperand(src) + 
							   ", " + rm->getRegisterZero());
	}
	
	return instructions;
}


