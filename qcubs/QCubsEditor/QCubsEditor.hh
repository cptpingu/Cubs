#ifndef QCUBSEDITOR_HH_
# define QCUBSEDITOR_HH_

# include <QPlainTextEdit>
# include <QtGui>
# include "CubsHighlighter.hh"
# include "LineNumberWidget.hh"

class QCubsEditor : public QPlainTextEdit
{
	Q_OBJECT

	typedef QPlainTextEdit super;
public:
	explicit QCubsEditor(QWidget* parent = 0);
	explicit QCubsEditor(const QString& text, QWidget* parent = 0);
	virtual ~QCubsEditor();
	bool getSavedFile(QString& file);
	void lineNumberAreaPaintEvent(QPaintEvent *event);
	int lineNumberAreaWidth();
	int getCurrentLine();
	int getLineNumber();

protected:
	virtual void changeEvent(QEvent* e);
	virtual void init();
	virtual void closeEvent(QCloseEvent* event);
	virtual void paintEvent(QPaintEvent* event);
	virtual void resizeEvent(QResizeEvent* event);
	virtual void highlightCurrentLine();

public slots:
	void newFile();
	bool open();
	bool save();
	bool saveAs();
	void documentWasModified();
	void onCursorPositionChanged();
	void updateLineNumberAreaWidth(int newBlockCount);
	void updateLineNumberArea(const QRect&, int);

	bool maybeSave();
	bool loadFile(const QString& fileName);
	bool saveFile(const QString& fileName);
	void setCurrentFile(const QString& fileName);
	static QString strippedName(const QString& fullFileName);

protected:
	QString _curFile;
	CubsHighlighter* _highlighter;
	LineNumberWidget* _lineNumberArea;
};

#endif /* !QCUBSEDITOR_HH_ */
