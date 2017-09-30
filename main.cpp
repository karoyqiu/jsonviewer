/*! ***********************************************************************************************
 *
 * \file        main.cpp
 * \brief        类头/源文件。
 *
 * \version     0.1
 * \date        2017/9/22
 *
 * \author      Roy QIU <karoyqiu@gmail.com>
 * \copyright   © 2017 Roy QIU。
 *
 **************************************************************************************************/
#include "stable.h"
#include "mainwindow.h"


static void loadTranslation(const QLocale &locale, const QString &baseName)
{
    QTranslator *ts = new QTranslator;

    if (ts->load(locale, baseName, QS("_"), QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
    {
        QCoreApplication::installTranslator(ts);
    }
    else
    {
        qWarning() << "Failed to load translation" << baseName;
        delete ts;
    }
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QLocale loc;
    qDebug() << "Current locale:" << loc << loc.uiLanguages();
    loadTranslation(loc, QS("qt"));
    loadTranslation(loc, QS("jsonviewer"));

    QApplication::setApplicationName(QS("jsonviewer"));
    QApplication::setApplicationDisplayName(QApplication::translate("main", "JSON Viewer"));
    QApplication::setOrganizationName(QS("Zhongfu"));
    QApplication::setOrganizationDomain(QS("zhongfu.net"));

    MainWindow w;
    w.show();

    return a.exec();
}
