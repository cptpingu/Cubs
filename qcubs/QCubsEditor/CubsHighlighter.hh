#ifndef CUBSHIGHLIGHTER_HH
#define CUBSHIGHLIGHTER_HH

 #include <QSyntaxHighlighter>
 #include <QHash>
 #include <QTextCharFormat>

class QTextDocument;

class CubsHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    CubsHighlighter(QTextDocument *parent = 0);

protected:
    void highlightBlock(const QString &text);

private:
    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;
    QRegExp commentStartExpression;
    QRegExp commentEndExpression;
    QTextCharFormat keywordFormat;
    QTextCharFormat typeFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
    QTextCharFormat quotationFormat;
    QTextCharFormat functionFormat;
    QTextCharFormat builtinFormat;
    QTextCharFormat trailingWhiteSpaceFormat;
    QTextCharFormat valueFormat;
};

#endif // CUBSHIGHLIGHTER_HH
