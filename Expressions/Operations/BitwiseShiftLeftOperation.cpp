#include "BitwiseShiftLeftOperation.h"

BitwiseShiftLeftOperation::BitwiseShiftLeftOperation(const OperationString &source) : Operation(source)
{

}

vector<AssemblyInstruction> BitwiseShiftLeftOperation::getInstructions()
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
			int val = val1 << val2;
			loadToRegister(instructions, val, source.target);
		} else {
			string tempReg = rm->getNextTempRegister();
			int val = Utility::stringToInt(rm->decodeOperand(firstOperand));
			loadToRegister(instructions, val, tempReg);
			instructions.push_back("sllv\t" + rm->decodeOperand(source.target) +
								   ", " + rm->decodeOperand(tempReg) +
								   ", " + rm->decodeOperand(secondOperand));
			rm->releaseTempRegister(tempReg);
		}
	} else {
		if(rm->isNumber(secondOperand)) {
			int val = Utility::stringToInt(rm->decodeOperand(secondOperand));
			if(val > 31) {
				loadToRegister(instructions, 0, source.target);
			} else {
				instructions.push_back("sll\t" + rm->decodeOperand(source.target) +
									   ", " + rm->decodeOperand(firstOperand) +
									   ", " + Utility::intToString(val));
			}
		} else {
			instructions.push_back("sllv\t" + rm->decodeOperand(source.target) +
								   ", " + rm->decodeOperand(firstOperand) +
								   ", " + rm->decodeOperand(secondOperand));
		}
	}
	return instructions;
}


