/*! ***********************************************************************************************
 *
 * \file        jsonhighlighter.cpp
 * \brief       JsonHighlighter 类头/源文件。
 *
 * \version     0.1
 * \date        2017/9/22
 *
 * \author      Roy QIU <karoyqiu@gmail.com>
 * \copyright   © 2017 Roy QIU。
 *
 **************************************************************************************************/
#include "stable.h"
#include "jsonhighlighter.h"


JsonHighlighter::JsonHighlighter(QObject *parent)
    : QSyntaxHighlighter(parent)
{
    initRules();
}


JsonHighlighter::JsonHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    initRules();
}


void JsonHighlighter::highlightBlock(const QString &text)
{
    for (const auto &rule : rules_)
    {
        const QRegularExpression &regex = rule.pattern;
        auto match = regex.match(text);

        if (match.hasMatch())
        {
            for (int i = 0; i <= match.lastCapturedIndex(); i++)
            {
                setFormat(match.capturedStart(i), match.capturedLength(i), rule.format);
            }
        }
    }
}


void JsonHighlighter::initRules()
{
    HighlightingRule rule;

    // Number
    rule.pattern = QRegularExpression(QS("([-0-9.]+)(?!([^\"]*\"[\\s]*\\:))"));
    rule.format.setForeground(Qt::darkRed);
    rules_.append(rule);

    // middle
    rule.pattern = QRegularExpression(QS("(?:[ ]*\\,[ ]*)(\"[^\"]*\")"));
    rule.format.setForeground(Qt::darkGreen);
    rules_.append(rule);

    // last
    rule.pattern = QRegularExpression(QS("(\"[^\"]*\")(?:\\s*\\])"));
    rule.format.setForeground(Qt::darkGreen);
    rules_.append(rule);

    // String
    rule.pattern = QRegularExpression(QS("(\"[^\"]*\")\\s*\\:"));
    rule.format.setForeground(Qt::darkYellow);
    rules_.append(rule);

    rule.pattern = QRegularExpression(QS(":+(?:[: []*)(\"[^\"]*\")"));
    rule.format.setForeground(Qt::darkGreen);
    rules_.append(rule);

    // Keyword
    rule.pattern = QRegularExpression(QS("null|true|false"));
    rule.format.setForeground(Qt::darkCyan);
    rules_.append(rule);
}
