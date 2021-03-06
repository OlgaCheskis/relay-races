#ifndef PROJECT_H
#define PROJECT_H

#include<string>
#include<vector>

#include "team.h"
#include "athlete.h"

class project
{
public:
  project ();

  int add_athlete (const std::string &name,
               int age,
               gender_t gender,
               double,
               double,
               double,
               double
               );

  const std::vector<athlete_t> &get_athletes () const {return m_athletes;}
  std::vector<athlete_t> &get_athletes () {return m_athletes;}

  const std::vector<std::unique_ptr<team_item>> &get_team_tree () const {return m_team_tree;}
  std::vector<std::unique_ptr<team_item>> &get_team_tree () {return m_team_tree;}
  void set_team_tree (std::vector<std::unique_ptr<team_item>> &&tems)
  {
    m_team_tree = std::move (tems);
  }

private:
  //std::map<int, athlete_t>  m_athletes;
  std::vector<athlete_t>  m_athletes;
  std::vector<std::unique_ptr<team_item>>  m_team_tree;
};

#endif
