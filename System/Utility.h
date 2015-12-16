#ifndef UTILITY_H
#define UTILITY_H
#include <string>
#include <vector>
#include <cctype>
#include <sstream>
#include <stdexcept>
#include <cstdlib>
#include <iostream>
#ifdef QT_VERSION
	#include <QDebug>
	#include <QString>
#endif

using namespace std;

class Utility
{
public:
	static void println(const string &s);
	static void println(int x);
	static void println(unsigned int x);
	static void println(char x);
	static void println(bool x);
	static void println(const char *s);
	static bool isVariableCharacter(char c);
	static bool isVariable(string s);
	static bool isOperatorCharacter(char c);
	static unsigned int upper16(unsigned int x);
	static unsigned int lower16(unsigned int x);
	static bool isDigit(char c, int base = 10);
	static vector<string> stringToVector(const string &s);
	static string intToString(int x);
	static string intToHexString(int x);
	static int stringToInt(string s);
	static string charToString(char c);
	static bool isBig(int val);
	static int ceilDiv(int n, int d);
	static int floorLog(int x, int base = 2);
	static int ceilLog(int x, int base = 2);
	static int intPow(int base, int exp);
	static bool isPowerOfTwo(unsigned int x);
	static int countOnes(unsigned int x);
};

#endif // UTILITY_H
