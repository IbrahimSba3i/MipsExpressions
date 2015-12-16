#ifndef REGISTERSMANAGER_H
#define REGISTERSMANAGER_H
#include <map>
#include <string>
#include <stdexcept>
#include "Utility.h"
using namespace std;

#define AVAILABE_REGISTERS_COUNT 10
#define TRACE_TEMP_REGISTERS 0

class RegistersManager
{
private:
	RegistersManager();
	static RegistersManager instance;
	bool tempRegisters[AVAILABE_REGISTERS_COUNT];
	map<string, string> regMap;
public:
	static RegistersManager* getInstance();
	bool isNumber(const string& name);
	string decodeOperand(const string& variableName);
	void addMapping(const string& variableName, const string& registerName);
	string getNextTempRegister();
	bool isTempRegister(const string &s);
	void releaseTempRegister(const string &s);
	void clear();
	void initializeRegistersMap();
	string getRegisterZero() const;
	string getRegister(string variableName);
};

#endif // REGISTERSMANAGER_H
