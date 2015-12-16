#include "SettingsPage.h"
#include "ui_SettingsPage.h"

SettingsPage::SettingsPage(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SettingsPage)
{
	ui->setupUi(this);
	settingsManager = SettingsManager::getInstance();

	ui->multCheckBox->setChecked(settingsManager->multiplicationAllowed());
	ui->srlCheckBox->setChecked(settingsManager->shiftRightLogical());
	ui->inlineCheckBox->setChecked(settingsManager->inlineFunctions());
}

SettingsPage::~SettingsPage()
{
	delete ui;
}

void SettingsPage::on_buttonBox_accepted()
{
	settingsManager->setMultiplicationAllowed(ui->multCheckBox->isChecked());
	settingsManager->setShiftRightLogical(ui->srlCheckBox->isChecked());
	settingsManager->setInlineFunctions(ui->inlineCheckBox->isChecked());
}
