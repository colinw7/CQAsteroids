#include <CAsteroidsBigRock.h>
#include <CAsteroids.h>
#include <CMathRand.h>

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

  double breakSpeed = CMathRand::randInRange(1.1, 1.3);

  double vx = v_.x()*breakSpeed;
  double vy = v_.y()*breakSpeed;

  app_.getObjectMgr()->createMediumRock(p_, angle_ + 0.25, CVector2D(-vx,  vy), da_);
  app_.getObjectMgr()->createMediumRock(p_, angle_ - 0.25, CVector2D( vx, -vy), da_);
}
