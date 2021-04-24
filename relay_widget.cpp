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

#include "relay_widget.h"
#include "relay_item_model.h"
#include "project.h"

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QPushButton>
#include <QtWidgets/QTreeView>
//#include <QtWidgets/QHeaderView>

relay_widget::relay_widget (project &proj, QWidget *parent)
    : QWidget (parent)
{
  m_model = new relay_item_model (proj, this);

  m_tree_view = new QTreeView (this);
  m_tree_view->setModel (m_model);
  m_tree_view->setMinimumWidth (600);
  m_tree_view->setHeaderHidden (false);
  m_model->setParent (m_tree_view);

  auto *main_layout = new QVBoxLayout;
  main_layout->addWidget (m_tree_view);
  auto calc_but = new QPushButton ("Calculate", this);
  main_layout->addWidget (calc_but);
  QObject::connect(calc_but, &QPushButton::clicked, [this] ()
  {
    m_model->calculate ();
    m_tree_view->resizeColumnToContents (0);
  });
//  tree_view->resizeColumnsToContents ();

  setLayout (main_layout);
}


