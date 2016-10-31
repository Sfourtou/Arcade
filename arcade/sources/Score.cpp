#include "Score.hh"

Score::Score() :
  score(0)
{
}

Score::~Score()
{
}

void Score::reset()
{
  score = 0;
}

void Score::add(int add)
{
  score += add;
}

bool mySortScore(std::string str, std::string str1)
{
  std::stringstream s(str);
  std::stringstream s1(str1);
  int nb;
  int nb1;

  s >> nb;
  s1 >> nb1;

  return (nb < nb1);
}

void Score::load(const std::string & filepath, int nb)
{
  std::ifstream afile (filepath, std::ios::in);
  int i = 0;

  strings.clear();
  if (afile.good() && afile.is_open())
  {
    std::string buffer;
    while (std::getline(afile, buffer))
      strings.push_back(buffer);
    afile.close();
  }
  else
    std::cout << "Unable to open score file " << filepath << std::endl;
  if (strings.size() > 1)
  {
    std::sort(strings.begin(), strings.end(), mySortScore);
    std::reverse(strings.begin(), strings.end());
    if (nb < strings.size())
      strings.erase(strings.begin() + nb, strings.end());
  }
}

void Score::save(const std::string & filepath, const std::string & name)
{
  std::ofstream afile (filepath, std::ios::app);

  if (afile.is_open())
  {
    if (name == "")
      afile << score << " " << "???" << std::endl;
    else
      afile << score << " " << name << std::endl;
    afile.close();
  }
}

int Score::getScore() const
{
  return score;
}

std::vector<std::string> Score::getHighScores() const
{
  return strings;
}
