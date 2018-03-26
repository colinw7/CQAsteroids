#include <CAsteroidsLibI.h>

CAsteroidsSmallRock::
CAsteroidsSmallRock(const CAsteroids &app, double x, double y, double a,
                    double dx, double dy, double da) :
 CAsteroidsRock(app, x, y, a, dx, dy, da, CASTEROIDS_ROCK_SMALL)
{
}
