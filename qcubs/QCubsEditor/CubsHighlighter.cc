#include "CubsHighlighter.hh"

CubsHighlighter::CubsHighlighter(QTextDocument *parent)
 : QSyntaxHighlighter(parent)
{
	HighlightingRule rule;

	keywordFormat.setForeground(QBrush(QColor(0, 85, 255, 255)));
	keywordFormat.setFontWeight(QFont::Bold);
	keywordFormat.setFontItalic(false);
	QStringList keywordPatterns;
	keywordPatterns << "\\bbegin\\b" << "\\bend\\b" << "\\bexit\\b"
		<< "\\bif\\b" << "\\bwhile\\b" << "\\breturn\\b" << "\\bdo\\b"
		<< "\\bvar\\b" << "\\bfunction\\b" << "\\bthen\\b";
	foreach (QString pattern, keywordPatterns)
	{
		rule.pattern = QRegExp(pattern);
		rule.format = keywordFormat;
		highlightingRules.append(rule);
	}

	typeFormat.setForeground(QBrush(QColor(255, 85, 0, 255)));
	typeFormat.setFontWeight(QFont::Normal);
	keywordPatterns.clear();
	keywordPatterns << "\\binteger\\b" << "\\bstring\\b" << "\\bboolean\\b";
	foreach (QString pattern, keywordPatterns)
	{
		rule.pattern = QRegExp(pattern);
		rule.format = typeFormat;
		highlightingRules.append(rule);
	}

	functionFormat.setFontItalic(true);
	functionFormat.setForeground(Qt::blue);
	rule.pattern = QRegExp("\\b[A-Za-z0-9_]+\\s*(?=\\()");
	rule.format = functionFormat;
	highlightingRules.append(rule);

	builtinFormat.setForeground(QBrush(QColor(85, 0, 255, 255)));
	builtinFormat.setFontWeight(QFont::Normal);
	keywordPatterns.clear();
	keywordPatterns << "\\bexit\\b" << "\\bread\\b" << "\\bprint\\b";
	foreach (QString pattern, keywordPatterns)
	{
		rule.pattern = QRegExp(pattern);
		rule.format = builtinFormat;
		highlightingRules.append(rule);
	}

	valueFormat.setForeground(QBrush(QColor(0, 150, 0, 255)));
	rule.pattern = QRegExp("\\b(true|false|[0-9]+)\\b");
	rule.format = valueFormat;
	highlightingRules.append(rule);

	quotationFormat.setForeground(Qt::red);
	rule.pattern = QRegExp("\".*\"");
	rule.format = quotationFormat;
	highlightingRules.append(rule);

	singleLineCommentFormat.setForeground(Qt::darkGray);
	rule.pattern = QRegExp("//[^\n]*");
	rule.format = singleLineCommentFormat;
	highlightingRules.append(rule);
	rule.pattern = QRegExp("#[^\n]*");
	rule.format = singleLineCommentFormat;
	highlightingRules.append(rule);

	trailingWhiteSpaceFormat.setBackground(Qt::red);
	rule.pattern = QRegExp("\\s+$");
	rule.format = trailingWhiteSpaceFormat;
	highlightingRules.append(rule);

	multiLineCommentFormat.setForeground(Qt::darkGray);

	commentStartExpression = QRegExp("/\\*");
	commentEndExpression = QRegExp("\\*/");
}

void
CubsHighlighter::highlightBlock(const QString &text)
{
	foreach (HighlightingRule rule, highlightingRules)
	{
		QRegExp expression(rule.pattern);
		int index = text.indexOf(expression);
		while (index >= 0)
		{
			int length = expression.matchedLength();
			setFormat(index, length, rule.format);
			index = text.indexOf(expression, index + length);
		}
	}
	setCurrentBlockState(0);
	int startIndex = 0;
	if (previousBlockState() != 1)
		startIndex = text.indexOf(commentStartExpression);
	while (startIndex >= 0)
	{
		int endIndex = text.indexOf(commentEndExpression, startIndex);
		int commentLength;
		if (endIndex == -1)
		{
			setCurrentBlockState(1);
			commentLength = text.length() - startIndex;
		}
		else
		{
			commentLength = endIndex - startIndex + commentEndExpression.matchedLength();
		}
		setFormat(startIndex, commentLength, multiLineCommentFormat);
		startIndex = text.indexOf(commentStartExpression, startIndex + commentLength);
	}
}
