#include <CAsteroidsShip.h>
#include <CAsteroidsBullet.h>
#include <CAsteroidsRock.h>
#include <CAsteroidsSaucer.h>
#include <CAsteroidsExplosion.h>
#include <CAsteroids.h>
#include <CAsteroidsShapeMgr.h>
#include <CMathRand.h>

CAsteroidsShip::
CAsteroidsShip(const CAsteroids &app, const CPoint2D &p, double angle,
               const CVector2D &v, double da) :
 CAsteroidsObject(app, Type::SHIP, p, angle, v, da, 0.1, 0, true)
{
  bulletMgr_ = new CAsteroidsBulletMgr(app, this);

  size_ = 0.03;

  //---

  (void) app_.getConfigValue("Ship", "size"       , size_       );
  (void) app_.getConfigValue("Ship", "rotateSpeed", rotateSpeed_);
  (void) app_.getConfigValue("Ship", "thrust"     , thrustSize_ );
  (void) app_.getConfigValue("Ship", "thrustMax"  , thrustMax_  );
  (void) app_.getConfigValue("Ship", "bulletSize" , bulletSize_ );
  (void) app_.getConfigValue("Ship", "bulletSpeed", bulletSpeed_);
  (void) app_.getConfigValue("Ship", "bulletLife" , bulletLife_ );
  (void) app_.getConfigValue("Ship", "bulletNum"  , bulletNum_  );

  //---

  color_ = CRGBA(0.9, 0.9, 0.0);

  auto shape_mgr = app_.getShapeMgr();

  setDrawCoords     (shape_mgr->drawPoints     (CAsteroidsShapeMgr::Type::SHIP));
  setCollisionCoords(shape_mgr->collisionPoints(CAsteroidsShapeMgr::Type::SHIP));
}

CAsteroidsShip::
~CAsteroidsShip()
{
  delete bulletMgr_;
}

void
CAsteroidsShip::
init()
{
  resetPosition();

  visible_ = true;

  exploding_   = 0;
  invunerable_ = 0;
}

void
CAsteroidsShip::
resetPosition()
{
  p_ = CPoint2D (0.5, 0.5);
  v_ = CVector2D(0.0, 0.0);
  a_ = CVector2D(0.0, 0.0);

  angle_ = 0;
  da_    = 0;

  matrix_.setIdentity();
}

void
CAsteroidsShip::
intersect()
{
  if (! isVisible() || exploding_ > 0 || invunerable_ > 0)
    return;

  bool hit = false;

  for (const auto &rock : app_.getRockMgr()->getRocks()) {
    if (! rock->isRemove() && rock->intersectObj(this)) {
      rock->hit();

      hit = true;

      break;
    }
  }

  CAsteroidsSaucer *saucer = app_.getSaucerMgr()->getVisibleSaucer();

  if (saucer && saucer->intersectObj(this)) {
    saucer->hit();

    hit = true;
  }

  if (hit)
    destroy();

  //---

  bulletMgr_->intersect();
}

void
CAsteroidsShip::
destroy()
{
  if (! isVisible() || exploding_ > 0 || invunerable_ > 0)
    return;

  app_.shipDestroyed();

  exploding_ = 50;

  app_.getExplosionMgr()->addExplosion(this, p_);
}

void
CAsteroidsShip::
turnLeft()
{
  if (! isVisible() || exploding_ > 0) return;

  da_ = app_.scaledValue(rotateSpeed_);
}

void
CAsteroidsShip::
turnRight()
{
  if (! isVisible() || exploding_ > 0) return;

  da_ = -app_.scaledValue(rotateSpeed_);
}

void
CAsteroidsShip::
turnStop()
{
  if (! isVisible() || exploding_ > 0) return;

  da_ = 0.0;
}

bool
CAsteroidsShip::
thrust()
{
  if (! isVisible() || exploding_ > 0)
    return false;

  double tx, ty;

  matrix_.multiplyPoint(thrustSize_, 0.0, &tx, &ty);

#if 0
  double dx1 = v_.x() + tx;
  double dy1 = v_.y() + ty;

  double d = v_.lengthSqr();

  if (d < thrustMax_)
    v_ = CVector2D(dx1, dy1);
#else
  CVector2D a(tx, ty);

  double d = a.lengthSqr();

  if (d < thrustMax_)
    a_ = a;
#endif

  auto shape_mgr = app_.getShapeMgr();

  setDrawCoords(shape_mgr->drawPoints(CAsteroidsShapeMgr::Type::SHIP_THRUST));

  return true;
}

void
CAsteroidsShip::
stopThrust()
{
  da_ = 0;

  auto shape_mgr = app_.getShapeMgr();

  setDrawCoords(shape_mgr->drawPoints(CAsteroidsShapeMgr::Type::SHIP));
}

bool
CAsteroidsShip::
fire()
{
  if (! isVisible() || exploding_ > 0) return false;

  if (bulletMgr_->getNumBullets() >= bulletNum_)
    return false;

  double x1r, y1r;

  matrix_.multiplyPoint(0.5*size_, 0, &x1r, &y1r);

  double bulletSpeed = app_.scaledValue(bulletSpeed_) + v_.length();

  bulletMgr_->addBullet(CPoint2D(p_.x + x1r, p_.y + y1r), angle_,
                        bulletSize_, bulletSpeed, bulletLife_);

  return true;
}

bool
CAsteroidsShip::
hyperspace()
{
  if (! isVisible() || exploding_ > 0)
    return false;

  resetPosition();

  p_ = CPoint2D(CMathRand::randInRange(0.0, 1.0), CMathRand::randInRange(0.0, 1.0));

  return true;
}

void
CAsteroidsShip::
move()
{
  if (! isVisible())
    return;

  assert(! app_.isGameOver());

  if (exploding_ > 0) {
    --exploding_;

    if (exploding_ <= 0) {
      init();

      invunerable_ = 50;

      CAsteroidsObject::move();
    }

    return;
  }

  if (invunerable_ > 0)
    --invunerable_;

  a_ *= 0.95;

  CAsteroidsObject::move();

  bulletMgr_->move();
}

CRGBA
CAsteroidsShip::
color() const
{
  if (invunerable_ > 0) {
    CRGBA c(0.5, 0.5, 0.5);

    c.setAlpha((50.0 - invunerable_)/50.0);

    return c;
  }
  else
    return CAsteroidsObject::color();
}

void
CAsteroidsShip::
draw()
{
  if (! isVisible() || exploding_ > 0) return;

  CAsteroidsObject::draw();

  bulletMgr_->draw();
}

void
CAsteroidsShip::
hit()
{
  CAsteroidsObject::hit();
}
