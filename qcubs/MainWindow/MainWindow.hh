#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

# include <QtGui/QMainWindow>
# include <QtGui/QTableWidget>
# include <QProcess>
# include "QCubsEditor/QCubsEditor.hh"
# include "DialogWait/DialogWait.hh"

namespace Ui
{
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();
	virtual void compile(const QString& fileName);
	virtual void addErrorLine(QTableWidgetItem* id, QTableWidgetItem* line, QTableWidgetItem* msg);
	virtual void addErrorLine(QTableWidgetItem* line, QTableWidgetItem* msg);

private:
	void setupEditor();
	void setupAction();
	void setupActionBuild();

private slots:
	// MainWindow Action
	void onLstErrorDoubleClick(int x, int y);
	void onOpen();
	void onClose();
	void onNew();
	void onSave();
	void onSaveAs();
	void onExit();
	void onCut();
	void onCopy();
	void onPaste();
	void onAbout();
	void onAboutQt();
	// MainWindowBuild Action
	void onCompile();
	void onProcessStandardOutput();
	void onProcessStandardError();
	void onProcessFinished();
	void onProcessError();

private:
	Ui::MainWindow *ui;
	QProcess _process;
	DialogWait _dialogWait;
};

#endif // MAINWINDOW_HH
