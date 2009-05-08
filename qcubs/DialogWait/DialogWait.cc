#include "DialogWait.hh"
#include "ui_DialogWait.h"

DialogWait::DialogWait(QWidget* parent)
 : QDialog(parent), ui(new Ui::DialogWait), _process(0)
{
	ui->setupUi(this);
	connect(ui->btCancel, SIGNAL(clicked(QAbstractButton*)), this, SLOT(onCancel()));
}

DialogWait::~DialogWait()
{
	delete ui;
}

void
DialogWait::setActiveProcess(QProcess& process)
{
	_process = &process;
}

void
DialogWait::onCancel()
{
	if (_process)
		_process->kill();
	close();
}

void
DialogWait::changeEvent(QEvent* e)
{
	QDialog::changeEvent(e);
	switch (e->type())
	{
		case QEvent::LanguageChange:
			ui->retranslateUi(this);
			break;
		default:
			break;
	}
}
