#include <CAsteroidsSaucer.h>
#include <CAsteroidsBigSaucer.h>
#include <CAsteroidsSmallSaucer.h>
#include <CAsteroidsBullet.h>
#include <CAsteroidsRock.h>
#include <CAsteroidsShip.h>
#include <CAsteroidsExplosion.h>
#include <CAsteroids.h>
#include <CAsteroidsShapeMgr.h>
#include <CMathRand.h>

CAsteroidsSaucerMgr::
CAsteroidsSaucerMgr(const CAsteroids &app) :
 app_(app)
{
  (void) app_.getConfigValue("BigSaucer", "score"       , bigSaucerScore_);
  (void) app_.getConfigValue("BigSaucer", "size"        , bigSaucerSize_);
  (void) app_.getConfigValue("BigSaucer", "bulletSize"  , bigSaucerBulletSize_);
  (void) app_.getConfigValue("BigSaucer", "bulletSpeed" , bigSaucerBulletSpeed_);
  (void) app_.getConfigValue("BigSaucer", "bulletLife"  , bigSaucerBulletLife_);
  (void) app_.getConfigValue("BigSaucer", "bulletNum"   , bigSaucerBulletNum_);
  (void) app_.getConfigValue("BigSaucer", "delay"       , bigSaucerDelay_);
  (void) app_.getConfigValue("BigSaucer", "fireInterval", bigSaucerFireInterval_);

  (void) app_.getConfigValue("SmallSaucer", "score"       , smallSaucerScore_);
  (void) app_.getConfigValue("SmallSaucer", "size"        , smallSaucerSize_);
  (void) app_.getConfigValue("SmallSaucer", "bulletSize"  , smallSaucerBulletSize_);
  (void) app_.getConfigValue("SmallSaucer", "bulletSpeed" , smallSaucerBulletSpeed_);
  (void) app_.getConfigValue("SmallSaucer", "bulletLife"  , smallSaucerBulletLife_);
  (void) app_.getConfigValue("SmallSaucer", "bulletNum"   , smallSaucerBulletNum_);
  (void) app_.getConfigValue("SmallSaucer", "delay"       , smallSaucerDelay_);
  (void) app_.getConfigValue("SmallSaucer", "fireInterval", smallSaucerFireInterval_);
}

CAsteroidsSaucerMgr::
~CAsteroidsSaucerMgr()
{
  delete bigSaucer_;
  delete smallSaucer_;
}

void
CAsteroidsSaucerMgr::
init()
{
  bigSaucer_   = app_.getObjectMgr()->createBigSaucer  ();
  smallSaucer_ = app_.getObjectMgr()->createSmallSaucer();
}

CAsteroidsSaucer *
CAsteroidsSaucerMgr::
getVisibleSaucer() const
{
  if (bigSaucer_->isVisible())
    return bigSaucer_;

  if (smallSaucer_->isVisible())
    return smallSaucer_;

  return nullptr;
}

void
CAsteroidsSaucerMgr::
update()
{
  t1_ += 1;

  if (bigSaucer_->isVisible() || smallSaucer_->isVisible())
    return;

  if (t1_ >= bigSaucerDelay_) {
    t2_ += 1;

    if (t2_ >= smallSaucerDelay_)
      showSmallSaucer(CPoint2D(0.0, 0.75), CVector2D(0.006, 0.0));
    else
      showBigSaucer(CPoint2D(0.0, 0.75), CVector2D(0.004, 0.0));
  }
}

void
CAsteroidsSaucerMgr::
showBigSaucer(const CPoint2D &p, const CVector2D &v)
{
  bigSaucer_->setVisible (true);
  bigSaucer_->setPos     (p);
  bigSaucer_->setVelocity(v);
}

void
CAsteroidsSaucerMgr::
showSmallSaucer(const CPoint2D &p, const CVector2D &v)
{
  smallSaucer_->setVisible (true);
  smallSaucer_->setPos     (p);
  smallSaucer_->setVelocity(v);
}

void
CAsteroidsSaucerMgr::
reset()
{
  bigSaucer_->setVisible(false);
  bigSaucer_->reset();

  smallSaucer_->setVisible(false);
  smallSaucer_->reset();

  t1_ = 0;
  t2_ = 0;
}

void
CAsteroidsSaucerMgr::
restart(CAsteroidsSaucerType type)
{
  if      (type == CAsteroidsSaucerType::BIG) {
    t1_ = 0;
  }
  else if (type == CAsteroidsSaucerType::SMALL) {
    t1_ = 0;
    t2_ = 0;
  }
}

std::string
CAsteroidsSaucerMgr::
statusStr() const
{
  std::string str = "SaucerMgr:";

  str += " " + std::to_string(t1_) + "," + std::to_string(t2_);

  if (bigSaucer_->isVisible())
    str += " Big";

  if (smallSaucer_->isVisible())
    str += " Small";

  return str;
}

//------

