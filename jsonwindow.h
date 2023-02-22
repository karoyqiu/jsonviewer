/*! ***********************************************************************************************
 *
 * \file        jsonwindow.h
 * \brief       JsonWindow 类头文件。
 *
 * \version     0.1
 * \date        2023-02-22
 *
 * \author      Roy QIU <karoyqiu@gmail.com>
 * \copyright   © 2017~2023 karoyqiu。
 *
 **************************************************************************************************/
#pragma once
#include <QMdiSubWindow>
#include "jsonview.h"

enum class ViewType
{
    TreeView,
    TextView,
};


class JsonWindow : public QMdiSubWindow, public JsonView
{
    Q_OBJECT

public:
    explicit JsonWindow(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
    virtual ~JsonWindow();

    void setViewType(ViewType value);

    virtual void setJson(const QByteArray &value) override;
    virtual QByteArray json() const override;

private:
    ViewType viewType_;
    JsonView *view_;
};
