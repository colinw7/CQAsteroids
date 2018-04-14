#include <CAsteroidsSmallRock.h>
#include <CAsteroidsExplosion.h>
#include <CAsteroids.h>

CAsteroidsSmallRock::
CAsteroidsSmallRock(const CAsteroids &app, const CPoint2D &p, double a,
                    const CVector2D &v, double da) :
 CAsteroidsRock(app, p, a, v, da, CAsteroidsRockType::SMALL)
{
}

void
CAsteroidsSmallRock::
hit()
{
  app_.getExplosionMgr()->addExplosion(this, p_);

  CAsteroidsRock::hit();
}
