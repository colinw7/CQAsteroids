#include "CAsteroidsTypes.h"

class CAsteroidsScore {
 private:
  const CAsteroids &app_;
  int               score_;
  double            size_;
  int               lives_;

 public:
  CAsteroidsScore(const CAsteroids &app);

  void reset();

  void add(int score);

  void die();

  int numLives() const { return lives_; }

  void draw();
};
