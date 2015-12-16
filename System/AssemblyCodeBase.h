#ifndef ASSEMBLYCODEBASE_H
#define ASSEMBLYCODEBASE_H
#include <vector>
#include <string>
#include "AssemblyInstruction.h"
#include "../Expressions/Operations/Operation.h"
#include "../Expressions/OperationObject.h"
using namespace std;

class AssemblyCodeBase
{
	vector<pair<string, string> > labelsReplacementMap;
	vector<OperationObject> codeList;
	AssemblyCodeBase();
	static AssemblyCodeBase* instance;
public:
	static AssemblyCodeBase *getInstance();
	string toString();
	void add(Operation *op);
	void clear();

	void addLabelsReplacement(string source, string target);
	bool replaceTargetInLast(string originalTarget, string newTarget);
};

#endif // ASSEMBLYCODEBASE_H
