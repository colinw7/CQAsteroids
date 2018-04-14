#include <CAsteroidsMediumRock.h>
#include <CAsteroids.h>
#include <CMathRand.h>

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

  double breakSpeed = CMathRand::randInRange(1.1, 1.3);

  double vx = v_.x()*breakSpeed;
  double vy = v_.y()*breakSpeed;

  app_.getObjectMgr()->createSmallRock(p_, angle_ + 0.25, CVector2D(-vx,  vy), da_);
  app_.getObjectMgr()->createSmallRock(p_, angle_ - 0.25, CVector2D( vx, -vy), da_);
}
