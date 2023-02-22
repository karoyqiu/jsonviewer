/*! ***********************************************************************************************
 *
 * \file        jsonview.h
 * \brief       JsonView 类头文件。
 *
 * \version     0.1
 * \date        2023-02-22
 *
 * \author      Roy QIU <karoyqiu@gmail.com>
 * \copyright   © 2017~2023 karoyqiu。
 *
 **************************************************************************************************/
#pragma once

class JsonView
{
public:
    virtual ~JsonView() = default;

    virtual void setJson(const QByteArray &value) = 0;
    virtual QByteArray json() const = 0;
};
