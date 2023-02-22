/*! ***********************************************************************************************
 *
 * \file        mainwindow.cpp
 * \brief       MainWindow 类头/源文件。
 *
 * \version     0.1
 * \date        2017/9/22
 *
 * \author      Roy QIU <karoyqiu@gmail.com>
 * \copyright   © 2017 Roy QIU。
 *
 **************************************************************************************************/
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "jsonwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //model_ = new JsonModel(this);

    ui->setupUi(this);
    //ui->treeView->setModel(model_);

    //QToolButton *button = new QToolButton(this);
    //button->setDefaultAction(ui->actionOpen);
    //button->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    //ui->centerWidget->setCornerWidget(button, Qt::TopLeftCorner);

    //new JsonHighlighter(ui->editView->document());

    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openDocument);

    loadSettings();
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);

    switch (e->type())
    {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


void MainWindow::closeEvent(QCloseEvent *e)
{
    saveSettings();
    QMainWindow::closeEvent(e);
}


void MainWindow::openDocument()
{
    QString filename = QFileDialog::getOpenFileName(this, QString(), QString(),
        tr("JSON files (*.json *.har);;All files (*)"));

    if (!filename.isEmpty())
    {
        QFile file(filename);

        if (file.open(QFile::ReadOnly | QFile::Text))
        {
            auto body = file.readAll();
            auto *window = new JsonWindow;
            window->setJson(body);
            window->setWindowFilePath(filename);
            ui->centerWidget->addSubWindow(window);
            window->showMaximized();
        }
        else
        {
            QMessageBox::critical(this, tr("Failed to open file"), file.errorString());
        }
    }
}


void MainWindow::loadSettings()
{
    QSettings settings;
    restoreGeometry(settings.value(QS("geo")).toByteArray());
    restoreState(settings.value(QS("state")).toByteArray());
}


void MainWindow::saveSettings() const
{
    QSettings settings;
    settings.setValue(QS("geo"), saveGeometry());
    settings.setValue(QS("state"), saveState());
}
