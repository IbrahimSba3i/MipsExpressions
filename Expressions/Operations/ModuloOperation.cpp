#include "ModuloOperation.h"

ModuloOperation::ModuloOperation(const OperationString &source) : Operation(source)
{

}


void ModuloOperation::addDivisionCode(vector<AssemblyInstruction>& instructions, const string& num, const string& den,
										bool firstIsNum, bool secondIsNum, int numericalValue)
{
	RegistersManager* rm = RegistersManager::getInstance();
	LabelsManager* lm = LabelsManager::getInstance();

	string tempReg0 = rm->getNextTempRegister();
	string tempReg1 = rm->getNextTempRegister();
	string tempReg2 = firstIsNum? num : rm->getNextTempRegister();
	string tempReg3 = rm->getNextTempRegister();
	string tempReg4 = secondIsNum? den : rm->getNextTempRegister();

	string s0 = rm->decodeOperand(num);
	string s1 = rm->decodeOperand(den);
	string s2 = rm->decodeOperand(tempReg0);
	string s3 = rm->decodeOperand(source.target);
	string t0 = rm->decodeOperand(tempReg1);
	string t1 = rm->decodeOperand(tempReg2);
	string t2 = rm->decodeOperand(tempReg3);
	string t3 = rm->decodeOperand(tempReg4);

	string divEndIfLabel = lm->getLabel("div_endif");
	string divLoopLabel = lm->getLabel("div_loop");

	instructions.push_back("addiu\t" + s2 + ", " + rm->getRegisterZero() + ", " + "0");
	instructions.push_back("addiu\t" + s3 + ", " + rm->getRegisterZero() + ", " + "0");
	instructions.push_back("lui\t"   + t0 + ", " + "0x8000");
	if(!firstIsNum) {
		instructions.push_back("sra\t"  + t2 + ", " + s0 + ", " + "31");
		instructions.push_back("xor\t"  + t1 + ", " + s0 + ", " + t2);
		instructions.push_back("subu\t" + t1 + ", " + t1 + ", " + t2);
	}
	if(!secondIsNum) {
		instructions.push_back("sra\t"  + t2 + ", " + s1 + ", " + "31");
		instructions.push_back("xor\t"  + t3 + ", " + s1 + ", " + t2);
		instructions.push_back("subu\t" + t3 + ", " + t3 + ", " + t2);
	}
	instructions.push_back("sll\t"   + s3 + ", " + s3 + ", " + "1");
	instructions.back().setLabel(divLoopLabel);
	instructions.push_back("slt\t"   + t2 + ", " + t1 + ", " + rm->getRegisterZero());
	instructions.push_back("or\t"    + s3 + ", " + s3 + ", " + t2);
	instructions.push_back("slt\t"   + t2 + ", " + s3 + ", " + t3);
	instructions.push_back("bne\t"   + t2 + ", " + rm->getRegisterZero() + ", " + divEndIfLabel);
	instructions.push_back("subu\t"  + s3 + ", " + s3 + ", " + t3);
	instructions.push_back("or\t"    + s2 + ", " + s2 + ", " + t0);
	instructions.push_back("srl\t"   + t0 + ", " + t0 + ", " + "1");
	instructions.back().setLabel(divEndIfLabel);
	instructions.push_back("sll\t"   + t1 + ", " + t1 + ", " + "1");
	instructions.push_back("bne\t"   + t0 + ", " + rm->getRegisterZero() + ", " + divLoopLabel);

	if(firstIsNum) {
		if(numericalValue < 0) {
			instructions.push_back("subu\t" + s3 + ", " + rm->getRegisterZero() + ", " + s3);
		}
	} else {
		string divEndNegCond = lm->getLabel("div_endnegcond");
		instructions.push_back("slt\t" + t2 + ", " + s0 + ", " + rm->getRegisterZero());
		instructions.push_back("beq\t" + t2 + ", " + rm->getRegisterZero() + ", " + divEndNegCond);
		instructions.push_back("subu\t" + s3 + ", " + rm->getRegisterZero() + ", " + s3);
		AssemblyInstruction::setPendingLabel(divEndNegCond);
	}


	rm->releaseTempRegister(tempReg0);
	rm->releaseTempRegister(tempReg1);
	if(!firstIsNum) rm->releaseTempRegister(tempReg2);
	rm->releaseTempRegister(tempReg3);
	if(!secondIsNum) rm->releaseTempRegister(tempReg4);
}

