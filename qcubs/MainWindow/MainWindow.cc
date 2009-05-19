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
	readSettings();
	setupEditor();
	setupAction();
	setWindowTitle("Qcubs");
	QIcon icon("images/tigrou.jpg");
	setWindowIcon(icon);
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

	ui->splitterEditor->setSizes(QList<int>() << 75 << 25);
	ui->lstError->setVisible(false);
	// TODO: Se souvenir de tout les fichiers ouverts précedemment
	ui->textEdit->loadFile("check/test.mmc");
}

void
MainWindow::setupAction()
{
	connect(ui->actionShowOnlyEditor, SIGNAL(triggered()), this, SLOT(onShowOnlyEditor()));
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
	connect(ui->actionShowEditor, SIGNAL(triggered()), this, SLOT(onShowEditor()));
	connect(ui->actionShowCompileOutput, SIGNAL(triggered()), this, SLOT(onShowCompileOutput()));

	connect(ui->textEdit, SIGNAL(copyAvailable(bool)), ui->actionCut, SLOT(setEnabled(bool)));
	connect(ui->textEdit, SIGNAL(copyAvailable(bool)), ui->actionCopy, SLOT(setEnabled(bool)));

	connect(ui->lstError, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(onLstErrorDoubleClick(int, int)));
	setupActionBuild();
}

void
MainWindow::closeEvent(QCloseEvent* event)
{
	if (ui->textEdit->maybeSave())
	{
		event->accept();
		writeSettings();
	}
	else
		event->ignore();
}

void
MainWindow::readSettings()
{
	QSettings settings("Trolltech", "Application Example");
	QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
	QSize size = settings.value("size", QSize(400, 400)).toSize();
	resize(size);
	move(pos);
}

void
MainWindow::writeSettings()
{
	QSettings settings("Trolltech", "Application Example");
	settings.setValue("pos", pos());
	settings.setValue("size", size());
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
MainWindow::onLstErrorDoubleClick(int x, int)
{
	int line = ui->lstError->item(x, 1)->text().toInt();
	//QMessageBox::about(this, tr("About Application"), msg);
	QTextCursor cur = ui->textEdit->textCursor();
	cur.movePosition(QTextCursor::Start);
	cur.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, line);
	ui->textEdit->setTextCursor(cur);
	ui->textEdit->ensureCursorVisible();
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
	static const QString about =
		"<h3>QCubs 0.2</h3>"
		"<u>Authors:</u>"
		"<ul>"
		"  <li>CptPingu (<a href=\"mailto:cptpingu@gmail.com\">cptpingu@gmail.com</a>)</li>"
		"</ul>"
		"<hr />"
		"<h3>cubs 1.0 </h3>"
		"<u>Authors:</u>"
		"<ul>"
		"  <li>CptPingu (<a href=\"mailto:cptpingu@gmail.com\">cptpingu@gmail.com</a>)</li>"
		"</ul>"
		"<hr />"
		"<h3>Thanks to </h3>"
		"<ul>"
		"  <li>No one yet :p</li>"
		"</ul>"
		"<hr />"
		"Homepage:"
		"<a href=\"http://my-trac.assembla.com/Cubs2\">"
		"  http://my-trac.assembla.com/Cubs2"
		"</a>.";

	QMessageBox::about(this, "About QCubs", about);
}

void
MainWindow::onAboutQt()
{
	QApplication::aboutQt();
}

void
MainWindow::onShowEditor()
{
	ui->textEdit->setVisible(!ui->textEdit->isVisible());
}

void
MainWindow::onShowCompileOutput()
{
	ui->lstError->setVisible(!ui->lstError->isVisible());
}

void
MainWindow::onShowOnlyEditor()
{
	ui->lstError->setVisible(false);
	ui->textEdit->setVisible(true);
	ui->actionShowCompileOutput->setChecked(false);
	ui->actionShowEditor->setChecked(true);
}
