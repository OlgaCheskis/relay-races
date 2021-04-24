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

#include "athletes_model.h"
#include "athlete.h"
#include "project.h"

athlete_wrapper::athlete_wrapper (athlete_t &athlete):
  m_athlete (athlete)
{
}

QVariant athlete_wrapper::get_data_by_section (int section) const
{
  QVariant res;
  switch (section)
    {
    case 0:
      res = {m_athlete.m_name.c_str()};
      break;
    case 1:
      res = {m_athlete.m_age};
      break;
    case 2:
      if (m_athlete.m_back < novalid_time) res = {m_athlete.m_back};
      break;
    case 3:
      if (m_athlete.m_breast < novalid_time) res = {m_athlete.m_breast};
      break;
    case 4:
      if (m_athlete.m_fly < novalid_time) res = {m_athlete.m_fly};
      break;
    case 5:
      if (m_athlete.m_free < novalid_time) res = {m_athlete.m_free};
      break;
    }

  return res;
}

void athlete_wrapper::set_data_by_section (int section, QVariant data)
{
  switch (section)
    {
    case 0:
      m_athlete.m_name = data.toString ().toStdString ();
      break;
    case 1:
      m_athlete.m_age = data.toInt ();
      break;
    case 2:
      m_athlete.m_back = data.toDouble ();
      break;
    case 3:
      m_athlete.m_breast = data.toDouble ();
      break;
    case 4:
      m_athlete.m_fly = data.toDouble ();
      break;
    case 5:
      m_athlete.m_free = data.toDouble ();
      break;
    }
}

QString athlete_wrapper::get_string_by_section (int section)
{
  switch (section)
    {
    case 0:
      return {"name"};
    case 1:
      return {"age"};
    case 2:
      return {"back"};
    case 3:
      return {"breast"};
    case 4:
      return {"fly"};
    case 5:
      return {"free"};
    default:
      return {};
    }

  return {};
}


athletes_model::athletes_model (project &proj, QObject *parent):
    QAbstractTableModel(parent), m_project (proj)
{
}

athletes_model::~athletes_model ()
{
}

int athletes_model::rowCount (const QModelIndex &parent) const
{
    Q_UNUSED (parent)
    return m_project.get_athletes ().size ();
}

int athletes_model::columnCount (const QModelIndex &parent) const
{
    Q_UNUSED (parent)
    return m_column_count;
}

QVariant athletes_model::headerData (int section, Qt::Orientation orientation, int role) const
{
  if (role != Qt::DisplayRole)
      return QVariant();

  if (orientation == Qt::Horizontal)
    return athlete_wrapper::get_string_by_section (section);
  else
    return section;

  return {};
}

QVariant athletes_model::data (const QModelIndex &index, int role) const
{
  auto athletes = m_project.get_athletes ();

  if (role == Qt::DisplayRole || role == Qt::EditRole)
    return athlete_wrapper (athletes[index.row()]).get_data_by_section (index.column());

  return QVariant();
}

bool athletes_model::setData (const QModelIndex &index, const QVariant &value, int role)
{
  if (index.isValid() && role == Qt::EditRole)
    {
      athlete_wrapper (m_project.get_athletes ()[index.row()]).set_data_by_section (index.column(), value);
      emit dataChanged (index, index);
      return true;
    }

  return false;
}

Qt::ItemFlags athletes_model::flags (const QModelIndex &index) const
{
  return QAbstractItemModel::flags (index) | Qt::ItemIsEditable;
}
