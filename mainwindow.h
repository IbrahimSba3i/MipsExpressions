#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include "Expressions/ExpressionParser.h"
#include "mipstexthighlighter.h"
#include "SettingsPage.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void on_pushButton_clicked();

	void on_actionSettings_triggered();

private:
	Ui::MainWindow *ui;
	MipsTextHighlighter *highlighter;
	SettingsPage* settingsPage;
};

#endif // MAINWINDOW_H
