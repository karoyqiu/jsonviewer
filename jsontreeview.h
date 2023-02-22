/*! ***********************************************************************************************
 *
 * \file        jsontreeview.h
 * \brief       JsonTreeView 类头文件。
 *
 * \version     0.1
 * \date        2023-02-22
 *
 * \author      Roy QIU <karoyqiu@gmail.com>
 * \copyright   © 2017~2023 karoyqiu。
 *
 **************************************************************************************************/
#pragma once
#include <QTreeView>
#include "jsonview.h"

class JsonModel;


class JsonTreeView : public QTreeView, public JsonView
{
    Q_OBJECT

public:
    explicit JsonTreeView(QWidget *parent = nullptr);

    virtual void setJson(const QByteArray &value) override;
    virtual QByteArray json() const override;

private:
    void showMenu(const QPoint &pos);
    void copyNode();

private:
    JsonModel *model_;
    QMenu *menu_;
};
