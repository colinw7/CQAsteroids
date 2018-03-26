#include <CAsteroidsLibI.h>
#include <CMathRand.h>

CPoint2D
CAsteroidsShip::
draw_coords_[] = {
  CPoint2D( 0.5,  0.0),
  CPoint2D(-0.5,  0.5),
  CPoint2D(-0.3,  0.0),
  CPoint2D(-0.5, -0.5),
};

CPoint2D
CAsteroidsShip::
collision_coords_[] = {
  CPoint2D( 0.5,  0.0),
  CPoint2D(-0.5,  0.5),
  CPoint2D(-0.3,  0.0),
  CPoint2D(-0.5, -0.5),
};

uint CAsteroidsShip::num_draw_coords_      = sizeof(draw_coords_)/sizeof(CPoint2D);
uint CAsteroidsShip::num_collision_coords_ = sizeof(collision_coords_)/sizeof(CPoint2D);

CAsteroidsShip::
CAsteroidsShip(const CAsteroids &app, double x, double y, double a,
               double dx, double dy, double da) :
 CAsteroidsObject(app, x, y, a, dx, dy, da, 0.1, 0, true),
 bullet_mgr_(app), visible_(true)
{
  if (! app_.getConfigValue("Ship", "size", size_))
    size_ = 0.03;

  if (! app_.getConfigValue("Ship", "rotateSpeed", rotateSpeed_))
    rotateSpeed_ = 0.008;

  if (! app_.getConfigValue("Ship", "thrust", thrust_))
    thrust_ = 0.003;

  if (! app_.getConfigValue("Ship", "thrustMax", thrustMax_))
    thrustMax_ = 0.01;

  if (! app_.getConfigValue("Ship", "bulletSize", bulletSize_))
    bulletSize_ = 0.01;

  if (! app_.getConfigValue("Ship", "bulletSpeed", bulletSpeed_))
    bulletSpeed_ = 0.01;

  if (! app_.getConfigValue("Ship", "bulletLife", bulletLife_))
    bulletLife_ = 0.6;

  if (! app_.getConfigValue("Ship", "bulletNum", bulletNum_))
    bulletNum_ = 4;

  ai_ = 0;

  setDrawCoords(draw_coords_, num_draw_coords_);

  setCollisionCoords(collision_coords_, num_collision_coords_);
}

void
CAsteroidsShip::
init()
{
  ai_ = 0;

  x_ = 0.5;
  y_ = 0.5;
  a_ = 0;

  dx_ = 0;
  dy_ = 0;
  da_ = 0;

  matrix_.setIdentity();
}

void
CAsteroidsShip::
intersect()
{
  if (! visible_) return;

  auto rocks = app_.getRockMgr()->getRocks();

  for (auto prock = rocks.begin(); prock != rocks.end(); ++prock) {
    if (! (*prock)->getRemove() && (*prock)->pointInside(x_, y_)) {
      (*prock)->hit();

      app_.shipDestroyed();

      init();

      break;
    }
  }

  bullet_mgr_.intersect();
}

void
CAsteroidsShip::
turnLeft()
{
  if (! visible_) return;

  a_ += rotateSpeed_;
}

void
CAsteroidsShip::
turnRight()
{
  if (! visible_) return;

  a_ -= rotateSpeed_;
}

void
CAsteroidsShip::
turnStop()
{
  if (! visible_) return;

  da_ = 0.0;
}

void
CAsteroidsShip::
thrust()
{
  if (! visible_) return;

  double t = thrust_;

  double tx, ty;

  matrix_.multiplyPoint(t, 0.0, &tx, &ty);

  double dx1 = dx_ + tx;
  double dy1 = dy_ + ty;

  double d = fabs(dx_*dx_ + dy_*dy_);

  if (d < thrustMax_) {
    dx_ = dx1;
    dy_ = dy1;
  }
}

bool
CAsteroidsShip::
fire()
{
  if (! visible_) return false;

  if (bullet_mgr_.getNumBullets() >= bulletNum_)
    return false;

  double x1r, y1r;

  matrix_.multiplyPoint(0.5*size_, 0, &x1r, &y1r);

  bullet_mgr_.addBullet(x_ + x1r, y_ + y1r, a_, bulletSize_, bulletSpeed_, bulletLife_);

  return true;
}

void
CAsteroidsShip::
hyperspace()
{
  if (! visible_) return;

  x_ = CMathRand::randInRange(0.0, 1.0);
  y_ = CMathRand::randInRange(0.0, 1.0);
}

void
CAsteroidsShip::
move()
{
  CAsteroidsObject::move();

  bullet_mgr_.move();
}

void
CAsteroidsShip::
draw()
{
  if (! visible_) return;

  CAsteroidsObject::draw();

  bullet_mgr_.draw();
}
