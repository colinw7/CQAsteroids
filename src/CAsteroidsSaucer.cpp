#include <CAsteroidsLibI.h>

CPoint2D
CAsteroidsSaucer::
draw_coords1_[] = {
  CPoint2D( 0.50,  0.00),
  CPoint2D( 0.25,  0.25),
  CPoint2D(-0.25,  0.25),
  CPoint2D(-0.50,  0.00),
  CPoint2D(-0.25, -0.25),
  CPoint2D( 0.25, -0.25),
};

CPoint2D
CAsteroidsSaucer::
draw_coords2_[] = {
  CPoint2D( 0.50,  0.00),
  CPoint2D( 0.25,  0.25),
  CPoint2D(-0.25,  0.25),
  CPoint2D(-0.50,  0.00),
  CPoint2D(-0.25, -0.25),
  CPoint2D( 0.25, -0.25),
};

CPoint2D
CAsteroidsSaucer::
collision_coords_[] = {
  CPoint2D( 0.5, -0.25),
  CPoint2D( 0.5,  0.25),
  CPoint2D(-0.5,  0.25),
  CPoint2D(-0.5, -0.25),
};

int CAsteroidsSaucer::num_draw_coords1_ = sizeof(draw_coords1_)/sizeof(CPoint2D);
int CAsteroidsSaucer::num_draw_coords2_ = sizeof(draw_coords2_)/sizeof(CPoint2D);

int CAsteroidsSaucer::num_collision_coords_ = sizeof(collision_coords_)/sizeof(CPoint2D);

CAsteroidsSaucerMgr::
CAsteroidsSaucerMgr(const CAsteroids &app) :
 app_(app)
{
  if (! app_.getConfigValue("BigSaucer", "score", big_saucer_score_))
    big_saucer_score_ = 500;
  if (! app_.getConfigValue("BigSaucer", "size", big_saucer_size_))
    big_saucer_size_  = 0.03;
  if (! app_.getConfigValue("BigSaucer", "bulletSize", big_saucer_bulletSize_))
    big_saucer_bulletSize_ = 0.01;
  if (! app_.getConfigValue("BigSaucer", "bulletSpeed", big_saucer_bulletSpeed_))
    big_saucer_bulletSpeed_ = 0.01;
  if (! app_.getConfigValue("BigSaucer", "bulletLife", big_saucer_bulletLife_))
    big_saucer_bulletLife_ = 0.6;
  if (! app_.getConfigValue("BigSaucer", "bulletNum", big_saucer_bulletNum_))
    big_saucer_bulletNum_ = 4;
  if (! app_.getConfigValue("BigSaucer", "delay", big_saucer_delay_))
    big_saucer_delay_ = 100;
  if (! app_.getConfigValue("BigSaucer", "fireInterval", big_saucer_fireInterval_))
    big_saucer_fireInterval_ = 10;

  if (! app_.getConfigValue("SmallSaucer", "score", small_saucer_score_))
    small_saucer_score_ = 1000;
  if (! app_.getConfigValue("SmallSaucer", "size", small_saucer_size_))
    small_saucer_size_  = 0.015;
  if (! app_.getConfigValue("SmallSaucer", "bulletSize", big_saucer_bulletSize_))
    small_saucer_bulletSize_ = 0.01;
  if (! app_.getConfigValue("SmallSaucer", "bulletSpeed", big_saucer_bulletSpeed_))
    small_saucer_bulletSpeed_ = 0.01;
  if (! app_.getConfigValue("SmallSaucer", "bulletLife", big_saucer_bulletLife_))
    small_saucer_bulletLife_ = 0.6;
  if (! app_.getConfigValue("SmallSaucer", "bulletNum", big_saucer_bulletNum_))
    small_saucer_bulletNum_ = 4;
  if (! app_.getConfigValue("SmallSaucer", "delay", small_saucer_delay_))
    small_saucer_delay_ = 200;
  if (! app_.getConfigValue("SmallSaucer", "fireInterval", small_saucer_fireInterval_))
    small_saucer_fireInterval_ = 5;

  t_ = 0;
}

