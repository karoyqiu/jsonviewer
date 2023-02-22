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
#ifdef HAS_WINRT
#include <winrt/Windows.UI.ViewManagement.h>
#endif

#include "mainwindow.h"


#ifdef HAS_WINRT
static inline bool isColorLight(const winrt::Windows::UI::Color &clr)
{
    return (((5 * clr.G) + (2 * clr.R) + clr.B) > (8 * 128));
}
#endif


static void checkDarkMode(QApplication &app)
{
#ifdef Q_OS_WIN
#ifdef HAS_WINRT
    using namespace winrt::Windows::UI::ViewManagement;

    UISettings settings;
    auto foreground = settings.GetColorValue(UIColorType::Foreground);
    auto isDarkMode = isColorLight(foreground);

    if (isDarkMode)
#else
    QSettings settings(QS(R"(HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Themes\Personalize)"), QSettings::NativeFormat);

    if (settings.value(QS("AppsUseLightTheme")) == 0)
#endif
    {
        QPalette darkPalette;
        QColor darkColor(45, 45, 45);
        QColor disabledColor(127, 127, 127);
        QColor textColor(204, 204, 204);
        darkPalette.setColor(QPalette::Window, darkColor);
        darkPalette.setColor(QPalette::WindowText, textColor);
        darkPalette.setColor(QPalette::Base, QColor(18, 18, 18));
        darkPalette.setColor(QPalette::AlternateBase, darkColor);
        darkPalette.setColor(QPalette::ToolTipBase, textColor);
        darkPalette.setColor(QPalette::ToolTipText, textColor);
        darkPalette.setColor(QPalette::Text, textColor);
        darkPalette.setColor(QPalette::Disabled, QPalette::Text, disabledColor);
        darkPalette.setColor(QPalette::Button, darkColor);
        darkPalette.setColor(QPalette::ButtonText, textColor);
        darkPalette.setColor(QPalette::Disabled, QPalette::ButtonText, disabledColor);
        darkPalette.setColor(QPalette::BrightText, Qt::red);
        darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
        darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
        darkPalette.setColor(QPalette::HighlightedText, Qt::black);
        darkPalette.setColor(QPalette::Disabled, QPalette::HighlightedText, disabledColor);

        QApplication::setStyle(QS("Fusion"));
        QApplication::setPalette(darkPalette);

        app.setStyleSheet(QS("QToolTip { color: #cccccc; background-color: #121212; border: 1px solid gray; }"));
    }
#else
    Q_UNUSED(app);
#endif
}


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
#ifdef Q_OS_WIN
    qputenv("QT_QPA_PLATFORM", QByteArrayLiteral("windows:darkmode=1"));
#endif

    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication::setAttribute(Qt::AA_DisableWindowContextHelpButton);

    QApplication a(argc, argv);

    QLocale loc;
    qDebug() << "Current locale:" << loc << loc.uiLanguages();
    loadTranslation(loc, QS("qt"));
    loadTranslation(loc, QS("jsonviewer"));

    QApplication::setApplicationName(QS("jsonviewer"));
    QApplication::setOrganizationName(QS("karoyqiu"));
    QApplication::setOrganizationDomain(QS("karoyqiu.gmail.com"));
    QApplication::setApplicationDisplayName(QApplication::translate("main", "JSON Viewer"));

    checkDarkMode(a);
    QIcon::setThemeName(QS("elementary"));

    MainWindow w;
    w.show();

    return QApplication::exec();
}
