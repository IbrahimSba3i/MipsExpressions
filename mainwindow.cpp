#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	this->setWindowTitle("Expression Converter");
	highlighter = NULL;
}

MainWindow::~MainWindow()
{
	if(highlighter != NULL) {
		delete highlighter;
	}
	delete ui;
}

void MainWindow::on_pushButton_clicked()
{
	AssemblyCodeBase* codeBase = AssemblyCodeBase::getInstance();
	ExpressionParser parser(ui->lineEdit->text().toStdString());
	try {
		codeBase->clear();
		parser.parse();

		ui->textEdit->setPlainText(QString::fromStdString(codeBase->toString()));
		QFont font;
		font.setFamily("Courier");
		font.setFixedPitch(true);
		font.setPointSize(8);

		ui->textEdit->setFont(font);
		if(highlighter != NULL) {
			delete highlighter;
		}
		highlighter = new MipsTextHighlighter(ui->textEdit->document());

		highlighter->rehighlight();

	} catch(exception& e) {
		ui->textEdit->setText(QString::fromStdString(std::string("Error: ") + e.what()));
	} catch(...) {
		ui->textEdit->setText(QString::fromStdString(std::string("Error")));
	}
}

void MainWindow::on_actionSettings_triggered()
{
	settingsPage = new SettingsPage(this);
	settingsPage->show();
}
