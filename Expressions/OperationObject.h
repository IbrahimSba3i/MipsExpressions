#ifndef OPERATIONOBJECT_H
#define OPERATIONOBJECT_H
#include "../System/AssemblyInstruction.h"
#include <vector>
#include "OperationString.h"

using namespace std;

class OperationObject
{
public:
	OperationObject();
	vector<AssemblyInstruction> instructions;
	OperationString source;

	string toString();
};

#endif // OPERATIONOBJECT_H
