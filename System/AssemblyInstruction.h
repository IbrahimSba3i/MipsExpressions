#ifndef ASSEMBLYINSTRUCTION_H
#define ASSEMBLYINSTRUCTION_H

#include <string>
#include <vector>

using namespace std;

class AssemblyInstruction
{
	string instruction;
	string label;
	string comment;
	static string pendingLabel;
public:
	AssemblyInstruction();
	AssemblyInstruction(string instruction);

	string toString() const;

	static void setPendingLabel(string s);
	static string getPendingLabel();

	string getInstruction() const;
	void setInstruction(const string &value);
	string getLabel() const;
	void setLabel(const string &value);
	string getComment() const;
	void setComment(const string &value);
};

#endif // ASSEMBLYINSTRUCTION_H
