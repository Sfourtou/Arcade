/*
** Timer.cpp for cpp_arcade in /Users/fourto_s/Projects/Epitech/Tek2/cpp_arcade/fourto_s/sources
**
** Made by Sebastien Fourtou
** Login   <fourto_s@epitech.net>
**
** Started on  Thu Mar 24 13:53:05 2016 Sebastien Fourtou
** Last update Sun Mar 27 14:05:55 2016 Sebastien Fourtou
*/

#include "Timer.hh"

Timer::Timer()
   : pause(false)
{
   gettimeofday(&t0, 0);
   gettimeofday(&t1, 0);
}

Timer::~Timer()
{
}

void Timer::startTime()
{
   gettimeofday(&t0, 0);
   gettimeofday(&t1, 0);
}

int Timer::getTimeElapsed()
{
  struct timeval result;

  gettimeofday(&t1, 0);
  timersub(&t1, &t0, &result);
  return (result.tv_usec);
}

int Timer::getTimeElapsedSec()
{
  struct timeval result;

  gettimeofday(&t1, 0);
  timersub(&t1, &t0, &result);

  return (result.tv_sec);
}

void Timer::resetTime()
{
  gettimeofday(&t0, 0);
}

void Timer::paused(bool new_pause)
{
  pause = new_pause;
}

bool Timer::isPaused()
{
  return (pause);
}
