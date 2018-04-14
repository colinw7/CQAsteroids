#include <CAsteroidsExplosion.h>
#include <CAsteroids.h>
#include <CMathRand.h>

CAsteroidsExplosionMgr::
CAsteroidsExplosionMgr(CAsteroids &app) :
 app_(app)
{
}

CAsteroidsExplosionMgr::
~CAsteroidsExplosionMgr()
{
  removeAll();
}

void
CAsteroidsExplosionMgr::
addExplosion(CAsteroidsObject *parent, const CPoint2D &p)
{
  CAsteroidsExplosion *explosion = new CAsteroidsExplosion(app_, parent, p);

  explosions_.push_back(explosion);
}

void
CAsteroidsExplosionMgr::
removeAll()
{
  for (auto &explosion : explosions_)
    delete explosion;

  explosions_.clear();
}

void
CAsteroidsExplosionMgr::
update()
{
  Explosions oldExplosions, newExplosions;

  for (auto &explosion : explosions_) {
    explosion->move();

    if (explosion->isRemove())
      oldExplosions.push_back(explosion);
    else
      newExplosions.push_back(explosion);
  }

  if (! oldExplosions.empty()) {
    for (auto &explosion : oldExplosions)
      delete explosion;

    explosions_ = newExplosions;
  }
}

void
CAsteroidsExplosionMgr::
draw()
{
  for (auto &explosion : explosions_)
    explosion->draw();
}

//------

CAsteroidsExplosion::
CAsteroidsExplosion(const CAsteroids &app, CAsteroidsObject *parent, const CPoint2D &p) :
 CAsteroidsObject(app, CAsteroidsObject::Type::EXPLOSION, p, 0.0, CVector2D(0.0, 0.0), 0.0,
                  0.1, 0, true), parent_(parent)
{
  const int num_lines = 10;

  for (int i = 0; i < num_lines; ++i) {
    double dx = CMathRand::randInRange(-0.01, 0.01);
    double dy = CMathRand::randInRange(-0.01, 0.01);
    double lx = CMathRand::randInRange(0.5, 1.0);
    double ly = CMathRand::randInRange(0.5, 1.0);
    double vx = CMathRand::randInRange(5, 10);
    double vy = CMathRand::randInRange(5, 10);

    CPoint2D p1(p_.x +    dx, p_.y +    dy);
    CPoint2D p2(p1.x + lx*dx, p1.y + ly*dy);

    Line l(p1, p2);

    l.v = app_.scaledSpeed(vx*dx, vy*dy);

    l.da = CMathRand::randInRange(0.0, 0.1);

    l.life = CMathRand::randInRange(0, life_);

    lines_.push_back(l);
  }
}

CAsteroidsExplosion::
~CAsteroidsExplosion()
{
}

void
CAsteroidsExplosion::
init()
{
}

void
CAsteroidsExplosion::
move()
{
  --life_;

  for (auto &line : lines_) {
    --line.life;

    line.p1.x += line.v.x();
    line.p1.y += line.v.y();

    line.p2.x += line.v.x();
    line.p2.y += line.v.y();
  }
}

void
CAsteroidsExplosion::
draw()
{
  if (app_.isColored()) {
    double r = 1.0;
    double g = 1.0;
    double b = 0.0;
    double a = 1.0*life_/initLife_;

    app_.setColor(CRGBA(r, g, b, a));
  }

  int numDrawn = 0;

  for (const auto &line : lines_) {
    if (line.life <= 0)
      continue;

    app_.drawLine(line.p1, line.p2);

    ++numDrawn;
  }

  if (numDrawn == 0)
    removeLater();
}
