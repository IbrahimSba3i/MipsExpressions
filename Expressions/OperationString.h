#ifndef OPERATION_STRING_H
#define OPERATION_STRING_H
#include <string>
#include <vector>

using namespace std;

class OperationString
{
public:
	string target;
	vector<string> operands;
	string operation;
	
	OperationString();
	OperationString(const string&target, const string& operation, const vector<string>& operands);
	string toString() const;
};

#endif // OPERATION_STRING_H
