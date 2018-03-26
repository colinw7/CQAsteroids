#include <CAsteroidsLibI.h>
#include <CFuncs.h>

CAsteroidsObjectMgr::
CAsteroidsObjectMgr(const CAsteroids &app) :
 app_(app)
{
}

CAsteroidsObjectMgr::
~CAsteroidsObjectMgr()
{
  for (auto p1 = objects_.begin(), p2 = objects_.end(); p1 != p2; ++p1)
    (*p1)->destroy();

  objects_.clear();
}

CAsteroidsShip *
CAsteroidsObjectMgr::
createShip()
{
  CAsteroidsShip *ship = new CAsteroidsShip(app_);

  addObject(ship);

  return ship;
}

CAsteroidsBigRock *
CAsteroidsObjectMgr::
createBigRock(double x, double y, double a, double dx, double dy, double da)
{
  CAsteroidsBigRock *rock = app_.getRockMgr()->createBigRock(x, y, a, dx,  dy, da);

  addObject(rock);

  return rock;
}

CAsteroidsMediumRock *
CAsteroidsObjectMgr::
createMediumRock(double x, double y, double a, double dx, double dy, double da)
{
  CAsteroidsMediumRock *rock = app_.getRockMgr()->createMediumRock(x, y, a, dx,  dy, da);

  addObject(rock);

  return rock;
}

CAsteroidsSmallRock *
CAsteroidsObjectMgr::
createSmallRock(double x, double y, double a, double dx, double dy, double da)
{
  CAsteroidsSmallRock *rock = app_.getRockMgr()->createSmallRock(x, y, a, dx,  dy, da);

  addObject(rock);

  return rock;
}

CAsteroidsBigSaucer *
CAsteroidsObjectMgr::
createBigSaucer(double x, double y, double dx, double dy)
{
  CAsteroidsBigSaucer *saucer = app_.getSaucerMgr()->createBigSaucer(x, y, dx, dy);

  addObject(saucer);

  return saucer;
}

void
CAsteroidsObjectMgr::
addObject(CAsteroidsObject *object)
{
  objects_.push_back(object);
}

void
CAsteroidsObjectMgr::
removeObject(CAsteroidsObject *object)
{
  objects_.remove(object);
}

void
CAsteroidsObjectMgr::
move()
{
  for (auto &object : objects_)
    object->move();

  std::list<CAsteroidsObject *> oldObjects;
  std::list<CAsteroidsObject *> newObjects;

  auto p1 = objects_.begin();
  auto p2 = objects_.end  ();

  for ( ; p1 != p2; ++p1) {
    if ((*p1)->getRemove())
      oldObjects.push_back(*p1);
    else
      newObjects.push_back(*p1);
  }

  for (p1 = oldObjects.begin(), p2 = oldObjects.end(); p1 != p2; ++p1)
    (*p1)->destroy();

  objects_ = newObjects;
}

void
CAsteroidsObjectMgr::
intersect()
{
  for (auto &object : objects_)
    object->intersect();
}

void
CAsteroidsObjectMgr::
draw()
{
  for (auto &object : objects_)
    object->draw();
}

//-------

CAsteroidsObject::
CAsteroidsObject(const CAsteroids &app, double x, double y, double a,
                 double dx, double dy, double da, double size,
                 int score, bool wrap_on_edge) :
 app_(app), x_(x), y_(y), a_(a), dx_(dx), dy_(dy), da_(da),
 size_(size), score_(score), wrap_on_edge_(wrap_on_edge),
 draw_coords_(), num_draw_coords_(0),
 coll_coords_(), num_coll_coords_(0)
{
  remove_ = false;

  matrix_.setRotation(2*M_PI*a_);
}

CAsteroidsObject::
~CAsteroidsObject()
{
}

void
CAsteroidsObject::
setDrawCoords(CPoint2D *draw_coords, uint num_draw_coords)
{
  num_draw_coords_ = num_draw_coords;

  draw_coords_ .resize(num_draw_coords);
  draw_coords1_.resize(num_draw_coords);

  for (uint i = 0; i < num_draw_coords; ++i)
    draw_coords_[i] = draw_coords[i];

  updateDrawCoords();
}

