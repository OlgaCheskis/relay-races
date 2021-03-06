#ifndef TEAM_H
#define TEAM_H

#include<vector>
#include<memory>

class project;
class QString;

enum class type_of_relay
{
  free = 0,
  medley,
};

enum class gender_type_of_relay
{
  male = 0,
  female,
  mixed,
};


class team_t
{
public:
  team_t () = default;
  team_t (const project &proj, const std::vector<int> &members,
          type_of_relay type,
          gender_type_of_relay gender_type);

  int get_age () const {return m_age;}
  double get_time () const {return m_time;}

  QString get_short_name (const project &proj) const;
  QString get_long_name (const project &proj) const;

  int get_points () const;

private:
  int m_age = 0;
  mutable int m_points = -1;
  double m_time = 0;
  std::vector<int> m_members;
  type_of_relay m_type = type_of_relay::free;
  gender_type_of_relay m_gtype = gender_type_of_relay::male;

  void calc_points () const;
};

class team_item
{
public:
  team_item (std::vector<team_t> &&perm_teams, team_item *parent)
    : m_perm_teams (perm_teams), m_parent (parent){}

  void set_children (std::vector<std::unique_ptr<team_item>> &&children)
  {
    m_children = std::move (children);
  }

  const std::vector<std::unique_ptr<team_item>> &get_children () const
  {
    return m_children;
  }

  const team_t &get_team () const {return *m_perm_teams.data();}
  team_item *get_parent () const {return m_parent;}
  const std::vector<team_t> &get_perm_teams () const {return m_perm_teams;};
  int get_row () const {return m_row;}
  void set_row (int row) {m_row = row;}
  int get_total_points () const;


private:
  std::vector<team_t> m_perm_teams;
  team_item *m_parent = nullptr;
  std::vector<std::unique_ptr<team_item>> m_children;
  int m_row = 0;
  mutable int m_total_points = -1;
  void calculate_total_points () const;
};

#endif //TEAM_H

