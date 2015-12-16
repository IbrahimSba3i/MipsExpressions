#include "BitwiseXorOperation.h"

BitwiseXorOperation::BitwiseXorOperation(const OperationString &source) : Operation(source)
{

}

void BitwiseXorOperation::performImmediate(vector<AssemblyInstruction>& instructions, const string& target, const string& reg, int val)
{
	RegistersManager* rm = RegistersManager::getInstance();
	if(Utility::isBig(val)) {
		string temp = rm->getNextTempRegister();
		loadToRegister(instructions, val, temp, true);

		instructions.push_back("xor\t" + rm->decodeOperand(target) +
							   ", " + rm->decodeOperand(reg) +
							   ", " + rm->decodeOperand(temp));
		rm->releaseTempRegister(temp);
	} else {
		instructions.push_back("xori\t" + rm->decodeOperand(target) +
							   ", " + rm->decodeOperand(reg) +
							   ", " + Utility::intToHexString(val));
	}
}

vector<AssemblyInstruction> BitwiseXorOperation::getInstructions()
{
	vector<AssemblyInstruction> instructions;
	RegistersManager* rm = RegistersManager::getInstance();

	if(source.operands.size() != 2) {
		return instructions;
	}

	string firstOperand = source.operands[0];
	string secondOperand = source.operands[1];

	if(rm->isNumber(firstOperand)) {
		if(rm->isNumber(secondOperand)) {
			int val1 = Utility::stringToInt(rm->decodeOperand(firstOperand));
			int val2 = Utility::stringToInt(rm->decodeOperand(secondOperand));
			int val = val1 ^ val2;
			loadToRegister(instructions, val, source.target, true);
		} else {
			int val = Utility::stringToInt(rm->decodeOperand(firstOperand));
			performImmediate(instructions, source.target, secondOperand, val);
		}
	} else {
		if(rm->isNumber(secondOperand)) {
			int val = Utility::stringToInt(rm->decodeOperand(secondOperand));
			performImmediate(instructions, source.target, firstOperand, val);
		} else {
			instructions.push_back("xor\t" + rm->decodeOperand(source.target) +
								   ", " + rm->decodeOperand(firstOperand) +
								   ", " + rm->decodeOperand(secondOperand));
		}
	}

	return instructions;
}


