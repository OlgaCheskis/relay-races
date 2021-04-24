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

#include "team.h"
#include "athlete.h"
#include "project.h"
#include <QString>
#include <array>

team_t::team_t (const project &proj, const std::vector<int> &members, type_of_relay type, gender_type_of_relay gtype) :
  m_members (members), m_type (type), m_gtype (gtype)
{
  switch (type)
    {
    case type_of_relay::free:
      for (auto &id: m_members)
        {
          m_time += proj.get_athletes ()[id].m_free;
          m_age += proj.get_athletes ()[id].m_age;
        }
      break;
    case type_of_relay::medley:
      m_time += proj.get_athletes ()[m_members[0]].m_back;
      m_time += proj.get_athletes ()[m_members[1]].m_breast;
      m_time += proj.get_athletes ()[m_members[2]].m_fly;
      m_time += proj.get_athletes ()[m_members[3]].m_free;

      for (auto &id: m_members)
        {
          m_age += proj.get_athletes ()[id].m_age;
        }
      break;
    }
  m_time += 1.5;
}

QString team_t::get_short_name (const project &proj) const
{
  auto &athletes = proj.get_athletes ();
  QString res = QString ("%1:%2:%3").arg (get_points()).arg (m_time).arg (m_age);

  for (auto &id: m_members)
    {
      res += ':';
      res += QString (athletes[id].m_name.c_str())[0];
    }

  return res;
}

QString team_t::get_long_name (const project &proj) const
{
  auto &athletes = proj.get_athletes ();
  QString res = QString ("%1:%2\n").arg (m_time).arg (m_age);

  for (auto &id: m_members)
    {
      res += '\n';
      res += athletes[id].m_name.c_str ();
      res += ':';
      res += QString (athletes[id].m_name.c_str())[0];

    }

  return res;
}

int team_t::get_points () const
{
  if (m_points < 0)
    calc_points ();

  return m_points;
}
//25m
//static std::array<std::array<std::array<double,8>,3>,2> base_points =
//std::vector<std::vector<std::vector<double>>> base_points =
//{
//  std::array<std::array<double,8>,3>{
//    std::array<double,8>{ 92.78,  92.76,  96.00, 101.16, 107.44, 121.44, 153.96, 323.71},
//    std::array<double,8>{109.80, 110.28, 111.27, 118.84, 128.62, 155.36, 198.08, 311.70},
//    std::array<double,8>{101.21, 100.70, 102.52, 108.16, 115.94, 133.17, 166.57, 280.19}
//  },
//  std::array<std::array<double,8>,3>{
//    std::array<double,8>{102.56, 100.76, 106.38, 112.54, 120.59, 137.45, 177.69, 340.46},
//    std::array<double,8>{120.56, 122.21, 125.08, 134.35, 144.90, 174.94, 229.42, 341.74},
//    std::array<double,8>{110.64, 109.18, 114.28, 120.05, 134.39, 154.01, 196.37, 354.25}
//  }
//};
//50m
static std::array<std::array<std::array<double,8>,3>,2> base_points =
{
  std::array<std::array<double,8>,3>{
    std::array<double,8>{ 95.33,  94.49,  97.46, 102.05, 108.53, 121.93, 150.59, 286.99},
    std::array<double,8>{112.13, 110.47, 111.79, 119.31, 127.05, 150.21, 200.48, 348.38},
    std::array<double,8>{102.82, 102.69, 104.30, 107.94, 116.91, 132.87, 165.55, 239.50},
  },
  std::array<std::array<double,8>,3>{
    std::array<double,8>{105.39, 104.03, 107.87, 114.02, 122.11, 137.99, 175.05, 322.94},
    std::array<double,8>{124.65, 124.25, 126.87, 134.12, 145.30, 171.34, 225.54, 353.02},
    std::array<double,8>{115.37, 112.51, 116.49, 122.43, 131.14, 150.28, 193.69, 311.99}
  }
};

void team_t::calc_points () const
{
  int age_ind = (m_age - 80) / 40;
  auto base_time = base_points[(int)m_type][(int)m_gtype][age_ind];
  auto retime = base_time / m_time;
  auto points = (retime * retime * retime) * 1000.;
  m_points = points;
}

void team_item::calculate_total_points () const
{
  m_total_points = get_team ().get_points ();
  if (m_children.size() > 0)
    m_total_points += m_children[0]->get_team ().get_points ();
}

int team_item::get_total_points () const
{
  if (m_total_points < 0)
    calculate_total_points ();

  return m_total_points;
}
