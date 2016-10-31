#ifndef SCORE_HH_
# define SCORE_HH_

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

class Score
{
private:
  int score;
  std::vector<std::string> strings;
public:
  Score();
  ~Score();
  void add(int);
  void reset();
  void load(const std::string & filepath, int);
  void save(const std::string & filepath, const std::string & name);
  int getScore() const;
  std::vector<std::string> getHighScores() const;
};

#endif
