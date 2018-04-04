#include "CAsteroidsBigRock.h"
#include "CAsteroids.h"

CAsteroidsBigRock::
CAsteroidsBigRock(const CAsteroids &app, double x, double y, double a, double dx, double dy, double da) :
 CAsteroidsRock(app, x, y, a, dx, dy, da, CASTEROIDS_ROCK_BIG)
{
}

void
CAsteroidsBigRock::
hit()
{
  CAsteroidsObject::hit();

  app_.getObjectMgr()->createMediumRock(x_, y_, a_ + 0.25, -dx_,  dy_, da_);
  app_.getObjectMgr()->createMediumRock(x_, y_, a_ - 0.25,  dx_, -dy_, da_);
}
