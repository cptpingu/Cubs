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
}

QCubsEditor::~QCubsEditor()
{
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

void
QCubsEditor::open()
{
	if (maybeSave())
	{
		QString fileName = QFileDialog::getOpenFileName(this);
		if (!fileName.isEmpty())
			loadFile(fileName);
	}
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
	//setWindowModified(isModified());
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

void
QCubsEditor::loadFile(const QString& fileName)
{
	QFile file(fileName);
	if (!file.open(QFile::ReadOnly))
	{
		QMessageBox::warning(this, tr("Application"),
							 tr("Cannot read file %1:\n%2.")
							 .arg(fileName)
							 .arg(file.errorString()));
		return;
	}

	QTextStream in(&file);
	QApplication::setOverrideCursor(Qt::WaitCursor);
	setText(in.readAll());
	QApplication::restoreOverrideCursor();

	setCurrentFile(fileName);
	//statusBar()->showMessage(tr("File loaded"), 2000);
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
	//statusBar()->showMessage(tr("File saved"), 2000);
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
