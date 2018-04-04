#include <CAsteroidsObject.h>
#include <CAsteroidsBigRock.h>
#include <CAsteroidsMediumRock.h>
#include <CAsteroidsSmallRock.h>
#include <CAsteroidsBigSaucer.h>
#include <CAsteroidsSmallSaucer.h>
#include <CAsteroidsShip.h>
#include <CAsteroids.h>
#include <CAsteroidsShapeMgr.h>
#include <CMathGeom2D.h>

CAsteroidsObjectMgr::
CAsteroidsObjectMgr(const CAsteroids &app) :
 app_(app)
{
}

CAsteroidsObjectMgr::
~CAsteroidsObjectMgr()
{
  for (auto &object : objects_)
    object->destroy();

  objects_.clear();
}

CAsteroidsShip *
CAsteroidsObjectMgr::
createShip()
{
  auto ship = new CAsteroidsShip(app_);

  addObject(ship);

  return ship;
}

CAsteroidsBigRock *
CAsteroidsObjectMgr::
createBigRock(const CPoint2D &p, double a, const CVector2D &v, double da)
{
  auto rock = app_.getRockMgr()->createBigRock(p, a, v, da);

  addObject(rock);

  return rock;
}

CAsteroidsMediumRock *
CAsteroidsObjectMgr::
createMediumRock(const CPoint2D &p, double a, const CVector2D &v, double da)
{
  auto rock = app_.getRockMgr()->createMediumRock(p, a, v, da);

  addObject(rock);

  return rock;
}

CAsteroidsSmallRock *
CAsteroidsObjectMgr::
createSmallRock(const CPoint2D &p, double a, const CVector2D &v, double da)
{
  auto rock = app_.getRockMgr()->createSmallRock(p, a, v, da);

  addObject(rock);

  return rock;
}

CAsteroidsBigSaucer *
CAsteroidsObjectMgr::
createBigSaucer()
{
  auto saucer = new CAsteroidsBigSaucer(app_);

  addObject(saucer);

  return saucer;
}

CAsteroidsSmallSaucer *
CAsteroidsObjectMgr::
createSmallSaucer()
{
  auto saucer = new CAsteroidsSmallSaucer(app_);

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

  Objects oldObjects, newObjects;

  for (auto &object : objects_) {
    if (object->isRemove())
      oldObjects.push_back(object);
    else
      newObjects.push_back(object);
  }

  for (auto &oldObject : oldObjects)
    oldObject->destroy();

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
CAsteroidsObject(const CAsteroids &app, Type type, const CPoint2D &p, double a,
                 const CVector2D &v, double da, double size, int score,
                 bool wrap_on_edge) :
 app_(app), type_(type), p_(p), v_(v), angle_(a), da_(da), size_(size),
 score_(score), wrap_on_edge_(wrap_on_edge)
{
  remove_ = false;

  matrix_.setRotation(2*M_PI*angle_);
}

CAsteroidsObject::
~CAsteroidsObject()
{
}

void
CAsteroidsObject::
setDrawCoords(const Points &draw_coords)
{
  auto num_draw_coords = draw_coords.size();

  draw_coords_ .resize(num_draw_coords);
  draw_coords1_.resize(num_draw_coords);

  for (std::size_t i = 0; i < num_draw_coords; ++i)
    draw_coords_[i] = draw_coords[i];

  updateDrawCoords();
}

void
CAsteroidsObject::
setCollisionCoords(const Points &coll_coords)
{
  auto num_coll_coords = coll_coords.size();

  coll_coords_ .resize(num_coll_coords);
  coll_coords1_.resize(num_coll_coords);

  for (std::size_t i = 0; i < num_coll_coords; ++i)
    coll_coords_[i] = coll_coords[i];

  updateCollisionCoords();
}

void
CAsteroidsObject::
move()
{
  v_     += a_;
  p_     += v_;
  angle_ += da_;

  if (wrap_on_edge_) {
    if (p_.x > 1.0) p_.x = 0.0;
    if (p_.x < 0.0) p_.x = 1.0;
    if (p_.y > 1.0) p_.y = 0.0;
    if (p_.y < 0.0) p_.y = 1.0;
  }
  else {
    if (p_.x > 1.0) remove();
    if (p_.x < 0.0) remove();
    if (p_.y > 1.0) remove();
    if (p_.y < 0.0) remove();
  }

  if (angle_ < 0.0) angle_ += 1.0;
  if (angle_ > 1.0) angle_ -= 1.0;

  matrix_.setRotation(2*M_PI*angle_);

  updateDrawCoords();

  updateCollisionCoords();
}

void
CAsteroidsObject::
updateDrawCoords()
{
  for (std::size_t i = 0; i < draw_coords_.size(); ++i) {
    double x = draw_coords_[i].x*size_;
    double y = draw_coords_[i].y*size_;

    matrix_.multiplyPoint(x, y, &draw_coords1_[i].x, &draw_coords1_[i].y);

    draw_coords1_[i].x += p_.x;
    draw_coords1_[i].y += p_.y;
  }

  bbox_.reset();

  for (std::size_t i = 0; i < draw_coords_.size(); ++i)
    bbox_.add(draw_coords1_[i]);
}

void
CAsteroidsObject::
updateCollisionCoords()
{
  for (std::size_t i = 0; i < coll_coords_.size(); ++i) {
    double x = coll_coords_[i].x*size_;
    double y = coll_coords_[i].y*size_;

    matrix_.multiplyPoint(x, y, &coll_coords1_[i].x, &coll_coords1_[i].y);

    coll_coords1_[i].x += p_.x;
    coll_coords1_[i].y += p_.y;
  }
}

bool
CAsteroidsObject::
pointInside(const CPoint2D &p) const
{
  if (! bbox_.inside(p.x, p.y))
    return false;

  if (! CMathGeom2D::PointInsideConvex(p, &coll_coords1_[0], coll_coords_.size()))
    return false;

  return true;
}

bool
CAsteroidsObject::
intersectObj(const CAsteroidsObject *obj) const
{
  std::vector<CPoint2D> ipoints;

  if (! CMathGeom2D::IntersectPolygons(coll_coords1_, obj->coll_coords1_, ipoints))
    return false;

  return true;
}

void
CAsteroidsObject::
draw()
{
  if (isRemove()) return;

  if (app_.isColored())
     app_.setColor(color());

  if (app_.isFilled())
    app_.fillPolygon(draw_coords1_);
  else
    app_.drawPolygon(draw_coords1_);

#ifdef SHOW_COLLISION
  app_.drawPolygon(coll_coords1_);
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
  remove();

  app_.addScore(score_);
}

void
CAsteroidsObject::
remove()
{
  remove_ = true;
}

void
CAsteroidsObject::
destroy()
{
  delete this;
}
