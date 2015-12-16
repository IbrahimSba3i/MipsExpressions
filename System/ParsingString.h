#ifndef PARSINGSTRING_H
#define PARSINGSTRING_H
#include <string>

using std::string;

class ParsingString
{
private:
	string source;
	int cursor;
public:
	ParsingString();
	ParsingString(const string& source);
	char getNext();
	char peekNext() const;
	void moveForward();
	void moveBackward(int ammount = 1);
	bool isFinished() const;
	void setCursor(int cursor);
	int getCursor() const;
	void resetCursor();
	string getSource() const;
	void setSource(const string &source);
};

#endif // PARSINGSTRING_H
