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
  return bullets_.size();
}

CAsteroidsBullet *
CAsteroidsBulletMgr::
addBullet(const CPoint2D &p, double a, double size, double speed, double life)
{
  CAsteroidsBullet *bullet = new CAsteroidsBullet(app_, this, p, a, size, speed, life);

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
  for (auto &bullet : bullets_)
    bullet->move();

  Bullets oldBullets, newBullets;

  for (const auto &bullet : bullets_) {
    if (bullet->isRemove())
      oldBullets.push_back(bullet);
    else
      newBullets.push_back(bullet);
  }

  for (auto &bullet : oldBullets)
    bullet->destroy();

  bullets_ = newBullets;
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
                 const CPoint2D &p, double a, double size, double speed, double life) :
 CAsteroidsObject(app, CAsteroidsObject::Type::BULLET, p, a, CVector2D(0.0, 0.0), 0.0,
                  size, 0, true),
 bulletMgr_(bulletMgr), speed_(speed), life_(life)
{
  setDirection(a);

  d_ = 0.0;

  setDrawCoords     (CAsteroidsShapeMgrInst->drawPoints     (CAsteroidsShapeMgr::Type::BULLET));
  setCollisionCoords(CAsteroidsShapeMgrInst->collisionPoints(CAsteroidsShapeMgr::Type::BULLET));
}

CAsteroidsBullet::
~CAsteroidsBullet()
{
}

void
CAsteroidsBullet::
setDirection(double a)
{
  angle_ = a;

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

    double a = atan2(pos.y - p_.y, pos.x - p_.x)/(2*M_PI);

    setDirection(a);
  }

  d_ += speed_;

  if (d_ > life_)
    remove();

  CAsteroidsObject::move();
}

void
CAsteroidsBullet::
intersect()
{
  intersectRocks();

  if      (bulletMgr_->parent()->type() == CAsteroidsObject::Type::SHIP) {
    intersectSaucers(bulletMgr_->parent());
  }
  else if (bulletMgr_->parent()->type() == CAsteroidsObject::Type::SAUCER) {
    CAsteroidsShip *ship = app_.getShip();

    if (ship->pointInside(p_)) {
      ship->destroy();

      remove();
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

      remove();

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

    remove();
  }
}

void
CAsteroidsBullet::
destroy()
{
  bulletMgr_->removeBullet(this);
}
