#include <CAsteroidsLibI.h>

CAsteroidsScore::
CAsteroidsScore(const CAsteroids &app) :
 app_(app)
{
  reset();
}

void
CAsteroidsScore::
reset()
{
  score_ = 0;
  size_  = 0.03;
  lives_ = 3;
}

void
CAsteroidsScore::
add(int score)
{
  score_ += score;
}

void
CAsteroidsScore::
die()
{
  if (lives_ > 0)
    --lives_;
}

void
CAsteroidsScore::
draw()
{
  std::string str = CStrUtil::toString(score_);

  while (str.size() < 5)
    str = "0" + str;

  double x = 0.0;
  double y = 0.01;

  int len = str.size();

  for (int i = 0; i < len; i++) {
    app_.drawChar(x, y, size_, str[i]);

    x += size_;
  }

  x = 0.99 - size_;
  y = 0.01;

  for (int i = 0; i < lives_; i++) {
    app_.drawChar(x, y, size_, 'A');

    x -= size_;
  }
}
