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
