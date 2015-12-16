#include "SettingsManager.h"

SettingsManager* SettingsManager::instance = new SettingsManager();

SettingsManager::SettingsManager()
{
	settings = new QSettings("AssemblyParse.ini", QSettings::IniFormat);
}

SettingsManager::~SettingsManager()
{
	delete settings;
}

SettingsManager *SettingsManager::getInstance()
{
	return instance;
}

bool SettingsManager::multiplicationAllowed() const
{
	if(!settings->contains("multiplication_allowed")) {
		settings->setValue("multiplication_allowed", true);
	}
	return settings->value("multiplication_allowed").toBool();
}

bool SettingsManager::shiftRightLogical() const
{
	if(!settings->contains("shift_right_logical")) {
		settings->setValue("shift_right_logical", false);
	}
	return settings->value("shift_right_logical").toBool();
}

bool SettingsManager::inlineFunctions() const
{
	if(!settings->contains("inline_functions")) {
		settings->setValue("inline_functions", true);
	}
	return settings->value("inline_functions").toBool();
}

void SettingsManager::setMultiplicationAllowed(bool val)
{
	settings->setValue("multiplication_allowed", val);
}

void SettingsManager::setShiftRightLogical(bool val)
{
	settings->setValue("shift_right_logical", val);
}

void SettingsManager::setInlineFunctions(bool val)
{
	settings->setValue("inline_functions", val);
}
