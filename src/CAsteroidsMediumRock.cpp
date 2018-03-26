#include <CAsteroidsLibI.h>

CAsteroidsMediumRock::
CAsteroidsMediumRock(const CAsteroids &app, double x, double y, double a,
                     double dx, double dy, double da) :
 CAsteroidsRock(app, x, y, a, dx, dy, da, CASTEROIDS_ROCK_MEDIUM)
{
}

void
CAsteroidsMediumRock::
hit()
{
  CAsteroidsObject::hit();

  app_.getObjectMgr()->createSmallRock(x_, y_, a_ + 0.25, -dx_,  dy_, da_);
  app_.getObjectMgr()->createSmallRock(x_, y_, a_ - 0.25,  dx_, -dy_, da_);
}
