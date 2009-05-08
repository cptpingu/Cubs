#include "MainWindow.hh"
#include "ui_MainWindow.h"
#include <QMessageBox>

void
MainWindow::setupActionBuild()
{
	connect(ui->actionCompile, SIGNAL(triggered()), this, SLOT(onCompile()));
	connect(&_process, SIGNAL(readyReadStandardOutput()), this, SLOT(onProcessOutput()));
	connect(&_process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(onProcessFinished()));
	connect(&_process, SIGNAL(error(QProcess::ProcessError)), this, SLOT(onProcessError()));
}

void
MainWindow::addErrorLine(QTableWidgetItem* id, QTableWidgetItem* line,
						QTableWidgetItem* msg)
{
	int rowCount = ui->lstError->rowCount();
	ui->lstError->setRowCount(rowCount + 1);
	ui->lstError->setItem(rowCount, 0, id);
	ui->lstError->setItem(rowCount, 1, line);
	ui->lstError->setItem(rowCount, 2, msg);
}

void
MainWindow::addErrorLine(QTableWidgetItem* line, QTableWidgetItem* msg)
{
	int rowCount = ui->lstError->rowCount() + 1;
	QTableWidgetItem* id = new QTableWidgetItem(QString::number(rowCount));
	addErrorLine(id, line, msg);
}

void
MainWindow::onCompile()
{
	QString fileName;
	if (ui->textEdit->getSavedFile(fileName))
		compile(fileName);
}

void
MainWindow::compile(const QString& fileName)
{
	QString exe = "/home/pingu/projects/cubs/cubs/minicompil";
	_process.setReadChannelMode(QProcess::MergedChannels);
	_process.start(exe, QStringList() << "-X" << fileName);
	_dialogWait.show();
}

void
MainWindow::onProcessOutput()
{
	QString s = _process.readAllStandardOutput () + _process.readAllStandardError();
	QStringList list2 = s.split("\n", QString::SkipEmptyParts);
	foreach (QString line, list2)
	{
		QTableWidgetItem* lineItem = new QTableWidgetItem(line.section(':', 0, 0));
		QTableWidgetItem* msgItem = new QTableWidgetItem(line.section(':', 1));
		addErrorLine(lineItem, msgItem);
	}

	//OutputWin::self()->text_console->verticalScrollBar()->setValue(OutputWin::self()->text_console->verticalScrollBar()->maximum());
}

void
MainWindow::onProcessFinished()
{
	//QMessageBox::about(this, tr("About Application"), tr("<b>Finished</b> "));
	_dialogWait.hide();
}

void
MainWindow::onProcessError()
{
	_dialogWait.hide();
	QMessageBox::about(this, tr("About Application"), tr("<b>Error</b> "));
}
