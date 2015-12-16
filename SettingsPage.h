#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include <QDialog>
#include "System/SettingsManager.h"

namespace Ui {
class SettingsPage;
}

class SettingsPage : public QDialog
{
	Q_OBJECT

public:
	explicit SettingsPage(QWidget *parent = 0);
	~SettingsPage();

private slots:
	void on_buttonBox_accepted();

private:
	Ui::SettingsPage *ui;
	SettingsManager* settingsManager;
};

#endif // SETTINGSPAGE_H