CAsteroidsSaucer::
CAsteroidsSaucer(const CAsteroids &app, CAsteroidsSaucerType type) :
 CAsteroidsObject(app, CAsteroidsObject::Type::SAUCER, CPoint2D(0.0, 0.0), 0.0,
                  CVector2D(0.0, 0.0), 0.0, 0.1, 0, false),
 type_(type)
{
  bulletMgr_ = new CAsteroidsBulletMgr(app, this);

  if      (type_ == CAsteroidsSaucerType::BIG) {
    size_         = app_.getSaucerMgr()->getBigSaucerSize        ();
    score_        = app_.getSaucerMgr()->getBigSaucerScore       ();
    bulletSize_   = app_.getSaucerMgr()->getBigSaucerBulletSize  ();
    bulletSpeed_  = app_.getSaucerMgr()->getBigSaucerBulletSpeed ();
    bulletLife_   = app_.getSaucerMgr()->getBigSaucerBulletLife  ();
    bulletNum_    = app_.getSaucerMgr()->getBigSaucerBulletNum   ();
    fireInterval_ = app_.getSaucerMgr()->getBigSaucerFireInterval();
  }
  else if (type_ == CAsteroidsSaucerType::SMALL) {
    size_         = app_.getSaucerMgr()->getSmallSaucerSize        ();
    score_        = app_.getSaucerMgr()->getSmallSaucerScore       ();
    bulletSize_   = app_.getSaucerMgr()->getSmallSaucerBulletSize  ();
    bulletSpeed_  = app_.getSaucerMgr()->getSmallSaucerBulletSpeed ();
    bulletLife_   = app_.getSaucerMgr()->getSmallSaucerBulletLife  ();
    bulletNum_    = app_.getSaucerMgr()->getSmallSaucerBulletNum   ();
    fireInterval_ = app_.getSaucerMgr()->getSmallSaucerFireInterval();
  }

  t_ = 0;

  //---

  color_ = CRGBA(0.9, 0.0, 0.0);

  auto shape_mgr = CAsteroidsShapeMgrInst;

  if (type_ == CAsteroidsSaucerType::BIG) {
    setDrawCoords     (shape_mgr->drawPoints     (CAsteroidsShapeMgr::Type::BIG_SAUCER));
    setCollisionCoords(shape_mgr->collisionPoints(CAsteroidsShapeMgr::Type::BIG_SAUCER));
  }
  else {
    setDrawCoords     (shape_mgr->drawPoints     (CAsteroidsShapeMgr::Type::SMALL_SAUCER));
    setCollisionCoords(shape_mgr->collisionPoints(CAsteroidsShapeMgr::Type::SMALL_SAUCER));
  }
}

CAsteroidsSaucer::
~CAsteroidsSaucer()
{
  delete bulletMgr_;
}

void
CAsteroidsSaucer::
reset()
{
  bulletMgr_->reset();
}

void
CAsteroidsSaucer::
move()
{
  if (visible_)
    CAsteroidsObject::move();

  bulletMgr_->move();
}

void
CAsteroidsSaucer::
intersect()
{
  if (visible_)
    intersectRocks();

  bulletMgr_->intersect();
}

void
CAsteroidsSaucer::
draw()
{
  if (visible_) {
    CAsteroidsObject::draw();

    ++t_;

    if ((t_ % fireInterval_) == 0) {
      if (bulletMgr_->getNumBullets() >= bulletNum_)
        return;

      double x1r, y1r;

      matrix_.multiplyPoint(0.5*size_, 0, &x1r, &y1r);

      CPoint2D bulletPos(p_.x + x1r, p_.y + y1r);

      const CPoint2D &shipPos = app_.getShip()->pos();

      CAsteroidsBullet *bullet =
        bulletMgr_->addBullet(bulletPos, 0.0, bulletSize_, bulletSpeed_, bulletLife_);

      double a = atan2(shipPos.y - bulletPos.y, shipPos.x - bulletPos.x)/(2*M_PI);

      a += CMathRand::randInRange(-0.1, 0.1);

      bullet->setDirection(a);

      if (type_ == CAsteroidsSaucerType::SMALL)
        bullet->setTarget(app_.getShip());

      app_.playSound("saucer.fire");
    }
  }

  bulletMgr_->draw();
}

void
CAsteroidsSaucer::
intersectRocks()
{
  assert(visible_);

  for (const auto &rock : app_.getRockMgr()->getRocks()) {
    if (rock->intersectObj(this)) {
      rock->hit();

      destroy();

      break;
    }
  }
}

void
CAsteroidsSaucer::
remove()
{
  destroy();
}

void
CAsteroidsSaucer::
destroy()
{
  if (! visible_)
    return;

  app_.getExplosionMgr()->addExplosion(this, p_);

  auto mgr = app_.getSaucerMgr();

  mgr->restart(type_);

  visible_ = false;
}

void
CAsteroidsSaucer::
hit()
{
  if (! visible_)
    return;

  app_.playSound("saucer.hit");

  CAsteroidsObject::hit();
}
