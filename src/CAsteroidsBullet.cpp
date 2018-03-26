#include <CAsteroidsLibI.h>
#include <CFuncs.h>

CPoint2D
CAsteroidsBullet::
draw_coords_[] = {
  CPoint2D(-0.1, -0.1),
  CPoint2D( 0.1, -0.1),
  CPoint2D(-0.1,  0.1),
  CPoint2D( 0.1,  0.1),
};

CPoint2D
CAsteroidsBullet::
collision_coords_[] = {
  CPoint2D(-0.1, -0.1),
  CPoint2D( 0.1, -0.1),
  CPoint2D(-0.1,  0.1),
  CPoint2D( 0.1,  0.1),
};

int CAsteroidsBullet::num_draw_coords_      = sizeof(draw_coords_)/sizeof(CPoint2D);
int CAsteroidsBullet::num_collision_coords_ = sizeof(collision_coords_)/sizeof(CPoint2D);

CAsteroidsBulletMgr::
CAsteroidsBulletMgr(const CAsteroids &app) :
 app_(app)
{
}

CAsteroidsBulletMgr::
~CAsteroidsBulletMgr()
{
}

int
CAsteroidsBulletMgr::
getNumBullets()
{
  return bullets_.size();
}

void
CAsteroidsBulletMgr::
addBullet(double x, double y, double a, double size, double speed, double life)
{
  CAsteroidsBullet *bullet = new CAsteroidsBullet(app_, this, x, y, a, size, speed, life);

  bullets_.push_back(bullet);
}

void
CAsteroidsBulletMgr::
removeBullet(CAsteroidsBullet *bullet)
{
  bullets_.remove(bullet);

  delete bullet;
}

void
CAsteroidsBulletMgr::
move()
{
  for (auto &bullet : bullets_)
    bullet->move();

  std::list<CAsteroidsBullet *> oldObjects;
  std::list<CAsteroidsBullet *> newObjects;

  auto p1 = bullets_.begin();
  auto p2 = bullets_.end  ();

  for ( ; p1 != p2; ++p1) {
    if ((*p1)->getRemove())
      oldObjects.push_back(*p1);
    else
      newObjects.push_back(*p1);
  }

  for (p1 = oldObjects.begin(), p2 = oldObjects.end(); p1 != p2; ++p1)
    (*p1)->destroy();

  bullets_ = newObjects;
}

void
CAsteroidsBulletMgr::
intersect()
{
  for (auto &bullet : bullets_)
    bullet->intersect();
}

void
CAsteroidsBulletMgr::
draw()
{
  for (auto &bullet : bullets_)
    bullet->draw();
}

//-------

CAsteroidsBullet::
CAsteroidsBullet(const CAsteroids &app, CAsteroidsBulletMgr *bullet_mgr,
                 double x, double y, double a, double size, double speed, double life) :
 CAsteroidsObject(app, x, y, a, 0.0, 0.0, 0.0, size, 0, true),
 bullet_mgr_(bullet_mgr), speed_(speed), life_(life)
{
  matrix_.setRotation(2*M_PI*a_);

  matrix_.multiplyPoint(speed_, 0, &dx_, &dy_);

  d_ = 0.0;

  setDrawCoords(draw_coords_, num_draw_coords_);

  setCollisionCoords(collision_coords_, num_collision_coords_);
}

CAsteroidsBullet::
~CAsteroidsBullet()
{
}

void
CAsteroidsBullet::
move()
{
  d_ += speed_;

  if (d_ > life_)
    remove_ = true;

  CAsteroidsObject::move();
}

void
CAsteroidsBullet::
intersect()
{
  intersectRocks();

  intersectSaucers();
}

void
CAsteroidsBullet::
intersectRocks()
{
  auto rocks = app_.getRockMgr()->getRocks();

  auto prock1 = rocks.begin();
  auto prock2 = rocks.end  ();

  for ( ; prock1 != prock2; ++prock1) {
    if ((*prock1)->pointInside(x_, y_)) {
      (*prock1)->hit();
      remove_ = true;
      break;
    }
  }
}

void
CAsteroidsBullet::
intersectSaucers()
{
  CAsteroidsSaucerMgr *saucer_mgr = app_.getSaucerMgr();

  auto saucers = saucer_mgr->getSaucers();

  auto psaucer1 = saucers.begin();
  auto psaucer2 = saucers.end  ();

  for ( ; psaucer1 != psaucer2; ++psaucer1) {
    if ((*psaucer1)->pointInside(x_, y_)) {
      (*psaucer1)->hit();
      remove_ = true;
      break;
    }
  }
}

void
CAsteroidsBullet::
destroy()
{
  bullet_mgr_->removeBullet(this);
}
