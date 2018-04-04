#ifndef CAsteroidsSmallRock_H
#define CAsteroidsSmallRock_H

#include <CAsteroidsRock.h>

class CAsteroidsSmallRock : public CAsteroidsRock {
 public:
  CAsteroidsSmallRock(const CAsteroids &app, const CPoint2D &p, double a,
                      const CVector2D &v, double da);

 private:
  static double default_size_;
};

#endif
