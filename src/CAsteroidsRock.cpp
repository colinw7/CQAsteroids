#include <CAsteroidsRock.h>
#include <CAsteroidsBigRock.h>
#include <CAsteroidsMediumRock.h>
#include <CAsteroidsSmallRock.h>
#include <CAsteroids.h>
#include <CAsteroidsShapeMgr.h>

int CAsteroidsRock::currentRockNum_ = 0;

CAsteroidsRockMgr::
CAsteroidsRockMgr(const CAsteroids &app) :
 app_(app)
{
  (void) app_.getConfigValue("BigRock"   , "score", bigRockScore_   );
  (void) app_.getConfigValue("BigRock"   , "size" , bigRockSize_    );
  (void) app_.getConfigValue("MediumRock", "score", mediumRockScore_);
  (void) app_.getConfigValue("MediumRock", "size" , mediumRockSize_ );
  (void) app_.getConfigValue("SmallRock" , "score", smallRockScore_ );
  (void) app_.getConfigValue("SmallRock" , "size" , smallRockSize_  );
}

CAsteroidsBigRock *
CAsteroidsRockMgr::
createBigRock(const CPoint2D &p, double angle, const CVector2D &v, double da)
{
  CAsteroidsBigRock *rock = new CAsteroidsBigRock(app_, p, angle, v, da);

  rocks_.push_back(rock);

  return rock;
}

CAsteroidsMediumRock *
CAsteroidsRockMgr::
createMediumRock(const CPoint2D &p, double angle, const CVector2D &v, double da)
{
  CAsteroidsMediumRock *rock = new CAsteroidsMediumRock(app_, p, angle, v, da);

  rocks_.push_back(rock);

  return rock;
}

CAsteroidsSmallRock *
CAsteroidsRockMgr::
createSmallRock(const CPoint2D &p, double angle, const CVector2D &v, double da)
{
  CAsteroidsSmallRock *rock = new CAsteroidsSmallRock(app_, p, angle, v, da);

  rocks_.push_back(rock);

  return rock;
}

void
CAsteroidsRockMgr::
removeRock(CAsteroidsRock *rock)
{
  rocks_.remove(rock);

  delete rock;
}

void
CAsteroidsRockMgr::
removeAll()
{
  for (auto &rock : rocks_)
    rock->setRemove();
}

//------

CAsteroidsRock::
CAsteroidsRock(const CAsteroids &app, const CPoint2D &p, double angle,
               const CVector2D &v, double da, CAsteroidsRockType type) :
 CAsteroidsObject(app, Type::ROCK, p, angle, v, da, 0.1, 0, true)
{
  color_ = CRGBA(0.76, 0.57, 0.27);

  if      (type == CAsteroidsRockType::BIG) {
    size_  = app_.getRockMgr()->getBigRockSize();
    score_ = app_.getRockMgr()->getBigRockScore();
  }
  else if (type == CAsteroidsRockType::MEDIUM) {
    size_  = app_.getRockMgr()->getMediumRockSize();
    score_ = app_.getRockMgr()->getMediumRockScore();
  }
  else if (type == CAsteroidsRockType::SMALL) {
    size_  = app_.getRockMgr()->getSmallRockSize();
    score_ = app_.getRockMgr()->getSmallRockScore();
  }

  ++currentRockNum_;

  currentRockNum_ %= 3;

  rockNum_ = currentRockNum_;

  //---

  auto shape_mgr = app_.getShapeMgr();

  switch (rockNum_) {
    default:
    case 0: {
      setDrawCoords     (shape_mgr->drawPoints     (CAsteroidsShapeMgr::Type::ROCK1));
      setCollisionCoords(shape_mgr->collisionPoints(CAsteroidsShapeMgr::Type::ROCK1));

      break;
    }
    case 1: {
      setDrawCoords     (shape_mgr->drawPoints     (CAsteroidsShapeMgr::Type::ROCK2));
      setCollisionCoords(shape_mgr->collisionPoints(CAsteroidsShapeMgr::Type::ROCK2));

      break;
    }
    case 2: {
      setDrawCoords     (shape_mgr->drawPoints     (CAsteroidsShapeMgr::Type::ROCK3));
      setCollisionCoords(shape_mgr->collisionPoints(CAsteroidsShapeMgr::Type::ROCK3));

      break;
    }
  }
}

CAsteroidsRock::
~CAsteroidsRock()
{
}

void
CAsteroidsRock::
destroy()
{
  app_.getRockMgr()->removeRock(this);
}

void
CAsteroidsRock::
hit()
{
  app_.playSound("rock.hit");

  CAsteroidsObject::hit();
}
