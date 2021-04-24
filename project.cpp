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

#include "project.h"
#include "athlete.h"

project::project ()
{
  add_athlete ("Божик Павел", 38, gender_t::male, novalid_time, novalid_time, 31., 28.);
  add_athlete ("Жемчугов Александр", 33, gender_t::male, novalid_time, 35., 29.5, 27.5);
  add_athlete ("Кузякин Олег", 57, gender_t::male, 34., 36., 33., 28.5);
  add_athlete ("Мирзабекян Александр", 49, gender_t::male, 34, 36, novalid_time, 28.5);
  add_athlete ("Светлаков Андрей", 41, gender_t::male, 29.5, novalid_time, 27.5, 24.5);
  add_athlete ("Тарасов Антон", 42, gender_t::male, novalid_time, 35, novalid_time, novalid_time);
  add_athlete ("Федоров Владимир", 52, gender_t::male, novalid_time, 36., 33., 30.);
  add_athlete ("Циркин Артем", 37, gender_t::male, novalid_time, 33., 29., 26.);
  add_athlete ("Жигарева Анастасия", 37, gender_t::female, novalid_time, 42, novalid_time, 33.);
  add_athlete ("Пешкова Валентина", 41, gender_t::female, novalid_time, 48., novalid_time, 38.);
  add_athlete ("Трофимова Юлия", 46, gender_t::female, novalid_time, 42., 38., 33.);
  add_athlete ("Ческис Ольга", 47, gender_t::female, 35.5, 43., 34.5, 30.);
}

int project::add_athlete (const std::string &name,
                          int age,
                          gender_t gender,
                          double back,
                          double breast,
                          double fly,
                          double free
             )
{
  athlete_t athlete = {name,
                       age,
                       gender,
                       back,
                       breast,
                       fly,
                       free};

  m_athletes.push_back (athlete);
  return m_athletes.size ();
}
