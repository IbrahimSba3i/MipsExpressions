#include "MaxOperation.h"

MaxOperation::MaxOperation(const OperationString &source) : Operation(source)
{

}

vector<AssemblyInstruction> MaxOperation::getInstructions()
{
	vector<AssemblyInstruction> instructions;
	RegistersManager* rm = RegistersManager::getInstance();
	LabelsManager* lm = LabelsManager::getInstance();

	if(source.operands.size() != 2) {
		return instructions;
	}

	string firstOperand = source.operands[0];
	string secondOperand = source.operands[1];
	string target = source.target;

	if(rm->isNumber(firstOperand)) {
		if(rm->isNumber(secondOperand)) {
			int val1 = Utility::stringToInt(rm->decodeOperand(firstOperand));
			int val2 = Utility::stringToInt(rm->decodeOperand(secondOperand));
			int val = max(val1, val2);
			loadToRegister(instructions, val, target);
		} else {
			string tempReg = rm->getNextTempRegister();
			string maxEndifLabel = lm->getLabel("max_endif");
			int val = Utility::stringToInt(rm->decodeOperand(firstOperand));
			if(Utility::isBig(val)) {
				if(secondOperand != target) {
					loadToRegister(instructions, val, target);
					instructions.push_back("slt\t" + rm->decodeOperand(tempReg) + ", " + rm->decodeOperand(target) + ", " + rm->decodeOperand(secondOperand));
					instructions.push_back("beq\t" + rm->decodeOperand(tempReg) + ", " + rm->getRegisterZero() + ", " + maxEndifLabel);
					moveToRegister(instructions, secondOperand, target);
				} else {
					string tempReg2 = rm->getNextTempRegister();
					loadToRegister(instructions, val, tempReg);
					instructions.push_back("slt\t" + rm->decodeOperand(tempReg2) + ", " + rm->decodeOperand(target) + ", " + rm->decodeOperand(tempReg));
					instructions.push_back("beq\t" + rm->decodeOperand(tempReg2) + ", " + rm->getRegisterZero() + ", " + maxEndifLabel);
					moveToRegister(instructions, tempReg, target);
					rm->releaseTempRegister(tempReg2);
				}
			} else {
				moveToRegister(instructions, secondOperand, target);
				instructions.push_back("slti\t" + rm->decodeOperand(tempReg) + ", " + rm->decodeOperand(secondOperand) + ", " + Utility::intToString(val));
				instructions.push_back("beq\t" + rm->decodeOperand(tempReg) + ", " + rm->getRegisterZero() + ", " + maxEndifLabel);
				loadToRegister(instructions , val, target);
			}
			AssemblyInstruction::setPendingLabel(maxEndifLabel);
			rm->releaseTempRegister(tempReg);
		}
	} else {
		if(rm->isNumber(secondOperand)) {
			string tempReg = rm->getNextTempRegister();
			string maxEndifLabel = lm->getLabel("max_endif");
			int val = Utility::stringToInt(rm->decodeOperand(secondOperand));
			if(Utility::isBig(val)) {
				if(firstOperand != target) {
					loadToRegister(instructions, val, target);
					instructions.push_back("slt\t" + rm->decodeOperand(tempReg) + ", " + rm->decodeOperand(target) + ", " + rm->decodeOperand(firstOperand));
					instructions.push_back("beq\t" + rm->decodeOperand(tempReg) + ", " + rm->getRegisterZero() + ", " + maxEndifLabel);
					moveToRegister(instructions, firstOperand, target);
				} else {
					string tempReg2 = rm->getNextTempRegister();
					loadToRegister(instructions, val, tempReg);
					instructions.push_back("slt\t" + rm->decodeOperand(tempReg2) + ", " + rm->decodeOperand(target) + ", " + rm->decodeOperand(tempReg));
					instructions.push_back("beq\t" + rm->decodeOperand(tempReg2) + ", " + rm->getRegisterZero() + ", " + maxEndifLabel);
					moveToRegister(instructions, tempReg, target);
					rm->releaseTempRegister(tempReg2);
				}
			} else {
				moveToRegister(instructions, firstOperand, target);
				instructions.push_back("slti\t" + rm->decodeOperand(tempReg) + ", " + rm->decodeOperand(firstOperand) + ", " + Utility::intToString(val));
				instructions.push_back("beq\t" + rm->decodeOperand(tempReg) + ", " + rm->getRegisterZero() + ", " + maxEndifLabel);
				loadToRegister(instructions , val, target);
			}
			AssemblyInstruction::setPendingLabel(maxEndifLabel);
			rm->releaseTempRegister(tempReg);
		} else {
			if(firstOperand == secondOperand) {
				moveToRegister(instructions, firstOperand, target);
			} else {
				if(secondOperand == target) {
					swap(firstOperand, secondOperand);
				}
				if(firstOperand == target) {
					string maxEndifLabel = lm->getLabel("max_endif");
					string tempReg = rm->getNextTempRegister();
					instructions.push_back("slt\t" + rm->decodeOperand(tempReg) + ", " + rm->decodeOperand(target) + ", " + rm->decodeOperand(secondOperand));
					instructions.push_back("beq\t" + rm->decodeOperand(tempReg) + ", " + rm->getRegisterZero() + ", " + maxEndifLabel);
					moveToRegister(instructions, secondOperand, target);
					AssemblyInstruction::setPendingLabel(maxEndifLabel);
					rm->releaseTempRegister(tempReg);
				} else {
					string maxEndifLabel = lm->getLabel("max_endif");
					string tempReg = rm->getNextTempRegister();
					moveToRegister(instructions, firstOperand, target);
					instructions.push_back("slt\t" + rm->decodeOperand(tempReg) + ", " + rm->decodeOperand(target) + ", " + rm->decodeOperand(secondOperand));
					instructions.push_back("beq\t" + rm->decodeOperand(tempReg) + ", " + rm->getRegisterZero() + ", " + maxEndifLabel);
					moveToRegister(instructions, secondOperand, target);
					AssemblyInstruction::setPendingLabel(maxEndifLabel);
					rm->releaseTempRegister(tempReg);
				}
			}
		}
	}

	return instructions;
}


