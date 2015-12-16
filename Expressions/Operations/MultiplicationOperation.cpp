#include "MultiplicationOperation.h"

MultiplicationOperation::MultiplicationOperation(const OperationString &source) : Operation(source)
{

}

vector<AssemblyInstruction> MultiplicationOperation::peformMultiplicationByAddition(string reg, int val) {
	vector<AssemblyInstruction> instructions;
	RegistersManager* rm = RegistersManager::getInstance();
	bool isNegative = val < 0;
	if(isNegative) {
		val = -val;
	}

	bool doneFirst = false;
	string tempReg = rm->getNextTempRegister();
	string tempReg2 = rm->getNextTempRegister();

	int lastTime = Utility::countOnes(val);
	int currentTime = 0;

	for(int shamt = 30; shamt >= 0; shamt--) {
		int p = val >> shamt;
		if(p & 1 == 1) {
			currentTime++;
			if(doneFirst) {
				if(shamt > 0) {
					instructions.push_back("sll\t" + rm->decodeOperand(tempReg) +
										   ", " + rm->decodeOperand(reg) +
										   ", " + Utility::intToString(shamt));
					instructions.push_back("addu\t" + rm->decodeOperand((currentTime == lastTime)? source.target : tempReg2) +
										   ", " + rm->decodeOperand(tempReg2) +
										   ", " + rm->decodeOperand(tempReg));
				} else {
					instructions.push_back("addu\t" + rm->decodeOperand((currentTime == lastTime)? source.target : tempReg2) +
										   ", " + rm->decodeOperand(tempReg2) +
										   ", " + rm->decodeOperand(reg));
				}
			}
			else {
				instructions.push_back("sll\t" + rm->decodeOperand((currentTime == lastTime)? source.target : tempReg2) +
									   ", " + rm->decodeOperand(reg) +
									   ", " + Utility::intToString(shamt));
				doneFirst = true;
			}
		}
	}

	rm->releaseTempRegister(tempReg);
	rm->releaseTempRegister(tempReg2);


	if(isNegative) {
		instructions.push_back("subu\t" + rm->decodeOperand(source.target)
							   + ", " + rm->getRegisterZero()
							   + ", " +  rm->decodeOperand(source.target));
	}

	return instructions;
}

vector<AssemblyInstruction> MultiplicationOperation::peformMultiplicationBySubtraction(string reg, int val) {
	vector<AssemblyInstruction> instructions;
	RegistersManager* rm = RegistersManager::getInstance();
	bool isNegative = val < 0;
	if(isNegative) {
		val = -val;
	}

	int firstLog = Utility::ceilLog(val);
	int firstPow = Utility::intPow(2, firstLog);
	int diff = firstPow - val;

	string tempReg = rm->getNextTempRegister();
	string tempReg2 = rm->getNextTempRegister();

	int lastTime = Utility::countOnes(diff);
	int currentTime = 0;

	instructions.push_back("sll\t" + rm->decodeOperand(tempReg2) +
						   ", " + rm->decodeOperand(reg) +
						   ", " + Utility::intToString(firstLog));
	for(int shamt = 30; shamt >= 0; shamt--) {
		int p = diff >> shamt;
		if(p & 1 == 1) {
			currentTime++;
			if(shamt > 0) {
				instructions.push_back("sll\t" + rm->decodeOperand(tempReg) +
									   ", " + rm->decodeOperand(reg) +
									   ", " + Utility::intToString(shamt));
				if(currentTime == lastTime) {
					instructions.push_back("subu\t" + rm->decodeOperand(source.target) +
										   ", " + rm->decodeOperand(tempReg2) +
										   ", " + rm->decodeOperand(tempReg));
				} else {
					instructions.push_back("subu\t" + rm->decodeOperand(tempReg2) +
										   ", " + rm->decodeOperand(tempReg2) +
										   ", " + rm->decodeOperand(tempReg));
				}
			} else {
				if(currentTime == lastTime) {
					instructions.push_back("subu\t" + rm->decodeOperand(source.target) +
										   ", " + rm->decodeOperand(tempReg2) +
										   ", " + rm->decodeOperand(reg));
				} else {
					instructions.push_back("subu\t" + rm->decodeOperand(tempReg2) +
										   ", " + rm->decodeOperand(tempReg2) +
										   ", " + rm->decodeOperand(reg));
				}
			}
		}
	}

	rm->releaseTempRegister(tempReg);
	rm->releaseTempRegister(tempReg2);

	if(isNegative) {
		instructions.push_back("subu\t" + rm->decodeOperand(source.target)
							   + ", " + rm->getRegisterZero()
							   + ", " +  rm->decodeOperand(source.target));
	}

	return instructions;
}

