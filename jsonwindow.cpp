/*! ***********************************************************************************************
 *
 * \file        jsonwindow.cpp
 * \brief       JsonWindow 类源文件。
 *
 * \version     0.1
 * \date        2023-02-22
 *
 * \author      Roy QIU <karoyqiu@gmail.com>
 * \copyright   © 2017~2023 karoyqiu。
 *
 **************************************************************************************************/
#include "jsonwindow.h"
#include "jsontreeview.h"


JsonWindow::JsonWindow(QWidget *parent /*= nullptr*/, Qt::WindowFlags flags)
    : QMdiSubWindow(parent, flags)
    , viewType_(ViewType::TextView)
    , view_(nullptr)
{
    setAttribute(Qt::WA_DeleteOnClose);
    setViewType(ViewType::TreeView);
}


JsonWindow::~JsonWindow()
{
}


void JsonWindow::setViewType(ViewType value)
{
    if (viewType_ != value)
    {
        viewType_ = value;

        auto *current = widget();

        if (current != nullptr)
        {
            current->deleteLater();
        }

        switch (value)
        {
        case ViewType::TreeView:
        {
            auto *view = new JsonTreeView(this);
            setWidget(view);
            view_ = view;
            break;
        }
        case ViewType::TextView:
            break;
        default:
            break;
        }
    }
}


void JsonWindow::setJson(const QByteArray &value)
{
    if (view_ != nullptr)
    {
        view_->setJson(value);
    }
}


QByteArray JsonWindow::json() const
{
    if (view_ != nullptr)
    {
        return   view_->json();
    }

    return {};
}
