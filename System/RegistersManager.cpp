#include "RegistersManager.h"

RegistersManager RegistersManager::instance;

RegistersManager::RegistersManager()
{
	initializeRegistersMap();
}

RegistersManager* RegistersManager::getInstance()
{
	return &instance;
}

bool RegistersManager::isNumber(const string& name)
{
	return (name[0] == '-' || Utility::isDigit(name[0]));
}

string RegistersManager::getRegisterZero() const
{
	return "$zero";
}

string RegistersManager::getRegister(string variableName)
{
	if(regMap.count(variableName) != 0)
		return regMap[variableName];
	return "";
}

string RegistersManager::decodeOperand(const string &variableName)
{
	if(variableName[0] == '$') {
		return variableName;
	} else if(isNumber(variableName)) {
		return variableName;
	} else if(isTempRegister(variableName)) {
		return variableName;
	} else {
		return getRegister(variableName);
	}
}

void RegistersManager::addMapping(const string &variableName, const string &registerName)
{
	regMap[variableName] = registerName;
}

string RegistersManager::getNextTempRegister()
{
	for(int i=0; i<AVAILABE_REGISTERS_COUNT; i++) {
		if(tempRegisters[i] == 0) {
			tempRegisters[i] = 1;
			string res = string("$t") + Utility::intToString(i);
			if(TRACE_TEMP_REGISTERS) Utility::println("taken: " + res);
			return res;
		}
	}
	throw invalid_argument("No Available temp registers");
}

bool RegistersManager::isTempRegister(const string& s)
{
	return (s[0] == '$' && s[1] == 't');
}

void RegistersManager::releaseTempRegister(const string& s)
{
	if(TRACE_TEMP_REGISTERS) Utility::println("freed: " + s);
	int index = Utility::stringToInt(s.substr(1));
	tempRegisters[index] = 0;
}

void RegistersManager::clear()
{
	regMap.clear();
	for(int i=0; i<AVAILABE_REGISTERS_COUNT; i++)
		tempRegisters[i] = 0;
	initializeRegistersMap();
}

void RegistersManager::initializeRegistersMap()
{
	regMap["A"] = "$s0";
	regMap["B"] = "$s1";
	regMap["C"] = "$s2";
}
