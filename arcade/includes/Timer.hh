/*
** Timer.hh for cpp_arcade in /Users/fourto_s/Projects/Epitech/Tek2/cpp_arcade/fourto_s/includes
**
** Made by Sebastien Fourtou
** Login   <fourto_s@epitech.net>
**
** Started on  Thu Mar 24 13:49:59 2016 Sebastien Fourtou
** Last update Sun Mar 27 14:06:15 2016 Sebastien Fourtou
*/

#ifndef TIMER_HH_
#define TIMER_HH_

#include <sys/time.h>

class Timer
{
public:
  Timer();
  ~Timer();
private:
  struct timeval t0;
  struct timeval t1;
  bool pause;
public:
  void startTime();
  void resetTime();
  int getTimeElapsed();
  int getTimeElapsedSec();
  void paused(bool);
  bool isPaused();
};

#endif