void
CAsteroidsSaucerMgr::
update()
{
  t_ += 1;

  if (t_ >= big_saucer_delay_) {
    if (saucers_.empty())
      app_.getObjectMgr()->createBigSaucer(0.0, 0.5, 0.004, 0.0);
  }

  if (saucers_.empty())
    restart();
}

CAsteroidsBigSaucer *
CAsteroidsSaucerMgr::
createBigSaucer(double x, double y, double dx, double dy)
{
  CAsteroidsBigSaucer *saucer = new CAsteroidsBigSaucer(app_, x, y, dx, dy);

  saucers_.push_back(saucer);

  return saucer;
}

void
CAsteroidsSaucerMgr::
removeSaucer(CAsteroidsSaucer *saucer)
{
  saucers_.remove(saucer);

  delete saucer;
}

void
CAsteroidsSaucerMgr::
restart()
{
  t_ = 0;
}

//------

CAsteroidsSaucer::
CAsteroidsSaucer(const CAsteroids &app, double x, double y,
                 double dx, double dy, CAsteroidsSaucerType type) :
 CAsteroidsObject(app, x, y, 0.0, dx, dy, 0.0, 0.1, 0, false),
 bullet_mgr_(app), type_(type)
{
  if      (type_ == CASTEROIDS_BIG_SAUCER) {
    size_         = app_.getSaucerMgr()->getBigSaucerSize        ();
    score_        = app_.getSaucerMgr()->getBigSaucerScore       ();
    bulletSize_   = app_.getSaucerMgr()->getBigSaucerBulletSize  ();
    bulletSpeed_  = app_.getSaucerMgr()->getBigSaucerBulletSpeed ();
    bulletLife_   = app_.getSaucerMgr()->getBigSaucerBulletLife  ();
    bulletNum_    = app_.getSaucerMgr()->getBigSaucerBulletNum   ();
    fireInterval_ = app_.getSaucerMgr()->getBigSaucerFireInterval();
  }
  else if (type_ == CASTEROIDS_SMALL_SAUCER) {
    size_         = app_.getSaucerMgr()->getSmallSaucerSize        ();
    score_        = app_.getSaucerMgr()->getSmallSaucerScore       ();
    bulletSize_   = app_.getSaucerMgr()->getSmallSaucerBulletSize  ();
    bulletSpeed_  = app_.getSaucerMgr()->getSmallSaucerBulletSpeed ();
    bulletLife_   = app_.getSaucerMgr()->getSmallSaucerBulletLife  ();
    bulletNum_    = app_.getSaucerMgr()->getSmallSaucerBulletNum   ();
    fireInterval_ = app_.getSaucerMgr()->getSmallSaucerFireInterval();
  }

  t_ = 0;

  if (type_ == CASTEROIDS_BIG_SAUCER)
    setDrawCoords(draw_coords1_, num_draw_coords1_);
  else
    setDrawCoords(draw_coords2_, num_draw_coords2_);

  setCollisionCoords(collision_coords_, num_collision_coords_);
}

CAsteroidsSaucer::
~CAsteroidsSaucer()
{
}

void
CAsteroidsSaucer::
move()
{
  CAsteroidsObject::move();

  bullet_mgr_.move();
}

void
CAsteroidsSaucer::
intersect()
{
  intersectRocks();

  bullet_mgr_.intersect();
}

void
CAsteroidsSaucer::
draw()
{
  ++t_;

  if ((t_ % fireInterval_) == 0) {
    if (bullet_mgr_.getNumBullets() >= bulletNum_)
      return;

    double x1r, y1r;

    matrix_.multiplyPoint(0.5*size_, 0, &x1r, &y1r);

    bullet_mgr_.addBullet(x_ + x1r, y_ + y1r, a_, bulletSize_, bulletSpeed_, bulletLife_);
  }

  bullet_mgr_.draw();
}

void
CAsteroidsSaucer::
intersectRocks()
{
  auto rocks = app_.getRockMgr()->getRocks();

  auto prock1 = rocks.begin();
  auto prock2 = rocks.end  ();;

  for ( ; prock1 != prock2; ++prock1) {
    if ((*prock1)->pointInside(x_, y_)) {
      (*prock1)->hit();
      remove_ = true;
      break;
    }
  }
}

void
CAsteroidsSaucer::
destroy()
{
  app_.getSaucerMgr()->removeSaucer(this);
}
