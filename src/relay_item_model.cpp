#include "relay_item_model.h"
#include "project.h"
#include "team.h"
#include "relay_calculator.h"

relay_item_model::relay_item_model (project &proj, QObject *parent)
    : QAbstractItemModel (parent), m_project (proj)
{
}

QModelIndex relay_item_model::index (int row, int column, const QModelIndex &parent) const
{
  team_item *parent_item = nullptr;
  if (parent.isValid ())
    parent_item = static_cast<team_item *>(parent.internalPointer());

  if (row >= 0)
    {
      auto *child_item = item (row, parent_item);
      if (child_item)
        return createIndex (row, column, child_item);
    }

  return QModelIndex();
}

QModelIndex relay_item_model::parent (const QModelIndex &child) const
{
  if (child.isValid ())
    {
      auto *child_item = static_cast<team_item *>(child.internalPointer ());
      auto *parent_item = parent (child_item);
      if (parent_item)
          return createIndex (row (parent_item), 0, parent_item);
    }

  return QModelIndex();
}

int relay_item_model::rowCount (const QModelIndex &parent) const
{
  if (parent.isValid ())
    {
      auto *parent_item = static_cast<team_item *>(parent.internalPointer());
      if (parent_item)
        return qMin<size_t> (parent_item->get_children ().size (), 2);
    }
  else
    {
      return m_project.get_team_tree ().size ();
    }

  return 0;
}

int relay_item_model::columnCount (const QModelIndex &parent) const
{
    Q_UNUSED (parent);
    return 4;
}

QVariant relay_item_model::data (const QModelIndex &index, int role) const
{
  if (!index.isValid())
      return QVariant();

  auto *item = static_cast<team_item *>(index.internalPointer());
  if (!item)
    return QVariant();
  if (index.column () >= (int)item->get_perm_teams ().size ())
    return QVariant();

  if (role == Qt::DisplayRole)
    return QString ("%1| %2").arg (index.row ()).arg (item->get_perm_teams ()[index.column ()].get_short_name (m_project)) ;
  else if (role == Qt::ToolTipRole)
    return QString ("%1").arg (item->get_perm_teams ()[index.column ()].get_long_name (m_project)) ;

  return QVariant();
}

QVariant relay_item_model::headerData (int section, Qt::Orientation orientation, int role) const
{
  return QAbstractItemModel::headerData (section, orientation, role);
}

Qt::ItemFlags relay_item_model::flags (const QModelIndex &index) const
{
  return QAbstractItemModel::flags (index);
}

team_item *relay_item_model::item (int row, team_item *parent) const
{
  auto &v = parent ? parent->get_children () : m_project.get_team_tree ();
  if (row < (int)v.size () && row >= 0)
    return v[row].get ();

  return nullptr;
}

team_item *relay_item_model::parent (team_item *child) const
{
  return child ? child->get_parent () : nullptr;
}

int relay_item_model::row (const team_item *item) const
{
  if (item)
    return item->get_row ();

  return -1;
}

void relay_item_model::calculate ()
{
  beginResetModel ();
  relay_calculator calculator (m_project, type_of_relay::medley, gender_type_of_relay::mixed);
  calculator.calculate ();
  endResetModel ();
}
