#ifndef MIPSTEXTHIGHLIGHTER_H
#define MIPSTEXTHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QRegExp>
#include <QTextCharFormat>
#include <QVector>
#include <QTextEdit>
#include <QTextDocument>

class MipsTextHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    explicit MipsTextHighlighter(QObject *parent = 0);
    explicit MipsTextHighlighter(QTextDocument *parent = 0);
    explicit MipsTextHighlighter(QTextEdit *parent = 0);
protected:
    void init();
     void highlightBlock(const QString &text);
     struct HighlightingRule{
         QRegExp pattern;
         QTextCharFormat format;
     };
     QVector<HighlightingRule> highlightingRules;

     QTextCharFormat instructionsHighlight;
     QTextCharFormat registersHighlight;
     QTextCharFormat immediateHighlight;
     QTextCharFormat labelsHighlight;
     QTextCharFormat commentsHighlight;
};



#endif // MIPSTEXTHIGHLIGHTER_H
