#include <QtGui>
#include "QCubsEditor.hh"

QCubsEditor::QCubsEditor(QWidget* parent)
 : super(parent), _parent(parent)
{
	init();
}

QCubsEditor::QCubsEditor(const QString& text, QWidget* parent)
 : super(text, parent), _parent(parent)
{
	init();
}

void
QCubsEditor::init()
{
	_lineNumberArea = new LineNumberWidget(Qt::red, this);
	QFont font;
	font.setFamily("Monospace");
	font.setFixedPitch(true);
	font.setPointSize(10);
	setFont(font);
	_highlighter = new CubsHighlighter(document());

	connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
	connect(this, SIGNAL(updateRequest(const QRect&, int)), this, SLOT(updateLineNumberArea(const QRect&, int)));
	connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(onCursorPositionChanged()));
	connect(this, SIGNAL(textChanged()), this, SLOT(documentWasModified()));

	updateLineNumberAreaWidth(0);
	highlightCurrentLine();
}

QCubsEditor::~QCubsEditor()
{
}

void
QCubsEditor::resizeEvent(QResizeEvent* event)
{
	super::resizeEvent(event);
	QRect cr = contentsRect();
	_lineNumberArea->setGeometry(QRect(cr.left(), cr.top(),
		lineNumberAreaWidth(), cr.height()));
}

void
QCubsEditor::paintEvent(QPaintEvent* event)
{
	super::paintEvent(event);
}

void
QCubsEditor::lineNumberAreaPaintEvent(QPaintEvent* event)
{
	QPainter painter(_lineNumberArea);
	painter.fillRect(event->rect(), QColor(240, 240, 240, 255));

	QTextBlock block = firstVisibleBlock();
	int blockNumber = block.blockNumber();
	int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
	int bottom = top + (int) blockBoundingRect(block).height();

	while (block.isValid() && top <= event->rect().bottom())
	{
		if (block.isVisible() && bottom >= event->rect().top())
		{
			QString number = QString::number(blockNumber + 1);
			painter.setPen(Qt::lightGray);
			painter.drawText(0, top, _lineNumberArea->width(),
				fontMetrics().height(), Qt::AlignRight, number);
		}
		block = block.next();
		top = bottom;
		bottom = top + (int) blockBoundingRect(block).height();
		++blockNumber;
	}
}

int
QCubsEditor::lineNumberAreaWidth()
{
	int digits = 1;
	int max = qMax(1, blockCount());
	while (max >= 10)
	{
		max /= 10;
		++digits;
	}

	int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;

	return space;
}

void
QCubsEditor::updateLineNumberAreaWidth(int /* newBlockCount */)
{
	setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void
QCubsEditor::updateLineNumberArea(const QRect& rect, int dy)
{
	if (dy)
		_lineNumberArea->scroll(0, dy);
	else
		_lineNumberArea->update(0, rect.y(), _lineNumberArea->width(), rect.height());

	if (rect.contains(viewport()->rect()))
		updateLineNumberAreaWidth(0);
}

void
QCubsEditor::highlightCurrentLine()
{
	QTextEdit::ExtraSelection highlight;
	highlight.cursor = this->textCursor();
	highlight.format.setProperty(QTextFormat::FullWidthSelection, true);
	highlight.format.setBackground(QColor(233, 243, 255, 255));

	QList<QTextEdit::ExtraSelection> extras;
	extras << highlight;
	setExtraSelections(extras);
}

int
QCubsEditor::getCurrentLine()
{
	QTextDocument *doc = this->document();
	QTextBlock blockFound = doc->findBlock(this->textCursor().position());
	QTextBlock blockPos = doc->begin();
	int line = 1;
	while (blockFound != blockPos)
	{
		blockPos = blockPos.next();
		line++;
	}
	return line;
}

int
QCubsEditor::getLineNumber()
{
	QTextDocument *doc = this->document();
	return doc->lineCount();
}

void
QCubsEditor::onCursorPositionChanged()
{
	highlightCurrentLine();
}

void
QCubsEditor::changeEvent(QEvent* e)
{
	super::changeEvent(e);
}

void
QCubsEditor::newFile()
{
	if (maybeSave())
	{
		clear();
		setCurrentFile("");
	}
}

bool
QCubsEditor::getSavedFile(QString& file)
{
	if (maybeSave())
	{
		file = _curFile;
		return true;
	}

	return false;
}

bool
QCubsEditor::open()
{
	if (maybeSave())
	{
		QString fileName = QFileDialog::getOpenFileName(this);
		if (!fileName.isEmpty())
			return loadFile(fileName);
	}
	return false;
}

bool
QCubsEditor::save()
{
	if (_curFile.isEmpty())
		return saveAs();
	return saveFile(_curFile);
}

bool
QCubsEditor::saveAs()
{
	QString fileName = QFileDialog::getSaveFileName(this);
	if (fileName.isEmpty())
		return false;

	return saveFile(fileName);
}

void
QCubsEditor::documentWasModified()
{
	if (_parent)
		_parent->setWindowModified(document()->isModified());
}

bool
QCubsEditor::maybeSave()
{
	if (document()->isModified())
	{
		int ret = QMessageBox::warning(this, tr("Application"),
					 tr("The document has been modified.\n"
						"Do you want to save your changes?"),
					 QMessageBox::Yes | QMessageBox::Default,
					 QMessageBox::No,
					 QMessageBox::Cancel | QMessageBox::Escape);
		if (ret == QMessageBox::Yes)
			return save();
		if (ret == QMessageBox::Cancel)
			return false;
	}
	return true;
}

bool
QCubsEditor::loadFile(const QString& fileName)
{
	QFile file(fileName);
	if (!file.open(QFile::ReadOnly))
	{
		QMessageBox::warning(this, tr("Application"),
							 tr("Cannot read file %1:\n%2.")
							 .arg(fileName)
							 .arg(file.errorString()));
		return false;
	}

	QTextStream in(&file);
	QApplication::setOverrideCursor(Qt::WaitCursor);
	setPlainText(in.readAll());
	QApplication::restoreOverrideCursor();

	setCurrentFile(fileName);
	return true;
}

bool
QCubsEditor::saveFile(const QString& fileName)
{
	QFile file(fileName);
	if (!file.open(QFile::WriteOnly))
	{
		QMessageBox::warning(this, tr("Application"),
							 tr("Cannot write file %1:\n%2.")
							 .arg(fileName)
							 .arg(file.errorString()));
		return false;
	}

	QTextStream out(&file);
	QApplication::setOverrideCursor(Qt::WaitCursor);
	out << this->Plain;
	QApplication::restoreOverrideCursor();

	setCurrentFile(fileName);
	return true;
}

void
QCubsEditor::setCurrentFile(const QString& fileName)
{
	_curFile = fileName;
	document()->setModified(false);
	if (_parent)
		_parent->setWindowModified(false);

	QString shownName;
	if (_curFile.isEmpty())
		shownName = "untitled.txt";
	else
		shownName = strippedName(_curFile);

	if (_parent)
		_parent->setWindowTitle(tr("%1[*] - %2").arg(shownName).arg(tr("Application")));
}

QString
QCubsEditor::strippedName(const QString& fullFileName)
{
	return QFileInfo(fullFileName).fileName();
}
