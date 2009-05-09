#ifndef QCUBSEDITOR_HH
#define QCUBSEDITOR_HH

#include <QTextEdit>
#include "CubsHighlighter.hh"

class QCubsEditor : public QTextEdit
{
	Q_OBJECT

	typedef QTextEdit super;
public:
	explicit QCubsEditor(QWidget* parent = 0);
	explicit QCubsEditor(const QString& text, QWidget* parent = 0);
	virtual ~QCubsEditor();
	bool getSavedFile(QString& file);

protected:
	virtual void changeEvent(QEvent* e);
	virtual void init();
	virtual void closeEvent(QCloseEvent* event);

public slots:
	void newFile();
	bool open();
	bool save();
	bool saveAs();
	void documentWasModified();
	void colorCurrentLine();

	bool maybeSave();
	bool loadFile(const QString& fileName);
	bool saveFile(const QString& fileName);
	void setCurrentFile(const QString& fileName);
	static QString strippedName(const QString& fullFileName);

protected:
	QString _curFile;
	CubsHighlighter* _highlighter;
};

#endif // QCUBSEDITOR_HH
