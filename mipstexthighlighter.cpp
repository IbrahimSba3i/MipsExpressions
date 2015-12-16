#include "mipstexthighlighter.h"
#include <QDebug>

MipsTextHighlighter::MipsTextHighlighter(QObject *parent) :
    QSyntaxHighlighter(parent)
{
    init();
}

MipsTextHighlighter::MipsTextHighlighter(QTextEdit *parent) :
    QSyntaxHighlighter(parent)
{
    init();
}

MipsTextHighlighter::MipsTextHighlighter(QTextDocument *parent) :
    QSyntaxHighlighter(parent)
{
    init();
}

void MipsTextHighlighter::init()
{
    HighlightingRule rule;
    instructionsHighlight.setForeground(Qt::blue);
    instructionsHighlight.setFontWeight(QFont::Bold);
    //instructionsHighlight.setFontItalic(true);
    QStringList instructionNames;
    instructionNames << "\\badd\\b" << "\\baddu\\b" << "\\bsub\\b" << "\\bsubu\\b" << "\\band\\b" << "\\bor\\b" << "\\bnor\\b" << "\\bxor\\b" << "\\bsrlv\\b" << "\\bsllv\\b" << "\\bsrav\\b" << "\\bslt\\b" << "\\bsltu\\b" << "\\bsb\\b" << "\\blb\\b" << "\\blbu\\b" << "\\bsh\\b" << "\\blh\\b" << "\\blhu\\b" << "\\bsw\\b" << "\\blw\\b" << "\\blwl\\b" << "\\blwr\\b" << "\\bswl\\b" << "\\bswr\\b" << "\\bll\\b" << "\\bsc\\b" << "\\baddi\\b" << "\\baddiu\\b" << "\\bandi\\b" << "\\bori\\b" << "\\bnori\\b" << "\\bxori\\b" << "\\bsrl\\b" << "\\bsll\\b" << "\\bsra\\b" << "\\bslti\\b" << "\\bsltiu\\b" << "\\bbeq\\b" << "\\bbne\\b" << "\\blui\\b" << "\\bjr\\b" << "\\bjalr\\b" << "\\bmfhi\\b" << "\\bmflo\\b" << "\\bmtlo\\b" << "\\bmthi\\b" << "\\bmult\\b" << "\\bmultu\\b" << "\\bdiv\\b" << "\\bdivu\\b" << "\\bj\\b" << "\\bjal\\b" << "\\bsyscall\\b" << "\\bnop\\b" << "\\bblt\\b" << "\\bbgt\\b" << "\\bble\\b" << "\\bbge\\b" << "\\bbltu\\b" << "\\bbgtu\\b" << "\\bbleu\\b" << "\\bbgeu\\b" << "\\bblti\\b" << "\\bbgti\\b" << "\\bblei\\b" << "\\bbgei\\b" << "\\bbltiu\\b" << "\\bbgtiu\\b" << "\\bbleiu\\b" << "\\bbgeiu\\b" << "\\bbeqz\\b" << "\\bbnez\\b" << "\\bbltz\\b" << "\\bbgtz\\b" << "\\bblez\\b" << "\\bbgez\\b" << "\\bli\\b" << "\\bla\\b" << "\\bror\\b" << "\\brol\\b" << "\\bnot\\b" << "\\bneg\\b" << "\\bmove\\b" << "\\babs\\b" << "\\bmul\\b" << "\\bdiv\\b" << "\\brem\\b" << "\\bclear\\b" << "\\bsubi\\b";
    foreach (const QString &pattern, instructionNames) {
        rule.pattern = QRegExp(pattern, Qt::CaseInsensitive);
        rule.format = instructionsHighlight;
        highlightingRules.append(rule);
    }

    registersHighlight.setForeground(QBrush(QColor(185,0,4)));
    registersHighlight.setFontWeight(QFont::Bold);
    QStringList registerNames;
    registerNames << "\\$zero" << "\\$at" << "\\$v0" << "\\$v1" << "\\$a0" << "\\$a1" << "\\$a2" << "\\$a3" << "\\$t0" << "\\$t1" << "\\$t2" << "\\$t3" << "\\$t4" << "\\$t5" << "\\$t6" << "\\$t7" << "\\$s0" << "\\$s1" << "\\$s2" << "\\$s3" << "\\$s4" << "\\$s5" << "\\$s6" << "\\$s7" << "\\$t8" << "\\$t9" << "\\$k0" << "\\$k1" << "\\$gp" << "\\$sp" << "\\$fp" << "\\$ra" ;
    foreach (const QString &pattern, registerNames) {
        rule.pattern = QRegExp(pattern);
        rule.format = registersHighlight;
        highlightingRules.append(rule);
    }
    QRegExp registersRegex("\\b$((?:[1-2]?[0-9])|(?:3[01]))\\b");
    rule.pattern = QRegExp(registersRegex);
    rule.format = registersHighlight;
    highlightingRules.append(rule);

    immediateHighlight.setForeground(QBrush(QColor(27,132,171)));
    immediateHighlight.setFontWeight(QFont::Bold);
    QRegExp immediateRegex("\\b((?:[1-9]*[0-9])|(?:0x[0-9a-fA-F])|(?:0b[01]+))\\b");
    rule.pattern = QRegExp(immediateRegex);
    rule.format = immediateHighlight;
    highlightingRules.append(rule);

    labelsHighlight.setForeground(Qt::black);
    labelsHighlight.setFontItalic(true);
    QRegExp labelRegex("(\\b[_a-zA-Z][_a-zA-Z0-9]*):");
    rule.pattern = QRegExp(labelRegex);
    rule.format = labelsHighlight;
    highlightingRules.append(rule);

    commentsHighlight.setForeground(Qt::darkGreen);
    QRegExp commentsRegex("#.+");
    rule.pattern = QRegExp(commentsRegex);
    rule.format = commentsHighlight;
    highlightingRules.append(rule);
}

void MipsTextHighlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, highlightingRules) {
            QRegExp expression(rule.pattern);
            int index = expression.indexIn(text);
            while (index >= 0) {
                int length = expression.matchedLength();
                setFormat(index, length, rule.format);
                index = expression.indexIn(text, index + length);
            }
    }
}
