#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H
#include <QSettings>

class SettingsManager
{
private:
	SettingsManager();
	~SettingsManager();
	static SettingsManager* instance;
	QSettings* settings;
public:

	static SettingsManager *getInstance();
	bool multiplicationAllowed() const;
	bool shiftRightLogical() const;
	bool inlineFunctions() const;
	void setMultiplicationAllowed(bool val);
	void setShiftRightLogical(bool val);
	void setInlineFunctions(bool val);
};

#endif // SETTINGSMANAGER_H
