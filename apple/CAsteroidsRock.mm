#include "CAsteroidsBigRock.h"
#include "CAsteroidsMediumRock.h"
#include "CAsteroidsSmallRock.h"
#include "CAsteroids.h"

CPoint2D
CAsteroidsRock::
draw_coords1_[] = {
  CPoint2D(-0.250, -0.500),
  CPoint2D( 0.125, -0.500),
  CPoint2D( 0.250, -0.250),
  CPoint2D( 0.500, -0.250),
  CPoint2D( 0.500,  0.125),
  CPoint2D( 0.250,  0.125),
  CPoint2D( 0.375,  0.500),
  CPoint2D(-0.250,  0.500),
  CPoint2D(-0.500,  0.125),
  CPoint2D(-0.250,  0.000),
  CPoint2D(-0.500, -0.250),
};

CPoint2D
CAsteroidsRock::
draw_coords2_[] = {
  CPoint2D(-0.125, -0.500),
  CPoint2D( 0.375, -0.500),
  CPoint2D( 0.500, -0.250),
  CPoint2D( 0.500,  0.125),
  CPoint2D( 0.250,  0.500),
  CPoint2D(-0.375,  0.500),
  CPoint2D(-0.250,  0.250),
  CPoint2D(-0.500,  0.250),
  CPoint2D(-0.500, -0.125),
  CPoint2D(-0.125, -0.125),
  CPoint2D(-0.375, -0.250),
};

CPoint2D
CAsteroidsRock::
draw_coords3_[] = {
  CPoint2D(-0.250, -0.500),
  CPoint2D( 0.125, -0.500),
  CPoint2D( 0.250, -0.250),
  CPoint2D( 0.500, -0.375),
  CPoint2D( 0.500,  0.000),
  CPoint2D( 0.250,  0.125),
  CPoint2D( 0.125,  0.500),
  CPoint2D(-0.125,  0.500),
  CPoint2D(-0.250,  0.125),
  CPoint2D(-0.500,  0.125),
  CPoint2D(-0.500, -0.250),
  CPoint2D(-0.250, -0.250),
};

CPoint2D
CAsteroidsRock::
collision_coords_[] = {
  CPoint2D( 0.5, -0.5),
  CPoint2D( 0.5,  0.5),
  CPoint2D(-0.5,  0.5),
  CPoint2D(-0.5, -0.5),
};

uint CAsteroidsRock::num_draw_coords1_ = sizeof(draw_coords1_)/sizeof(CPoint2D);
uint CAsteroidsRock::num_draw_coords2_ = sizeof(draw_coords2_)/sizeof(CPoint2D);
uint CAsteroidsRock::num_draw_coords3_ = sizeof(draw_coords3_)/sizeof(CPoint2D);

uint CAsteroidsRock::num_collision_coords_ = sizeof(collision_coords_)/sizeof(CPoint2D);

uint CAsteroidsRock::current_rock_num_ = 0;

CAsteroidsRockMgr::
CAsteroidsRockMgr(const CAsteroids &app) :
 app_(app)
{
  int big_rock_score    = 20;
  int medium_rock_score = 50;
  int small_rock_score  = 100;

  big_rock_score = 20;
  big_rock_size_  = 0.07;

  medium_rock_score = 50;
  medium_rock_size_  = 0.035;

  small_rock_score = 100;
  small_rock_size_ = 0.0175;

  big_rock_score_    = big_rock_score;
  medium_rock_score_ = medium_rock_score;
  small_rock_score_  = small_rock_score;
}

CAsteroidsBigRock *
CAsteroidsRockMgr::
createBigRock(double x, double y, double a, double dx, double dy, double da)
{
  CAsteroidsBigRock *rock = new CAsteroidsBigRock(app_, x, y, a, dx,  dy, da);

  rocks_.push_back(rock);

  return rock;
}

CAsteroidsMediumRock *
CAsteroidsRockMgr::
createMediumRock(double x, double y, double a, double dx, double dy, double da)
{
  CAsteroidsMediumRock *rock = new CAsteroidsMediumRock(app_, x, y, a, dx,  dy, da);

  rocks_.push_back(rock);

  return rock;
}

CAsteroidsSmallRock *
CAsteroidsRockMgr::
createSmallRock(double x, double y, double a, double dx, double dy, double da)
{
  CAsteroidsSmallRock *rock = new CAsteroidsSmallRock(app_, x, y, a, dx,  dy, da);

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
  for (RockList::iterator p = rocks_.begin(); p != rocks_.end(); ++p)
    (*p)->setRemove();
}

//------

CAsteroidsRock::
CAsteroidsRock(const CAsteroids &app, double x, double y, double a,
               double dx, double dy, double da, CAsteroidsRockType type) :
 CAsteroidsObject(app, x, y, a, dx, dy, da, 0.1, 0, true)
{
  if      (type == CASTEROIDS_ROCK_BIG) {
    size_  = app_.getRockMgr()->getBigRockSize();
    score_ = app_.getRockMgr()->getBigRockScore();
  }
  else if (type == CASTEROIDS_ROCK_MEDIUM) {
    size_  = app_.getRockMgr()->getMediumRockSize();
    score_ = app_.getRockMgr()->getMediumRockScore();
  }
  else if (type == CASTEROIDS_ROCK_SMALL) {
    size_  = app_.getRockMgr()->getSmallRockSize();
    score_ = app_.getRockMgr()->getSmallRockScore();
  }

  ++current_rock_num_;

  current_rock_num_ %= 3;

  rock_num_ = current_rock_num_;

  switch (rock_num_) {
    case 0:
      setDrawCoords(draw_coords1_, num_draw_coords1_);
      break;
    case 1:
      setDrawCoords(draw_coords2_, num_draw_coords2_);
      break;
    case 2:
      setDrawCoords(draw_coords3_, num_draw_coords3_);
      break;
    default:
      setDrawCoords(draw_coords1_, num_draw_coords1_);
      break;
  }

  setCollisionCoords(collision_coords_, num_collision_coords_);
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