vector<AssemblyInstruction> MultiplicationOperation::getBestMultiplicationWay(string reg, int val) {
	vector<AssemblyInstruction> instructions;
	RegistersManager* rm = RegistersManager::getInstance();
	SettingsManager* settings = SettingsManager::getInstance();

	if(Utility::isPowerOfTwo(val)) {
		int shamt = Utility::floorLog(val);
		instructions.push_back("sll\t" + rm->decodeOperand(source.target) +
							   ", " + rm->decodeOperand(reg) +
							   ", " + Utility::intToString(shamt));
	} else {
		int ins1 = 2 * Utility::countOnes(abs(val)) - 1 - (abs(val) & 1) + (abs(val) < 0);
		int ins2 = 2 * Utility::countOnes(Utility::intPow(2, Utility::ceilLog(abs(val))) - abs(val)) - (abs(val) & 1) + (abs(val) < 0);
		if(settings->multiplicationAllowed()) {
			int ins3 = 3 + (Utility::isBig(val) && (Utility::lower16(val) != 0));
			if(ins1 <= ins2 && ins1 <= ins3) {
				// ins1 is better
				instructions = peformMultiplicationByAddition(reg, val);
			} else if(ins2 <= ins3) {
				// ins2 is better
				instructions = peformMultiplicationBySubtraction(reg, val);
			} else {
				// ins3 is better
				instructions = peformMultiplicationByLoading(reg, val);
			}
		} else {
			if(ins1 <= ins2) {
				// ins1 is better
				instructions = peformMultiplicationByAddition(reg, val);
			} else {
				// ins2 is better
				instructions = peformMultiplicationBySubtraction(reg, val);
			}
		}
	}
	return instructions;
}

vector<AssemblyInstruction> MultiplicationOperation::addBinaryMultiplicationCode(string firstOperand, string secondOperand) {
	vector<AssemblyInstruction> instructions;
	RegistersManager* rm = RegistersManager::getInstance();
	LabelsManager* lm = LabelsManager::getInstance();

	string temp1 = rm->getNextTempRegister();
	string temp2 = rm->getNextTempRegister();
	string temp3 = rm->getNextTempRegister();

	string t1 = rm->decodeOperand(temp1);
	string t2 = rm->decodeOperand(temp2);
	string t3 = rm->decodeOperand(temp3);

	string r1 = rm->decodeOperand(firstOperand);
	string r2 = rm->decodeOperand(secondOperand);
	string r3 = rm->decodeOperand(source.target);

	string multLoop = lm->getLabel("mult_loop");
	string multEndLoop = lm->getLabel("mult_endloop");
	string multEndIf = lm->getLabel("mult_endif");

	instructions.push_back("addu\t" + r3 + ", " + rm->getRegisterZero() + ", " + rm->getRegisterZero());
	instructions.push_back("beq\t" + r2 + ", " + rm->getRegisterZero() + ", " + multEndLoop);
	instructions.push_back("addu\t" + t2 + ", " + r1 + ", " + rm->getRegisterZero());
	instructions.push_back("addu\t" + t1 + ", " + r2 + ", " + rm->getRegisterZero());
	instructions.push_back("andi\t" + t3 + ", " + t1 + ", " + "1");
	instructions.back().setLabel(multLoop);
	instructions.push_back("beq\t" + t3 + ", " + rm->getRegisterZero() + ", " + multEndIf);
	instructions.push_back("addu\t" + r3 + ", " + r3 + ", " + t2);
	instructions.push_back("sll\t" + t2 + ", " + t2 + ", " + "1");
	instructions.back().setLabel(multEndIf);
	instructions.push_back("srl\t" + t1 + ", " + t1 + ", " + "1");
	instructions.push_back("srl\t" + t1 + ", " + t1 + ", " + "1");
	instructions.push_back("bne\t" + t1 + ", " + rm->getRegisterZero() + ", " + multLoop);
	AssemblyInstruction::setPendingLabel(multEndLoop);

	rm->releaseTempRegister(temp1);
	rm->releaseTempRegister(temp2);
	rm->releaseTempRegister(temp3);

	return instructions;
}

vector<AssemblyInstruction> MultiplicationOperation::peformMultiplicationByLoading(string reg, int val) {
	vector<AssemblyInstruction> instructions;
	RegistersManager* rm = RegistersManager::getInstance();
	string temp = rm->getNextTempRegister();
	loadToRegister(instructions, val, temp);
	instructions.push_back("mult\t" + rm->decodeOperand(reg) +
						   ", " + rm->decodeOperand(temp));
	instructions.push_back("mflo\t" + rm->decodeOperand(source.target));

	rm->releaseTempRegister(temp);
	return instructions;
}

vector<AssemblyInstruction> MultiplicationOperation::getInstructions()
{
	vector<AssemblyInstruction> instructions;
	if(source.operands.size() != 2) {
		return instructions;
	}

	RegistersManager* rm = RegistersManager::getInstance();
	SettingsManager* settings = SettingsManager::getInstance();
	string firstOperand = source.operands[0];
	string secondOperand = source.operands[1];

	if(rm->isNumber(firstOperand)) {
		if(rm->isNumber(secondOperand)) {
			int val1 = Utility::stringToInt(rm->decodeOperand(firstOperand));
			int val2 = Utility::stringToInt(rm->decodeOperand(secondOperand));
			int val = val1 * val2;
			loadToRegister(instructions, val, source.target);
		} else {
			int val = Utility::stringToInt(rm->decodeOperand(firstOperand));
			instructions = getBestMultiplicationWay(secondOperand, val);
		}
	} else {
		if(rm->isNumber(secondOperand)) {
			int val = Utility::stringToInt(rm->decodeOperand(secondOperand));
			instructions = getBestMultiplicationWay(firstOperand, val);
		} else {
			if(settings->multiplicationAllowed()) {
				instructions.push_back("mult\t" + rm->decodeOperand(firstOperand) +
									   ", " + rm->decodeOperand(secondOperand));
				instructions.push_back("mflo\t" + rm->decodeOperand(source.target));
			} else {
				// Perform binary multiplication algorithm
				instructions = addBinaryMultiplicationCode(firstOperand, secondOperand);
			}
		}
	}
}


