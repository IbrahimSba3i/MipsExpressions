#include "Utility.h"


void Utility::println(const char* s) {
	println(string(s));
}

void Utility::println(const string &s) {
#ifdef QT_VERSION
	qDebug() << QString::fromStdString(s);
#else
	cout << "\"" << s << "\"" << endl;
#endif
}


void Utility::println(int x) {
#ifdef QT_VERSION
	qDebug() << x;
#else
	cout << x << endl;
#endif
}

void Utility::println(unsigned int x) {
#ifdef QT_VERSION
	qDebug() << x;
#else
	cout << x << endl;
#endif
}

void Utility::println(char x) {
#ifdef QT_VERSION
	qDebug() << x;
#else
	cout << x << endl;
#endif
}


void Utility::println(bool x) {
#ifdef QT_VERSION
	qDebug() << (x? "true":"false");
#else
	cout << (x? "true":"false") << endl;
#endif
}

bool Utility::isVariableCharacter(char c) {
	return (c == '_' || isalpha(c));
}

bool Utility::isVariable(string s) {
	if(s.size() == 0) return false;
	char c = s[0];
	if(!isVariableCharacter(c)) return false;
	for(int i=1; i<s.size(); i++) {
		if(!isVariableCharacter(s[i]) && ! isDigit(s[i], 10)) {
			return false;
		}
	}
	return true;
}

bool Utility::isOperatorCharacter(char c)
{
	string operators = "+-*/%=()&^!~|,<>[]{}#@$`";
	return (operators.find(c) != string::npos);
}

unsigned int Utility::upper16(unsigned int x) {
	return (x >> 16);
}

unsigned int Utility::lower16(unsigned int x) {
	return (x & 0xffff);
}

bool Utility::isDigit(char c, int base) {
	if(base <= 10) {
		return (c >= '0' && c < '0' + base);
	} else if(base <= 36) {
		if(isalpha(c)) c = tolower(c);
		return ((c >= '0' && c <= '9') || (c >= 'a' && c < (base - 10 + 'a')));
	} else {
		throw invalid_argument("Unkown base");
	}
}

vector<string> Utility::stringToVector(const string &s) {
	vector<string> v;
	v.push_back(s);
	return v;
}

string Utility::intToString(int x) {
	stringstream ss;
	ss << x;
	return ss.str();
}

string Utility::intToHexString(int x) {
	stringstream ss;
	ss << "0x" << std::hex << x;
	return ss.str();
}

int Utility::stringToInt(string s) {
	return atoi(s.c_str());
}

string Utility::charToString(char c) {
	return string("") + c;
}

bool Utility::isBig(int val) {
	return (val > 32767 || val < -32769);
}

int Utility::ceilDiv(int n, int d) {
	return (n + d - 1)/d;
}

int Utility::floorLog(int x, int base) {
	if(x <= 0) throw invalid_argument("log argument is not positive");
	if(x == 1) return 0;
	return 1 + floorLog(x / base, base);
}

int Utility::ceilLog(int x, int base) {
	if(x <= 0) throw invalid_argument("log argument is not positive");
	if(x == 1) return 0;
	return 1 + ceilLog(ceilDiv(x, base), base);
}

int Utility::intPow(int base, int exp) {
	if(exp < 0)
		return (base == 1 && exp == -1);

	int result = 1;
	while (exp != 0) {
		if (exp & 1 == 1)
			result *= base;
		exp >>= 1;
		base *= base;
	}

	return result;
}

bool Utility::isPowerOfTwo(unsigned int x) {
	return ((x & (x-1)) == 0);
}

int Utility::countOnes(unsigned int x) {
	int val = 0;
	while(x != 0) {
		val += x & 1;
		x >>= 1;
	}
	return val;
}
