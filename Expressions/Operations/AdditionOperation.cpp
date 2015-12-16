#include "AdditionOperation.h"

AdditionOperation::AdditionOperation(const OperationString &source) : Operation(source)
{
	
}

vector<AssemblyInstruction> AdditionOperation::getInstructions()
{
	vector<AssemblyInstruction> instructions;
	if(source.operands.size() != 2) {
		return instructions;
	}
	RegistersManager* rm = RegistersManager::getInstance();
	string firstOperand = source.operands[0];
	string secondOperand = source.operands[1];
	if(rm->isNumber(firstOperand)) {
		if(rm->isNumber(secondOperand)) {
			int firstVal = Utility::stringToInt(rm->decodeOperand(firstOperand));
			int secondVal = Utility::stringToInt(rm->decodeOperand(secondOperand));
			int val = firstVal + secondVal;
			loadToRegister(instructions, val, source.target);
		} else {
			int val = Utility::stringToInt(rm->decodeOperand(firstOperand));
			if(!Utility::isBig(val)) {
				instructions.push_back("addiu\t" + rm->decodeOperand(source.target)
									   + ", " + rm->decodeOperand(secondOperand)
									   + ", " + Utility::intToString(val));	
			} else {
				string tempReg = rm->getNextTempRegister();
				loadToRegister(instructions, val, tempReg);
				instructions.push_back("addu\t" + rm->decodeOperand(source.target)
									   + ", " + rm->decodeOperand(tempReg)
									   + ", " + rm->decodeOperand(secondOperand));
				rm->releaseTempRegister(tempReg);
			}
		}
	} else {
		if(rm->isNumber(secondOperand)) {
			string strval = rm->decodeOperand(secondOperand);
			int val = Utility::stringToInt(strval);
			
			if(!Utility::isBig(val)) {
				instructions.push_back("addiu\t" + rm->decodeOperand(source.target)
									   + ", " + rm->decodeOperand(firstOperand)
									   + ", " + Utility::intToString(val));
			} else {
				string tempReg = rm->getNextTempRegister();
				loadToRegister(instructions, val, tempReg);
				instructions.push_back("addu\t" + rm->decodeOperand(source.target)
									   + ", " + rm->decodeOperand(firstOperand)
									   + ", " + rm->decodeOperand(tempReg));
				rm->releaseTempRegister(tempReg);
			}
		} else {
			instructions.push_back("addu\t" + rm->decodeOperand(source.target)
								   + ", " + rm->decodeOperand(firstOperand)
								   + ", " + rm->decodeOperand(secondOperand));
		}
	}
	
	return instructions;
}
