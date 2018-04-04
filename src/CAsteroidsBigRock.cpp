#include <CAsteroidsBigRock.h>
#include <CAsteroids.h>

CAsteroidsBigRock::
CAsteroidsBigRock(const CAsteroids &app, const CPoint2D &p, double a,
                  const CVector2D &v, double da) :
 CAsteroidsRock(app, p, a, v, da, CAsteroidsRockType::BIG)
{
}

void
CAsteroidsBigRock::
hit()
{
  CAsteroidsRock::hit();

  app_.getObjectMgr()->createMediumRock(p_, angle_ + 0.25, CVector2D(-v_.x(),  v_.y()), da_);
  app_.getObjectMgr()->createMediumRock(p_, angle_ - 0.25, CVector2D( v_.x(), -v_.y()), da_);
}
