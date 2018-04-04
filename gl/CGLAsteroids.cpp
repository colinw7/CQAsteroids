#include <std_c++.h>
#include <CEvent/CEvent.h>
#ifdef HAS_SOUND
#include <CSound/CSound.h>
#endif
#include <CImageLib/CImageLib.h>
#include <CAsteroidsLib/CAsteroidsLib.h>
#include "CGLAsteroids.h"

int
main(int argc, char **argv)
{
  CGLAppInst->init(argc, argv);

  CGLAsteroids *asteroids = new CGLAsteroids;

  asteroids->setup();

  CGLAppInst->timerLoop(40);
}

//---------

class CGLAsteroidsRenderer : public CAsteroidsRenderer {
 public:
  CGLAsteroidsRenderer() { }

  void setSize(int w, int h) {
    w_ = w;
    h_ = h;
  }

  void clear(const CRGBA &bg) {
    glClearColor(bg.getRed(), bg.getGreen(), bg.getBlue(), bg.getAlpha());

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  void setForeground(const CRGBA &fg) {
    fg_ = fg;
  }

  void drawLine(const CPoint2D &p1, const CPoint2D &p2) {
    glColor4f(fg_.getRed(), fg_.getGreen(), fg_.getBlue(), fg_.getAlpha());

    glBegin(GL_LINES);

    glVertex3d(p1.x*w_, p1.y*h_, 0.0);
    glVertex3d(p2.x*w_, p2.y*h_, 0.0);

    glEnd();
  }

 private:
  CRGBA fg_;
  int   w_, h_;
};

//--------

CGLAsteroids::
CGLAsteroids()
 : asteroids_      (NULL)
#ifdef HAS_SOUND
 , fire_sound_     (0)
 , thrust_sound_   (0)
#endif
 ,  lturn_pressed_ (false)
 ,  rturn_pressed_ (false)
 ,  thurst_pressed_(false)
 ,  fire_pressed_  (false)
{
  init(0, 0, 400, 400);
}

CGLAsteroids::
~CGLAsteroids()
{
}

void
CGLAsteroids::
setup()
{
  renderer_ = new CGLAsteroidsRenderer;

  asteroids_ = new CAsteroids(renderer_);

#ifdef HAS_SOUND
  fire_sound_   = new CSound; fire_sound_  ->loadWAV("shot.wav");
  thrust_sound_ = new CSound; thrust_sound_->loadWAV("thrust.wav");
#endif
}

void
CGLAsteroids::
newGame()
{
  asteroids_->newGame();
}

void
CGLAsteroids::
shipTurnLeft()
{
  asteroids_->shipTurnLeft();
}

void
CGLAsteroids::
shipTurnRight()
{
  asteroids_->shipTurnRight();
}

void
CGLAsteroids::
shipThrust()
{
#ifdef HAS_SOUND
  thrust_sound_->stop();
  fire_sound_  ->stop();

  thrust_sound_->play();
#endif

  asteroids_->shipThrust();
}

void
CGLAsteroids::
shipFire()
{
  if (asteroids_->shipFire()) {
#ifdef HAS_SOUND
    thrust_sound_->stop();
    fire_sound_  ->stop();

    fire_sound_->play();
#endif
  }
}

void
CGLAsteroids::
shipHyperspace()
{
  asteroids_->shipHyperspace();
}

void
CGLAsteroids::
update()
{
  redisplay();
}

bool
CGLAsteroids::
resizeEvent()
{
  return true;
}

bool
CGLAsteroids::
exposeEvent()
{
  int w = getWidth ();
  int h = getHeight();

  glMatrixMode(GL_PROJECTION);

  glLoadIdentity();

  int dx = 0;
  int dy = 0;

  if (w <= h)
    dy = (h - w)/2;
  else
    dx = (w - h)/2;

  glOrtho(-dx, w + dx, h + dy, -dy, -1.0, 1.0);

  glMatrixMode(GL_MODELVIEW);

  glLoadIdentity();

  renderer_->setSize(w, h);

  if (lturn_pressed_ ) shipTurnLeft();
  if (rturn_pressed_ ) shipTurnRight();
  if (thurst_pressed_) shipThrust();
  if (fire_pressed_  ) shipFire();

  asteroids_->update();

  return true;
}

bool
CGLAsteroids::
keyPressEvent(const CKeyEvent &kevent)
{
  CKeyType type = kevent.getType();

  if      (type == CKEY_TYPE_z)
    lturn_pressed_ = true;
  else if (type == CKEY_TYPE_x)
    rturn_pressed_ = true;
  else if (type == CKEY_TYPE_Period)
    thurst_pressed_ = true;
  else if (type == CKEY_TYPE_Slash)
    fire_pressed_ = true;

  if      (type == CKEY_TYPE_Space)
    shipHyperspace();
  else if (type == CKEY_TYPE_Escape)
    newGame();

  return true;
}

bool
CGLAsteroids::
keyReleaseEvent(const CKeyEvent &kevent)
{
  CKeyType type = kevent.getType();

  if      (type == CKEY_TYPE_z)
    lturn_pressed_ = false;
  else if (type == CKEY_TYPE_x)
    rturn_pressed_ = false;
  else if (type == CKEY_TYPE_Period)
    thurst_pressed_ = false;
  else if (type == CKEY_TYPE_Slash)
    fire_pressed_ = false;

  return true;
}

bool
CGLAsteroids::
timerEvent()
{
  update();

  return true;
}
