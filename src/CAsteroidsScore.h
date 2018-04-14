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
  int               score_ { 0 };
  double            size_  { 1.0 };
  int               lives_ { 4 };
};

#endif
