#ifndef LINENUMBERWIDGET_HH_
# define LINENUMBERWIDGET_HH_

# include <QWidget>

class QCubsEditor;

class LineNumberWidget : public QWidget
{
	typedef QWidget super;

public:
	LineNumberWidget(QColor col, QCubsEditor* parent = 0);
	QSize sizeHint() const;

 protected:
	 void paintEvent(QPaintEvent *event);

protected:
	QColor _color;
	int _lineNumber;
	QCubsEditor* _codeEditor;
};

#endif /* !LINENUMBERWIDGET_HH_ */
