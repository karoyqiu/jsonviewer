/*! ***********************************************************************************************
 *
 * \file        jsonhighlighter.h
 * \brief       JsonHighlighter 类头/源文件。
 *
 * \version     0.1
 * \date        2017/9/22
 *
 * \author      Roy QIU <karoyqiu@gmail.com>
 * \copyright   © 2017 Roy QIU。
 *
 **************************************************************************************************/
#pragma once
#include <QSyntaxHighlighter>


class JsonHighlighter : public QSyntaxHighlighter
{
public:
    explicit JsonHighlighter(QObject *parent);
    explicit JsonHighlighter(QTextDocument *parent);

protected:
    // QSyntaxHighlighter interface
    virtual void highlightBlock(const QString &text) Q_DECL_OVERRIDE;

private:
    void initRules();

private:
    struct HighlightingRule
    {
        QRegularExpression pattern;
        QTextCharFormat format;
    };

    QVector<HighlightingRule> rules_;

    QRegExp commentStartExpression;
    QRegExp commentEndExpression;

    QTextCharFormat keywordFormat;
    QTextCharFormat classFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
    QTextCharFormat quotationFormat;
    QTextCharFormat functionFormat;
};
