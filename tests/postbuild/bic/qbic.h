/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the test suite of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/
#ifndef QBIC_H
#define QBIC_H

#include "QtCore/qhash.h"
#include "QtCore/qlist.h"
#include "QtCore/qpair.h"
#include "QtCore/qregexp.h"
#include "QtCore/qstring.h"
#include "QtCore/qstringlist.h"

QT_FORWARD_DECLARE_CLASS(QByteArray)

class QBic
{
public:
    struct Info
    {
        QHash<QString, int> classSizes;
        QHash<QString, QStringList> classVTables;
    };

    struct VTableDiff
    {
        QList<QPair<QString, QString> > reimpMethods;
        QList<QPair<QString, QString> > modifiedVTables;
        QStringList addedVTables;
        QStringList removedVTables;
    };

    struct SizeDiff
    {
        QStringList mismatch;
        QStringList added;
        QStringList removed;
    };

    void addBlacklistedClass(const QString &wildcard);
    void removeBlacklistedClass(const QString &wildcard);
    bool isBlacklisted(const QString &className) const;

    Info parseOutput(const QByteArray &ba) const;
    Info parseFile(const QString &fileName) const;

    VTableDiff diffVTables(const Info &oldLib, const Info &newLib) const;
    SizeDiff diffSizes(const Info &oldLib, const Info &newLib) const;

private:
    mutable QList<QRegExp> blackList;
};

#endif
