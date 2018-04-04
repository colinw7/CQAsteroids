#include "CAsteroidsRock.h"

class CAsteroidsMediumRock : public CAsteroidsRock {
 private:
  static double default_size_;

 public:
  CAsteroidsMediumRock(const CAsteroids &app,
                       double x, double y, double a,
                       double dx, double dy, double da);

  void hit();
};
