#include <QtGui>
#include "QCubsEditor.hh"

QCubsEditor::QCubsEditor(QWidget* parent)
 : super(parent)
{
	init();
}

QCubsEditor::QCubsEditor(const QString& text, QWidget* parent)
 : super(text, parent)
{
	init();
}

void
QCubsEditor::init()
{
	QFont font;
	font.setFamily("Monospace");
	font.setFixedPitch(true);
	font.setPointSize(10);

	setFont(font);
	_highlighter = new CubsHighlighter(document());

	connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(colorCurrentLine()));
}

QCubsEditor::~QCubsEditor()
{
}

void
QCubsEditor::colorCurrentLine()
{
	QTextEdit::ExtraSelection highlight;
	highlight.cursor = this->textCursor();
	highlight.format.setProperty(QTextFormat::FullWidthSelection, true);
	highlight.format.setBackground(QColor(233, 243, 255, 255));

	QList<QTextEdit::ExtraSelection> extras;
	extras << highlight;
	setExtraSelections(extras);
}

void
QCubsEditor::changeEvent(QEvent* e)
{
	super::changeEvent(e);
}

void
QCubsEditor::closeEvent(QCloseEvent* event)
{
	if (maybeSave())
	{
		//writeSettings();
		event->accept();
	}
	else
		event->ignore();
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
	setWindowModified(document()->isModified());
}

bool
QCubsEditor::maybeSave()
{
	if (this->document()->isModified())
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
	setText(in.readAll());
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
	setWindowModified(false);

	QString shownName;
	if (_curFile.isEmpty())
		shownName = "untitled.txt";
	else
		shownName = strippedName(_curFile);

	setWindowTitle(tr("%1[*] - %2").arg(shownName).arg(tr("Application")));
}

QString
QCubsEditor::strippedName(const QString& fullFileName)
{
	return QFileInfo(fullFileName).fileName();
}
