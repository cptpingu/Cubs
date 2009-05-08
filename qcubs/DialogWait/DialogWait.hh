#ifndef DIALOGWAIT_HH
#define DIALOGWAIT_HH

#include <QtGui/QDialog>

namespace Ui
{
	class DialogWait;
}

class DialogWait : public QDialog
{
	Q_OBJECT
	Q_DISABLE_COPY(DialogWait)
public:
	explicit DialogWait(QWidget* parent = 0);
	virtual ~DialogWait();

protected:
	virtual void changeEvent(QEvent* e);

private:
	Ui::DialogWait* ui;
};

#endif // DIALOGWAIT_HH
