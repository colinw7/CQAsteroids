#include <CAsteroidsMediumRock.h>
#include <CAsteroids.h>

CAsteroidsMediumRock::
CAsteroidsMediumRock(const CAsteroids &app, const CPoint2D &p, double a,
                     const CVector2D &v, double da) :
 CAsteroidsRock(app, p, a, v, da, CAsteroidsRockType::MEDIUM)
{
}

void
CAsteroidsMediumRock::
hit()
{
  CAsteroidsRock::hit();

  app_.getObjectMgr()->createSmallRock(p_, angle_ + 0.25, CVector2D(-v_.x(),  v_.y()), da_);
  app_.getObjectMgr()->createSmallRock(p_, angle_ - 0.25, CVector2D( v_.x(), -v_.y()), da_);
}
