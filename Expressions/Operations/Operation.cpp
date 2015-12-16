#include "Operation.h"

Operation::Operation(const OperationString &source)
{
	this->source = source;
}

Operation::~Operation()
{

}

bool Operation::validateAssignment() {
	RegistersManager* rm = RegistersManager::getInstance();

	if(source.operands.size() != 2) {
		return false;
	}
	string operand = source.operands[0];
	if(rm->isTempRegister(operand) || rm->isNumber(operand)) {
		return false;
	}

	if(operand != source.target) {
		return false;
	}

	return true;
}

void Operation::loadToRegister(vector<AssemblyInstruction> &instructions, int val, const string& reg, bool isHex) {
	RegistersManager* rm = RegistersManager::getInstance();
	if(Utility::isBig(val)) {
		instructions.push_back("lui\t" + rm->decodeOperand(reg) +
							   ", " + (isHex? Utility::intToHexString(Utility::upper16(val)) : Utility::intToString(Utility::upper16(val))));
		if(Utility::lower16(val) != 0) {
			instructions.push_back("ori\t" + rm->decodeOperand(reg) +
								   ", " + rm->decodeOperand(reg) +
								   ", " + (isHex? Utility::intToHexString(Utility::lower16(val)) : Utility::intToString(Utility::lower16(val))));
		}
	} else {
		instructions.push_back("addiu\t" + rm->decodeOperand(reg) +
							   ", " + rm->getRegisterZero() +
							   ", " + (isHex? Utility::intToHexString(val) : Utility::intToString(val)));
	}
}

void Operation::moveToRegister(vector<AssemblyInstruction> &instructions, const string& source, const string& target) {
	RegistersManager* rm = RegistersManager::getInstance();
	instructions.push_back("addu\t" + rm->decodeOperand(target) + ", " + rm->decodeOperand(source) + ", " + "0");
}
