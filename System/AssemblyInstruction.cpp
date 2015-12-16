#include "AssemblyInstruction.h"
#include "AssemblyCodeBase.h"

string AssemblyInstruction::pendingLabel = "";

AssemblyInstruction::AssemblyInstruction()
{
	label = pendingLabel;
	pendingLabel = "";
}

AssemblyInstruction::AssemblyInstruction(string instruction)
{
	this->instruction = instruction;
	label = pendingLabel;
	pendingLabel = "";

}

string AssemblyInstruction::toString() const
{
	if(label == "") {
		return "    " + instruction;
	} else {
		return label + ":\n    " + instruction;
	}
}

void AssemblyInstruction::setPendingLabel(string s)
{
	pendingLabel = s;
}

string AssemblyInstruction::getPendingLabel() {
	return pendingLabel;
}

string AssemblyInstruction::getInstruction() const
{
	return instruction;
}

void AssemblyInstruction::setInstruction(const string &value)
{
	instruction = value;
}

string AssemblyInstruction::getLabel() const
{
	return label;
}

void AssemblyInstruction::setLabel(const string &value)
{
	if(label.size() != 0) {
		AssemblyCodeBase* codeBase = AssemblyCodeBase::getInstance();
		codeBase->addLabelsReplacement(value, label);
	}
	else {
		label = value;
	}
}

string AssemblyInstruction::getComment() const
{
	return comment;
}

void AssemblyInstruction::setComment(const string &value)
{
	comment = value;
}

