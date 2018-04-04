#ifndef CAsteroidsScore_H
#define CAsteroidsScore_H

#include <string>

class CAsteroids;

class CAsteroidsScore {
 public:
  CAsteroidsScore(const CAsteroids &app);

  void reset();

  void add(int score);

  void die();

  int numLives() const { return lives_; }

  void draw();

 private:
  const CAsteroids& app_;
  int               score_;
  double            size_;
  int               lives_;
};

#endif
