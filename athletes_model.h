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

#ifndef ATHLETES_MODEL_H
#define ATHLETES_MODEL_H

#include <QtCore/QAbstractTableModel>

class project;
class athlete_t;

class athlete_wrapper
{
public:
  athlete_wrapper (athlete_t &athlete);

  QVariant get_data_by_section (int section) const;
  void set_data_by_section (int section, QVariant data);
  static QString get_string_by_section (int section);

private:
  athlete_t &m_athlete;
};

class athletes_model : public QAbstractTableModel
{
  Q_OBJECT
public:
  athletes_model (project &proj, QObject *parent = 0);
  virtual ~athletes_model();

  int rowCount (const QModelIndex &parent = QModelIndex()) const;
  int columnCount (const QModelIndex &parent = QModelIndex()) const;
  QVariant headerData (int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
  QVariant data (const QModelIndex &index, int role = Qt::DisplayRole) const;
  bool setData (const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
  Qt::ItemFlags flags(const QModelIndex &index) const;

private:
  project &m_project;
  const int m_column_count = 6;
};

#endif // ATHLETES_MODEL_H
