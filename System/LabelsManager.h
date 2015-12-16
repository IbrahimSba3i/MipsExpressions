#ifndef LABELSMANAGER_H
#define LABELSMANAGER_H
#include <map>
#include <string>
#include <vector>
#include "Utility.h"

using namespace std;

class LabelsManager
{
private:
	map<string, int> labels;
	LabelsManager();
	static LabelsManager* instance;
public:
	static LabelsManager* getInstance();
	string getLabel(const string& labelName);
	void clear();
};

#endif // LABELSMANAGER_H
