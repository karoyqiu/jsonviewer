﻿/*! ***********************************************************************************************
 *
 * \file        jsonitem.h
 * \brief       JsonItem 类头/源文件。
 *
 * \version     0.1
 * \date        2017/9/22
 *
 * \author      Roy QIU <karoyqiu@gmail.com>
 * \copyright   © 2017 Roy QIU。
 *
 **************************************************************************************************/
#pragma once
#include <QCoreApplication>
#include <QJsonValue>
#include <QList>
#include <QSharedDataPointer>

class JsonItemData;


class JsonItem
{
    Q_DECLARE_TR_FUNCTIONS(JsonItem)

public:
    JsonItem();
    JsonItem(const QString &name, const QJsonValue &value, JsonItem *parent = Q_NULLPTR);
    JsonItem(const JsonItem &);
    JsonItem &operator=(const JsonItem &);
    ~JsonItem();

    QString name() const;
    QJsonValue::Type type() const;
    QVariant value() const;

    JsonItem *parent() const;
    int row() const;

    int childCount() const;
    JsonItem *childAt(int index) const;

    QByteArray toJson() const;

private:
    QSharedDataPointer<JsonItemData> data;
};