void
CAsteroidsObject::
setCollisionCoords(CPoint2D *coll_coords, uint num_coll_coords)
{
  num_coll_coords_ = num_coll_coords;

  coll_coords_ .resize(num_coll_coords);
  coll_coords1_.resize(num_coll_coords);

  for (uint i = 0; i < num_coll_coords; ++i)
    coll_coords_[i] = coll_coords[i];

  updateCollisionCoords();
}

void
CAsteroidsObject::
move()
{
  x_ += dx_;
  y_ += dy_;
  a_ += da_;

  if (wrap_on_edge_) {
    if (x_ > 1.0) x_ = 0.0;
    if (x_ < 0.0) x_ = 1.0;
    if (y_ > 1.0) y_ = 0.0;
    if (y_ < 0.0) y_ = 1.0;
  }
  else {
    if (x_ > 1.0) remove_ = true;
    if (x_ < 0.0) remove_ = true;
    if (y_ > 1.0) remove_ = true;
    if (y_ < 0.0) remove_ = true;
  }

  if (a_ < 0.0) a_ += 1.0;
  if (a_ > 1.0) a_ -= 1.0;

  matrix_.setRotation(2*M_PI*a_);

  updateDrawCoords();
  updateCollisionCoords();
}

void
CAsteroidsObject::
updateDrawCoords()
{
  double x, y;

  for (int i = 0; i < num_draw_coords_; i++) {
    x = draw_coords_[i].x*size_;
    y = draw_coords_[i].y*size_;

    matrix_.multiplyPoint(x, y, &draw_coords1_[i].x, &draw_coords1_[i].y);

    draw_coords1_[i].x += x_;
    draw_coords1_[i].y += y_;
  }

  bbox_.reset();

  for (int i = 0; i < num_draw_coords_; ++i)
    bbox_.add(draw_coords1_[i]);
}

void
CAsteroidsObject::
updateCollisionCoords()
{
  double x, y;

  for (int i = 0; i < num_coll_coords_; i++) {
    x = coll_coords_[i].x*size_;
    y = coll_coords_[i].y*size_;

    matrix_.multiplyPoint(x, y, &coll_coords1_[i].x, &coll_coords1_[i].y);

    coll_coords1_[i].x += x_;
    coll_coords1_[i].y += y_;
  }
}

bool
CAsteroidsObject::
pointInside(double x, double y)
{
  if (! bbox_.inside(x, y))
    return false;

  CPolygon2D poly(&coll_coords1_[0], num_coll_coords_);

  return poly.inside(CPoint2D(x, y));
}

void
CAsteroidsObject::
draw()
{
  if (remove_) return;

  int i1 = num_draw_coords_ - 1;
  int i2 = 0;

  for ( ; i2 < num_draw_coords_; ++i2) {
    app_.drawLine(draw_coords1_[i1].x, draw_coords1_[i1].y,
                  draw_coords1_[i2].x, draw_coords1_[i2].y);

    i1 = i2;
  }

#ifdef SHOW_COLLISION
  i1 = num_coll_coords_ - 1;
  i2 = 0;

  for ( ; i2 < num_coll_coords_; ++i2) {
    app_.drawLine(coll_coords1_[i1].x, coll_coords1_[i1].y,
                  coll_coords1_[i2].x, coll_coords1_[i2].y);

    i1 = i2;
  }
#endif

#ifdef SHOW_BBOX
  double x1 = bbox_.getMin().x; double y1 = bbox_.getMin().y;
  double x2 = bbox_.getMax().x; double y2 = bbox_.getMax().y;

  app_.drawLine(x1, y1, x2, y1);
  app_.drawLine(x2, y1, x2, y2);
  app_.drawLine(x2, y2, x1, y2);
  app_.drawLine(x1, y2, x1, y1);
#endif
}

void
CAsteroidsObject::
hit()
{
  remove_ = true;

  app_.addScore(score_);
}

void
CAsteroidsObject::
destroy()
{
  delete this;
}
