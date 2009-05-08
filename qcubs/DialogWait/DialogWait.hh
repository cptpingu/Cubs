#ifndef DIALOGWAIT_HH_
#define DIALOGWAIT_HH_

# include <QtGui/QDialog>
# include <QProcess>

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
	void setActiveProcess(QProcess& process);

protected:
	virtual void changeEvent(QEvent* e);

protected slots:
	void onCancel();

private:
	Ui::DialogWait* ui;
	QProcess* _process;
};

#endif /* !DIALOGWAIT_HH_ */
