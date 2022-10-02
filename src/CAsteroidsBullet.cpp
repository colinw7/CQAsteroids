#include <CAsteroidsBullet.h>
#include <CAsteroidsRock.h>
#include <CAsteroidsSaucer.h>
#include <CAsteroidsShip.h>
#include <CAsteroids.h>
#include <CAsteroidsShapeMgr.h>

CAsteroidsBulletMgr::
CAsteroidsBulletMgr(const CAsteroids &app, CAsteroidsObject *parent) :
 app_(app), parent_(parent)
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
  return int(bullets_.size());
}

CAsteroidsBullet *
CAsteroidsBulletMgr::
addBullet(const CPoint2D &p, double angle, double size, double speed, int life)
{
  CAsteroidsBullet *bullet = new CAsteroidsBullet(app_, this, p, angle, size, speed, life);

  bullets_.push_back(bullet);

  return bullet;
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
reset()
{
  for (auto &bullet : bullets_)
    delete bullet;

  bullets_.clear();
}

void
CAsteroidsBulletMgr::
move()
{
  if (bullets_.empty())
    return;

  for (auto &bullet : bullets_)
    bullet->move();

  Bullets oldBullets, newBullets;

  for (const auto &bullet : bullets_) {
    if (bullet->isRemove())
      oldBullets.push_back(bullet);
    else
      newBullets.push_back(bullet);
  }

  bullets_ = newBullets;

  for (auto &bullet : oldBullets)
    bullet->destroy();
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
CAsteroidsBullet(const CAsteroids &app, CAsteroidsBulletMgr *bulletMgr,
                 const CPoint2D &p, double angle, double size, double speed, int life) :
 CAsteroidsObject(app, Type::BULLET, p, angle, CVector2D(0.0, 0.0), 0.0, size, 0, true),
 bulletMgr_(bulletMgr), speed_(speed), life_(life)
{
  setDirection(angle);

  auto shape_mgr = app_.getShapeMgr();

  setDrawCoords     (shape_mgr->drawPoints     (CAsteroidsShapeMgr::Type::BULLET));
  setCollisionCoords(shape_mgr->collisionPoints(CAsteroidsShapeMgr::Type::BULLET));
}

CAsteroidsBullet::
~CAsteroidsBullet()
{
}

void
CAsteroidsBullet::
setDirection(double angle)
{
  angle_ = angle;

  matrix_.setRotation(2*M_PI*angle_);

  double dx, dy;

  matrix_.multiplyPoint(speed_, 0, &dx, &dy);

  v_ = CVector2D(dx, dy);
}

void
CAsteroidsBullet::
move()
{
  if (target_) {
    const CPoint2D &pos = target_->pos();

    double angle = atan2(pos.y - p_.y, pos.x - p_.x)/(2*M_PI);

    setDirection(angle);
  }

  age_ += 1;

  if (age_ > life_)
    removeLater();

  CAsteroidsObject::move();
}

void
CAsteroidsBullet::
intersect()
{
  intersectRocks();

  if      (bulletMgr_->parent()->type() == Type::SHIP) {
    intersectSaucers(bulletMgr_->parent());
  }
  else if (bulletMgr_->parent()->type() == Type::SAUCER) {
    CAsteroidsShip *ship = app_.getShip();

    if (ship->pointInside(p_)) {
      ship->destroy();

      removeLater();
    }
  }
  else
    assert(false);
}

void
CAsteroidsBullet::
intersectRocks()
{
  for (const auto &rock : app_.getRockMgr()->getRocks()) {
    if (rock->pointInside(p_)) {
      rock->hit();

      removeLater();

      break;
    }
  }
}

void
CAsteroidsBullet::
intersectSaucers(CAsteroidsObject *parent)
{
  CAsteroidsSaucer *saucer = app_.getSaucerMgr()->getVisibleSaucer();

  if (! saucer || saucer == parent)
    return;

  if (saucer->pointInside(p_)) {
    saucer->hit();

    removeLater();
  }
}

void
CAsteroidsBullet::
destroy()
{
  bulletMgr_->removeBullet(this);
}
