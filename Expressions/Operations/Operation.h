#ifndef OPERATION_H
#define OPERATION_H
#include <string>
#include <vector>
#include "../OperationString.h"
#include "../../System/RegistersManager.h"
#include "../../System/SettingsManager.h"
#include "../../System/AssemblyInstruction.h"
#include "../../System/LabelsManager.h"

using namespace std;

class Operation
{
public:
	OperationString source;
	Operation(const OperationString& source);
	virtual ~Operation();
	virtual vector<AssemblyInstruction> getInstructions() = 0;
	static void loadToRegister(vector<AssemblyInstruction> &instructions, int val, const string &reg, bool isHex = false);
	static void moveToRegister(vector<AssemblyInstruction> &instructions, const string &source, const string &target);
	bool validateAssignment();
};

#endif // OPERATION_H