void ModuloOperation::divideNumbers(vector<AssemblyInstruction>& instructions, const string& num, const string& den,
									  bool firstIsNum, bool secondIsNum, int numericalValue)
{
	SettingsManager* settings = SettingsManager::getInstance();
	RegistersManager* rm = RegistersManager::getInstance();

	if(settings->multiplicationAllowed()) {
		instructions.push_back("div\t" + rm->decodeOperand(num) +
							   ", " + rm->decodeOperand(den));
		instructions.push_back("mfhi\t" + rm->decodeOperand(source.target));
	} else {
		addDivisionCode(instructions, num, den, firstIsNum, secondIsNum, numericalValue);
	}
}

vector<AssemblyInstruction> ModuloOperation::getInstructions()
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
			int val1 = Utility::stringToInt(rm->decodeOperand(firstOperand));
			int val2 = Utility::stringToInt(rm->decodeOperand(secondOperand));
			int val = val1 % val2;
			loadToRegister(instructions, val, source.target);
		} else {
			int val = Utility::stringToInt(rm->decodeOperand(firstOperand));
			string tempReg = rm->getNextTempRegister();
			loadToRegister(instructions, abs(val), tempReg);
			divideNumbers(instructions, tempReg, secondOperand, true, false, val);
			rm->releaseTempRegister(tempReg);
		}
	} else {
		if(rm->isNumber(secondOperand)) {
			int val = Utility::stringToInt(rm->decodeOperand(secondOperand));
			if(Utility::isPowerOfTwo(abs(val))) {
				string tempReg = rm->getNextTempRegister();
				string t0 = rm->decodeOperand(tempReg);
				string s0 = rm->decodeOperand(firstOperand);
				string v0 = rm->decodeOperand(source.target);
				LabelsManager* lm = LabelsManager::getInstance();
				string divSkipNeg = lm->getLabel("div_skipneg");
				string divEndIf = lm->getLabel("div_endif");
				instructions.push_back("slt\t" + t0 + ", " + s0 + ", " + rm->getRegisterZero());
				instructions.push_back("beq\t" + t0 + ", " + rm->getRegisterZero() + ", " + divSkipNeg);
				instructions.push_back("subu\t" + v0 + ", " + rm->getRegisterZero() + ", " + s0);
				instructions.push_back("andi\t" + v0 + ", " + v0 + ", " + Utility::intToHexString(abs(val) - 1));
				instructions.push_back("subu\t" + v0 + ", " + rm->getRegisterZero() + ", " + v0);
				instructions.push_back("j\t" + divEndIf);
				instructions.push_back("andi\t" + v0 + ", " + s0 + ", " + Utility::intToHexString(abs(val) - 1));
				instructions.back().setLabel(divSkipNeg);
				AssemblyInstruction::setPendingLabel(divEndIf);
				rm->releaseTempRegister(tempReg);
			} else {
				int val = Utility::stringToInt(rm->decodeOperand(secondOperand));
				string tempReg = rm->getNextTempRegister();
				loadToRegister(instructions, abs(val), tempReg);
				divideNumbers(instructions, firstOperand, tempReg, false, true, val);
				rm->releaseTempRegister(tempReg);
			}
		} else {
			divideNumbers(instructions, firstOperand, secondOperand, false, false, 0);
		}
	}

	return instructions;
}



