/*! ***********************************************************************************************
 *
 * \file        jsontreeview.cpp
 * \brief       JsonTreeView 类源文件。
 *
 * \version     0.1
 * \date        2023-02-22
 *
 * \author      Roy QIU <karoyqiu@gmail.com>
 * \copyright   © 2017~2023 karoyqiu。
 *
 **************************************************************************************************/
#include "jsontreeview.h"
#include "jsonmodel.h"


JsonTreeView::JsonTreeView(QWidget *parent /*= nullptr*/)
    : QTreeView(parent)
    , model_(nullptr)
    , menu_(nullptr)
{
    setAlternatingRowColors(true);
    setAnimated(true);
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QWidget::customContextMenuRequested, this, &JsonTreeView::showMenu);
}


void JsonTreeView::setJson(const QByteArray &value)
{
    if (model_ == nullptr)
    {
        model_ = q_check_ptr(new JsonModel(this));
        setModel(model_);
    }

    model_->setJson(value);
    expandAll();
}


QByteArray JsonTreeView::json() const
{
    if (model_ == nullptr)
    {
        return {};
    }

    return model_->document().toJson(QJsonDocument::Compact);
}


void JsonTreeView::showMenu(const QPoint &pos)
{
    auto idx = indexAt(pos);

    if (idx.column() == JsonModel::NameColumn)
    {
        if (menu_ == nullptr)
        {
            menu_ = new QMenu(this);
            menu_->addAction(tr("Copy node"), this, &JsonTreeView::copyNode);
        }

        menu_->popup(viewport()->mapToGlobal(pos));
    }
}


void JsonTreeView::copyNode()
{
    auto idx = currentIndex();
    auto s = model_->copyNode(idx);
    qApp->clipboard()->setText(s);
}
