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
	void readSettings();
	void writeSettings();
	virtual void closeEvent(QCloseEvent* event);

private slots:
	// QCubsEdit Action
	void onLstErrorDoubleClick(int x, int y);
	// MainWindow Action
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
	void onShowEditor();
	void onShowCompileOutput();
	void onShowOnlyEditor();
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
