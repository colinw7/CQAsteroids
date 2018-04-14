#include <CAsteroids.h>
#include <CAsteroidsShip.h>
#include <CAsteroidsRock.h>
#include <CAsteroidsSaucer.h>
#include <CAsteroidsScore.h>
#include <CAsteroidsExplosion.h>
#include <CAsteroidsObject.h>
#include <CAsteroidsShapeMgr.h>
#include <CAsteroidsRenderer.h>

#include <CLFont.h>
#include <COSUser.h>
#include <CConfigFile.h>

CAsteroids::
CAsteroids(CAsteroidsRenderer *renderer) :
 renderer_(renderer)
{
  config_ = new CConfigFile();

  config_->readFile(COSUser::getUserHome() + "/.asteroids");

  rockMgr_      = new CAsteroidsRockMgr     (*this);
  objectMgr_    = new CAsteroidsObjectMgr   (*this);
  saucerMgr_    = new CAsteroidsSaucerMgr   (*this);
  explosionMgr_ = new CAsteroidsExplosionMgr(*this);
  shapeMgr_     = new CAsteroidsShapeMgr    (*this);

  score_ = new CAsteroidsScore(*this);

  ship_ = objectMgr_->createShip();

  saucerMgr_->init();

  nextLevel();

  //setShowStatus(true);

  setColored(true);
  setFilled (true);
}

CAsteroids::
~CAsteroids()
{
  delete score_;

  delete objectMgr_;
  delete saucerMgr_;
  delete rockMgr_;
  delete explosionMgr_;

  delete config_;
}

void
CAsteroids::
newGame()
{
  gameOver_ = false;
  paused_   = false;

  ship_->setVisible(true);

  level_ = 0;

  ship_->init();

  score_->reset();

  rockMgr_->removeAll();

  saucerMgr_->reset();

  explosionMgr_->removeAll();

  nextLevel();
}

void
CAsteroids::
togglePause()
{
  paused_ = ! paused_;
}

void
CAsteroids::
nextLevel()
{
  ++level_;

  objectMgr_->createBigRock(CPoint2D(0.0, 0.0), 0.0, scaledSpeed( 0.05,  0.05), 0.003);
  objectMgr_->createBigRock(CPoint2D(1.0, 0.0), 0.0, scaledSpeed(-0.06,  0.06), 0.004);
  objectMgr_->createBigRock(CPoint2D(0.0, 1.0), 0.0, scaledSpeed( 0.07, -0.07), 0.005);
  objectMgr_->createBigRock(CPoint2D(1.0, 1.0), 0.0, scaledSpeed(-0.08, -0.08), 0.006);
}

void
CAsteroids::
shipTurnLeft()
{
  ship_->turnLeft();
}

void
CAsteroids::
shipTurnRight()
{
  ship_->turnRight();
}

void
CAsteroids::
shipTurnStop()
{
  ship_->turnStop();
}

void
CAsteroids::
shipThrust()
{
  if (! ship_->thrust())
    return;

  playSound("ship.thrust");
}

void
CAsteroids::
shipStopThrust()
{
  ship_->stopThrust();
}

bool
CAsteroids::
shipFire()
{
  if (! ship_->fire())
    return false;

  playSound("ship.fire");

  return true;
}

void
CAsteroids::
shipHyperspace()
{
  if (! ship_->hyperspace())
    return;

  playSound("ship.hyperspace");
}

void
CAsteroids::
explode(const CPoint2D &pos)
{
  explosionMgr_->addExplosion(nullptr, pos);
}

void
CAsteroids::
update()
{
  if (! paused_) {
    objectMgr_->move();

    if (! isGameOver())
      objectMgr_->intersect();

    if (! isGameOver())
      saucerMgr_->update();

    explosionMgr_->update();
  }

  //---

  renderer_->clear(CRGBA(0,0,0));

  setColor(CRGBA(1,1,1));

  //---

  objectMgr_->draw();

  explosionMgr_->draw();

  score_->draw();

  if (! isGameOver()) {
    if (rockMgr_->getNumRocks() == 0)
      nextLevel();
  }

  if      (paused_) {
    CPoint2D p(0.5, 0.66);

    double s = 0.07;

    drawCenteredString(p, s, "PAUSED");
  }
  else if (isGameOver()) {
    CPoint2D p(0.5, 0.46);

    double s = 0.07;

    drawCenteredString(p, s, "GAME OVER");
  }

  if (showStatus_) {
    CPoint2D p(0.5, 0.8);

    double s = 0.01;

    std::string statusStr;

    statusStr += saucerMgr_->statusStr();

    drawCenteredString(p, s, statusStr);
  }
}

void
CAsteroids::
setColor(const CRGBA &c) const
{
  renderer_->setForeground(c);
}

void
CAsteroids::
drawPolygon(const Points &points) const
{
  renderer_->drawPolygon(points);
}

void
CAsteroids::
fillPolygon(const Points &points) const
{
  renderer_->fillPolygon(points);
}

void
CAsteroids::
drawLine(const CPoint2D &p1, const CPoint2D &p2) const
{
  renderer_->drawLine(p1, p2);
}

void
CAsteroids::
drawCenteredString(const CPoint2D &p, double size, const std::string &str) const
{
  drawString(CPoint2D(p.x - size*str.size()/2.0, p.y), size, str);
}

void
CAsteroids::
drawString(const CPoint2D &p, double size, const std::string &str) const
{
  CPoint2D p1 = p;

  for (std::size_t i = 0; i < str.size(); ++i) {
    drawChar(p1, size, str[i]);

    p1.x += size;
  }
}

void
CAsteroids::
drawChar(const CPoint2D &p, double size, char c) const
{
  setColor(CRGBA(1,1,1));

  const CLFontDef &font_def = CLFont::getFontDef(c);

  for (std::size_t i = 0; i < font_def.lines().size(); ++i) {
    const CLFontLine &line = font_def.getLine(i);

    double x1 = line.start().x*size;
    double y1 = line.start().y*size;
    double x2 = line.end  ().x*size;
    double y2 = line.end  ().y*size;

    drawLine(CPoint2D(p.x + x1, p.y + y1), CPoint2D(p.x + x2, p.y + y2));
  }
}

void
CAsteroids::
addScore(int score) const
{
  score_->add(score);
}

void
CAsteroids::
shipDestroyed() const
{
  playSound("ship.hit");

  if (score_->numLives() > 0) {
    score_->die();
  }
  else {
    CAsteroids *th = const_cast<CAsteroids *>(this);

    ship_->setVisible(false);

    th->setGameOver(true);
  }
}

double
CAsteroids::
scaledValue(double v) const
{
  return v/refresh();
}

CVector2D
CAsteroids::
scaledSpeed(double x, double y) const
{
  return CVector2D(x/refresh(), y/refresh());
}

bool
CAsteroids::
getConfigValue(const std::string &section, const std::string &name, std::string &value) const
{
  return config_->getValue(section, name, value);
}

bool
CAsteroids::
getConfigValue(const std::string &section, const std::string &name, int &value) const
{
  return config_->getValue(section, name, value);
}

bool
CAsteroids::
getConfigValue(const std::string &section, const std::string &name, double &value) const
{
  return config_->getValue(section, name, value);
}
