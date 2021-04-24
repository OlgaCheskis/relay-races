/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "athletes_widget.h"
#include "athletes_model.h"
#include "project.h"

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QHeaderView>

athletes_widget::athletes_widget(project &proj, QWidget *parent)
    : QWidget(parent)
{
    m_model = new athletes_model (proj, this);

    QTableView *table_view = new QTableView;
    table_view->setModel (m_model);
    table_view->setMinimumWidth (600);
    //table_view->horizontalHeader()->setSectionResizeMode (QHeaderView::Stretch);
    //table_view->verticalHeader()->setSectionResizeMode (QHeaderView::Stretch);
    m_model->setParent (table_view);

    auto *main_layout = new QVBoxLayout;
    main_layout->addWidget (table_view);
    table_view->resizeColumnsToContents ();

    auto *button_layout = new QHBoxLayout;
    button_layout->addWidget (m_add_but = new QPushButton ("Add", this));
    button_layout->addWidget (m_del_but = new QPushButton ("Del", this));

    main_layout->addLayout(button_layout);

    setLayout (main_layout);
}
