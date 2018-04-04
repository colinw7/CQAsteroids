#include <CAsteroidsSmallRock.h>
#include <CAsteroids.h>

CAsteroidsSmallRock::
CAsteroidsSmallRock(const CAsteroids &app, const CPoint2D &p, double a,
                    const CVector2D &v, double da) :
 CAsteroidsRock(app, p, a, v, da, CAsteroidsRockType::SMALL)
{
}
