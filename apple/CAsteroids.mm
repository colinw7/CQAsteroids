#include "CAsteroids.h"
#include "CAsteroidsRock.h"
#include "CAsteroidsObject.h"
#include "CAsteroidsSaucer.h"
#include "CAsteroidsBullet.h"
#include "CAsteroidsScore.h"
#include "CAsteroidsShip.h"
#include "CLFont.h"

CAsteroids::
CAsteroids(CAsteroidsRenderer *renderer) :
 renderer_(renderer), game_over_(false)
{
  rock_mgr_   = new CAsteroidsRockMgr  (*this);
  object_mgr_ = new CAsteroidsObjectMgr(*this);
  saucer_mgr_ = new CAsteroidsSaucerMgr(*this);
  bullet_mgr_ = new CAsteroidsBulletMgr(*this);

  score_ = new CAsteroidsScore(*this);

  ship_  = object_mgr_->createShip();

  level_ = 0;

  nextLevel();
}

CAsteroids::
~CAsteroids()
{
  delete score_;

  delete object_mgr_;
  delete bullet_mgr_;
  delete saucer_mgr_;
  delete rock_mgr_;
}

void
CAsteroids::
newGame()
{
  game_over_ = false;

  ship_->setVisible(true);

  level_ = 0;

  ship_    ->init();
  score_   ->reset();
  rock_mgr_->removeAll();

  nextLevel();
}

void
CAsteroids::
nextLevel()
{
  ++level_;

  object_mgr_->createBigRock(0.0, 0.0, 0.0,  0.003,  0.003, 0.003);
  object_mgr_->createBigRock(1.0, 0.0, 0.0, -0.004,  0.004, 0.004);
  object_mgr_->createBigRock(0.0, 1.0, 0.0,  0.005, -0.005, 0.005);
  object_mgr_->createBigRock(1.0, 1.0, 0.0, -0.006, -0.006, 0.006);
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
shipThrust()
{
  ship_->thrust();
}

bool
CAsteroids::
shipFire()
{
  return ship_->fire();
}

void
CAsteroids::
shipHyperspace()
{
  ship_->hyperspace();
}

void
CAsteroids::
update()
{
  static const CGFloat bg[] = {0, 0, 0, 1};
  static const CGFloat fg[] = {1, 1, 1, 1};
  
  object_mgr_->move();

  if (! game_over_)
    object_mgr_->intersect();

  renderer_->clear(bg);

  renderer_->setForeground(fg);

  object_mgr_->draw();

  score_->draw();

  if (! game_over_) {
    if (rock_mgr_->getNumRocks() == 0)
      nextLevel();
  }

  if (game_over_) {
    double x = 0.07;
    double y = 0.46;
    double s = 0.07;

    drawChar(x += 0.08, y, s, 'G');
    drawChar(x += 0.08, y, s, 'A');
    drawChar(x += 0.08, y, s, 'M');
    drawChar(x += 0.08, y, s, 'E');
    drawChar(x += 0.08, y, s, ' ');
    drawChar(x += 0.08, y, s, 'O');
    drawChar(x += 0.08, y, s, 'V');
    drawChar(x += 0.08, y, s, 'E');
    drawChar(x += 0.08, y, s, 'R');
  }
}

void
CAsteroids::
drawLine(double x1, double y1, double x2, double y2) const
{
  renderer_->drawLine(x1, y1, x2, y2);
}

void
CAsteroids::
drawChar(double x, double y, double size, char c) const
{
  const CLFontDef &font_def = CLFont::getFontDef(c);

  for (int i = 0; i < font_def.num_lines; i++) {
    const CLFontLineDef &line = font_def.lines[i];

    double x1 = line.start.x*size;
    double y1 = (1.0 - line.start.y)*size;
    double x2 = line.end  .x*size;
    double y2 = (1.0 - line.end  .y)*size;

    renderer_->drawLine(x + x1, y + y1, x + x2, y + y2);
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
  if (score_->numLives() > 0)
    score_->die();
  else {
    CAsteroids *th = const_cast<CAsteroids *>(this);

    ship_->setVisible(false);

    th->game_over_ = true;
  }
}
