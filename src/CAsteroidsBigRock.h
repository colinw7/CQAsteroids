#ifndef CAsteroidsBigRock_H
#define CAsteroidsBigRock_H

#include <CAsteroidsRock.h>

class CAsteroidsBigRock : public CAsteroidsRock {
 public:
  CAsteroidsBigRock(const CAsteroids &app, const CPoint2D &p, double a,
                    const CVector2D &v, double da);

  void hit() override;
};

#endif
