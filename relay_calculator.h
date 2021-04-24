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

#ifndef RELAY_CALCULATOR_H
#define RELAY_CALCULATOR_H

#include<vector>
#include<array>
#include<memory>

class project;
class sample_generator;
class team_item;
enum class type_of_relay;
enum class gender_type_of_relay;
enum class gender_t;
enum class compare_type_t
{
  by_time,
  by_points,
};

class sample_generator
{
public:
  sample_generator (std::vector<int>::const_iterator first_it, std::vector<int>::const_iterator last_it, int sample_size);
  bool next ();
  std::vector<int> get () const;
  bool is_valid () const;

private:
  std::vector<int>::const_iterator m_cur_it;
  std::vector<int>::const_iterator m_last_it;
  int m_sample_size = 0;
  std::unique_ptr<sample_generator> m_cur_sample;
};

class relay_calculator
{
public:
  relay_calculator (project &proj,
                    type_of_relay relay_type,
                    gender_type_of_relay gender_type);

  void calculate ();

private:
  project &m_project;
  type_of_relay m_relay_type;
  gender_type_of_relay m_gender_type;

  std::vector<std::unique_ptr<team_item>> generate_teams (const std::vector<int> &athlete_ids,
                                                          team_item *parent_item,
                                                          bool &broken_branch);

  std::vector<std::unique_ptr<team_item>> generate_mixed_teams (const std::vector<int> &athlete_m_ids,
                                                                const std::vector<int> &athlete_f_ids,
                                                                team_item *parent_item,
                                                                bool &broken_branch);

  std::vector<int> make_gender_ids (gender_t gender);
  team_item *create_team_item (const std::vector<int> &sample,
                               team_item *parent_item) const;
};

#endif //RELAY_CALCULATOR_H
