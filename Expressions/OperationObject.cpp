#include "OperationObject.h"

OperationObject::OperationObject()
{
}

string OperationObject::toString()
{
	string result = "";
	for(int i=0; i<instructions.size(); i++) {
		result += instructions[i].toString() + "\n";
	}

	return result;
}
