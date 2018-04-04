#include "CAsteroidsRock.h"

class CAsteroidsBigRock : public CAsteroidsRock {
 private:
  static double default_size_;

 public:
  CAsteroidsBigRock(const CAsteroids &app,
                    double x, double y, double a,
                    double dx, double dy, double da);

  void hit();
};
