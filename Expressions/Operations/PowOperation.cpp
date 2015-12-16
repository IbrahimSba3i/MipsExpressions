#include "PowOperation.h"

PowOperation::PowOperation(const OperationString &source) : Operation(source)
{

}

void PowOperation::addPowCode(vector<AssemblyInstruction>& instructions, string base, string exp, string target)
{
	RegistersManager* rm = RegistersManager::getInstance();
	LabelsManager* lm = LabelsManager::getInstance();

	string powEndLabel = lm->getLabel("pow_end");
	string powLoopLabel = lm->getLabel("pow_loop");
	string powEndIfLabel = lm->getLabel("pow_endif");

	string temp0 = rm->getNextTempRegister();
	string temp1 = rm->getNextTempRegister();
	string temp2 = rm->getNextTempRegister();

	string s0 = rm->decodeOperand(base);
	string s1 = rm->decodeOperand(exp);
	string s2 = rm->decodeOperand(target);
	string t0 = rm->decodeOperand(temp0);
	string t1 = rm->decodeOperand(temp1);
	string t2 = rm->decodeOperand(temp2);


	instructions.push_back("addiu\t" + t0 + ", " + s0 + ", " + "0");
	instructions.push_back("addiu\t" + t1 + ", " + s1 + ", " + "0");
	instructions.push_back("addiu\t" + s2 + ", " + rm->getRegisterZero() + ", " + "1");
	instructions.push_back("slt\t"   + t2 + ", " + t1 + ", " + rm->getRegisterZero());
	instructions.push_back("beq\t"   + t2 + ", " + rm->getRegisterZero() + ", " + powLoopLabel);
	instructions.push_back("beq\t"   + t0 + ", " + s2 + ", " + powEndLabel);
	instructions.push_back("addiu\t" + s2 + ", " + rm->getRegisterZero() + ", " + "0");
	instructions.push_back("j\t"     + powEndLabel);
	instructions.push_back("beq\t"   + t1 + ", " + rm->getRegisterZero() + ", " + powEndLabel);
	instructions.back().setLabel(powLoopLabel);
	instructions.push_back("andi\t"  + t2 + ", " + t1 + ", " + "1");
	instructions.push_back("beq\t"   + t2 + ", " + rm->getRegisterZero() + ", " + powEndIfLabel);
	multiplyNumbers(instructions, s2, t0, s2);
	instructions.push_back("srl\t"   + t1 + ", " + t1 + ", " + "1");
	instructions.back().setLabel(powEndIfLabel);
	multiplyNumbers(instructions, t0, t0, t0);
	instructions.push_back("j\t"     + powLoopLabel);
	AssemblyInstruction::setPendingLabel(powEndLabel);

	rm->releaseTempRegister(temp0);
	rm->releaseTempRegister(temp1);
	rm->releaseTempRegister(temp2);
}

void PowOperation::multiplyNumbers(vector<AssemblyInstruction>& instructions, string first, string second, string target)
{
	vector<string> operands;
	operands.push_back(first);
	operands.push_back(second);
	MultiplicationOperation* operation = new MultiplicationOperation(OperationString(target, "*", operands));
	vector<AssemblyInstruction> multiplicationsInstructions = operation->getInstructions();
	instructions.insert(instructions.end(), multiplicationsInstructions.begin(), multiplicationsInstructions.end());
}

vector<AssemblyInstruction> PowOperation::getInstructions()
{
	vector<AssemblyInstruction> instructions;

	if(source.operands.size() != 2)
		return instructions;

	RegistersManager* rm = RegistersManager::getInstance();

	string firstOperand = source.operands[0];
	string secondOperand = source.operands[1];
	string target = source.target;

	if(rm->isNumber(firstOperand)) {
		if(rm->isNumber(secondOperand)) {
			int val1 = Utility::stringToInt(rm->decodeOperand(firstOperand));
			int val2 = Utility::stringToInt(rm->decodeOperand(secondOperand));
			int val = Utility::intPow(val1, val2);
			loadToRegister(instructions, val, target);
		} else {
			int val = Utility::stringToInt(rm->decodeOperand(firstOperand));
			string tempReg = rm->getNextTempRegister();
			loadToRegister(instructions, val, tempReg);
			addPowCode(instructions, tempReg, secondOperand, target);
			rm->releaseTempRegister(tempReg);
		}
	} else {
		if(rm->isNumber(secondOperand)) {
			int val = Utility::stringToInt(rm->decodeOperand(secondOperand));
			if(Utility::isPowerOfTwo(val)) {
				int x = Utility::floorLog(val);
				for(int i=0; i<x; i++) {
					if(i == 0) {
						multiplyNumbers(instructions, firstOperand, firstOperand, target);
					} else {
						multiplyNumbers(instructions, target, target, target);
					}
				}
			} else {
				string tempReg = rm->getNextTempRegister();
				loadToRegister(instructions, val, tempReg);
				addPowCode(instructions, firstOperand, tempReg, target);
				rm->releaseTempRegister(tempReg);
			}
		} else {
			addPowCode(instructions, firstOperand, secondOperand, target);
		}
	}

	return instructions;
}


