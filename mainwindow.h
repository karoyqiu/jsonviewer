/*! ***********************************************************************************************
 *
 * \file        mainwindow.h
 * \brief       MainWindow 类头/源文件。
 *
 * \version     0.1
 * \date        2017/9/22
 *
 * \author      Roy QIU <karoyqiu@gmail.com>
 * \copyright   © 2017 Roy QIU。
 *
 **************************************************************************************************/
#pragma once
#include <QMainWindow>

class JsonModel;

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = Q_NULLPTR);
    virtual ~MainWindow();

protected:
    virtual void changeEvent(QEvent *e) Q_DECL_OVERRIDE;
    virtual void closeEvent(QCloseEvent *e) Q_DECL_OVERRIDE;

private slots:
    void openDocument();

private:
    void loadSettings();
    void saveSettings() const;

private:
    Ui::MainWindow *ui;
    JsonModel *model_;
};
