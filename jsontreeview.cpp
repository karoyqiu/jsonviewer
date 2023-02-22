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
{
    setAlternatingRowColors(true);
    setAnimated(true);
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
