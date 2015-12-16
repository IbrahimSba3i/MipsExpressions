#include "AssemblyCodeBase.h"

AssemblyCodeBase* AssemblyCodeBase::instance = new AssemblyCodeBase();

AssemblyCodeBase::AssemblyCodeBase()
{

}

AssemblyCodeBase *AssemblyCodeBase::getInstance()
{
	return instance;
}

string AssemblyCodeBase::toString()
{
	for(int i=0; i<codeList.size(); i++) {
		for(int k=0; k<codeList[i].instructions.size(); k++) {
			string currentInstruction = codeList[i].instructions[k].getInstruction();
			int ind = 0;
			for(int j=0; j<labelsReplacementMap.size(); j++) {
				string source = labelsReplacementMap[j].first;
				string target = labelsReplacementMap[j].second;
				if((ind = currentInstruction.find(source)) != string::npos) {
					currentInstruction.replace(ind, source.size(), target);
					codeList[i].instructions[k].setInstruction(currentInstruction);
					j = labelsReplacementMap.size();
				}
			}
		}
	}

	string result = "";
	for(int i=0; i<codeList.size(); i++) {
		result += codeList[i].toString() + "\n";
	}
	if(AssemblyInstruction::getPendingLabel() != "") {
		result += AssemblyInstruction::getPendingLabel() + ":\n";
		AssemblyInstruction::setPendingLabel("");
	}
	return result;
}

void AssemblyCodeBase::add(Operation *op)
{
	OperationObject obj;
	obj.source = op->source;
	obj.instructions = op->getInstructions();
	codeList.push_back(obj);
	delete op;
}

void AssemblyCodeBase::clear()
{
	codeList.clear();
	labelsReplacementMap.clear();
	LabelsManager::getInstance()->clear();
	RegistersManager::getInstance()->clear();
}

void AssemblyCodeBase::addLabelsReplacement(string source, string target)
{
	labelsReplacementMap.push_back(make_pair(source, target));
}

bool AssemblyCodeBase::replaceTargetInLast(string originalTarget, string newTarget)
{
	if(codeList.back().source.target == originalTarget) {
		vector<AssemblyInstruction>& A = codeList.back().instructions;
		for(int i=0; i<A.size(); i++) {
			int ind = 0;
			string instruction = A[i].getInstruction();
			if((ind = instruction.find(originalTarget)) != string::npos) {
				instruction.replace(ind, originalTarget.size(), newTarget);
				A[i].setInstruction(instruction);
			}
		}
		return true;
	}
	return false;
}
