#include <QtGui>
#include "LineNumberWidget.hh"
#include "QCubsEditor.hh"

LineNumberWidget::LineNumberWidget(QColor col, QCubsEditor* parent)
 : super(reinterpret_cast<super*>(parent)), _color(col)
{
	_codeEditor = parent;
}

QSize
LineNumberWidget::sizeHint() const
{
	 return QSize(_codeEditor->lineNumberAreaWidth(), 0);
}

void
LineNumberWidget::paintEvent(QPaintEvent* event)
{
	_codeEditor->lineNumberAreaPaintEvent(event);
}

//void
//LineNumberWidget::paintEvent(QPaintEvent* e)
//{
//	super::paintEvent(e);
//	QTextEdit* txtEdit = static_cast<QTextEdit*>(parent());
//
//	QPainter p(this->viewport());
//	p.setPen(Qt::NoPen);
//	p.setBrush(_color);
//	p.drawRect(0, 0, width(), height());
//	p.drawRect(0, 0, width(), txtEdit->height());
//
//	int contentsY = txtEdit->verticalScrollBar()->value();
//	qreal pageBottom = contentsY + txtEdit->viewport()->height();
//	int lineNumber = 1/*_lineNumber*/;
//	const QFontMetrics fm = fontMetrics();
//	const int ascent = fontMetrics().ascent() + 1;
//
//	int tmp = 0;
//	p.setPen(Qt::SolidLine);
//	p.setBrush(Qt::black);
//	for (QTextBlock block = txtEdit->document()->begin();
//		block.isValid(); block = block.next(), ++lineNumber)
//	{
//		tmp++;
//		QTextLayout* layout = block.layout();
//		const QRectF boundingRect = layout->boundingRect();
//		QPointF position = layout->position();
//		if (position.y() + boundingRect.height() < contentsY)
//			continue;
//		if (position.y() > pageBottom)
//			break;
//		const QString txt = QString::number(lineNumber);
//		p.drawText(width() - fm.width(txt) - 2, qRound(position.y()) - contentsY + ascent, txt);
//	}
//	QString msg;
//	msg.append(QString::number(tmp));
//	qDebug(msg.toStdString().c_str());
//}
