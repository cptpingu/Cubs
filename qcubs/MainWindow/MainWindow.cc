#include <QMessageBox>
#include "MainWindow.hh"
#include "ui_MainWindow.h"

/*!
** Just a comment
** @param test
** @return pouet
*/
MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::MainWindow), _dialogWait(parent)
{
	ui->setupUi(this);
	setupEditor();
	setupAction();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void
MainWindow::setupEditor()
{
	ui->actionCut->setEnabled(false);
	ui->actionCopy->setEnabled(false);

	// TODO: Se souvenir de tout les fichiers ouverts précedemment
	ui->textEdit->loadFile("check/test.mmc");
}

void
MainWindow::setupAction()
{
	connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(onOpen()));
	connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(onNew()));
	connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(onSave()));
	connect(ui->actionSaveAs, SIGNAL(triggered()), this, SLOT(onSaveAs()));
	connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(onExit()));
	connect(ui->actionCut, SIGNAL(triggered()), this, SLOT(onCut()));
	connect(ui->actionCopy, SIGNAL(triggered()), this, SLOT(onCopy()));
	connect(ui->actionPaste, SIGNAL(triggered()), this, SLOT(onPaste()));
	connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(onAbout()));
	connect(ui->actionAboutQt, SIGNAL(triggered()), this, SLOT(onAboutQt()));

	// Bind to current textEdit
	connect(ui->textEdit, SIGNAL(copyAvailable(bool)), ui->actionCut, SLOT(setEnabled(bool)));
	connect(ui->textEdit, SIGNAL(copyAvailable(bool)), ui->actionCopy, SLOT(setEnabled(bool)));
	setupActionBuild();
}

void
MainWindow::onOpen()
{
	if (ui->textEdit->open())
		statusBar()->showMessage(tr("File loaded"), 2000);
}

void
MainWindow::onClose()
{
	// Close a tabulation
}

void
MainWindow::onNew()
{
	ui->textEdit->newFile();
}

void
MainWindow::onSave()
{
	if (ui->textEdit->save())
		statusBar()->showMessage(tr("File saved"), 2000);
}

void
MainWindow::onSaveAs()
{
	ui->textEdit->saveAs();
}

void
MainWindow::onExit()
{
	close();
}

void
MainWindow::onCut()
{
	ui->textEdit->cut();
}

void
MainWindow::onCopy()
{
	ui->textEdit->copy();
}

void
MainWindow::onPaste()
{
	ui->textEdit->paste();
}

void
MainWindow::onAbout()
{
}

void
MainWindow::onAboutQt()
{
	QApplication::aboutQt();
}
