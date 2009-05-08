#include "DialogWait.hh"
#include "ui_DialogWait.h"

DialogWait::DialogWait(QWidget* parent)
 : QDialog(parent),
	ui(new Ui::DialogWait)
{
	ui->setupUi(this);
}

DialogWait::~DialogWait()
{
	delete ui;
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
