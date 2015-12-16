#include "LabelsManager.h"

LabelsManager* LabelsManager::instance = new LabelsManager();

LabelsManager::LabelsManager()
{
}

LabelsManager *LabelsManager::getInstance()
{
	return instance;
}

string LabelsManager::getLabel(const string &labelName)
{
	if(labels.count(labelName)) {
		labels[labelName]++;
	} else {
		labels[labelName] = 1;
	}
	return labelName + "_" + Utility::intToString(labels[labelName]);
}

void LabelsManager::clear()
{
	labels.clear();
}
