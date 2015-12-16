#include "ParsingString.h"
#include <stdexcept>

ParsingString::ParsingString()
{
	cursor = 0;
}

ParsingString::ParsingString(const string &source)
{
	cursor = 0;
	this->source = source;
}

char ParsingString::getNext()
{
	if(cursor < source.size())
		return source[cursor++];
	throw std::out_of_range("String is Finished");
}

char ParsingString::peekNext() const
{
	if(cursor < source.size())
		return source[cursor];
	throw std::out_of_range("String is Finished");
}

void ParsingString::moveForward()
{
	if(cursor < source.size())
		cursor++;
}

void ParsingString::moveBackward(int ammount)
{
	if(cursor-ammount >= 0)
		cursor -= ammount;
}

bool ParsingString::isFinished() const
{
	return (cursor == source.size());
}

void ParsingString::setCursor(int cursor)
{
	this->cursor = cursor;
}

int ParsingString::getCursor() const
{
	return cursor;
}

void ParsingString::resetCursor()
{
	cursor = 0;
}

string ParsingString::getSource() const
{
	return source;
}

void ParsingString::setSource(const string &source)
{
	this->source = source;
}
