#ifndef CAsteroidsMediumRock_H
#define CAsteroidsMediumRock_H

#include <CAsteroidsRock.h>

class CAsteroidsMediumRock : public CAsteroidsRock {
 public:
  CAsteroidsMediumRock(const CAsteroids &app, const CPoint2D &p, double a,
                       const CVector2D &v, double da);

  void hit() override;
};

#endif
