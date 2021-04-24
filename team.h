/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

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

