#include "CAsteroidsRock.h"

class CAsteroidsSmallRock : public CAsteroidsRock {
 private:
  static double default_size_;

 public:
  CAsteroidsSmallRock(const CAsteroids &app,
                      double x, double y, double a,
                      double dx, double dy, double da);
};
