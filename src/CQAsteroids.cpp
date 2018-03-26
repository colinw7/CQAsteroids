#include <CQAsteroids.h>

#include <CQUtil.h>
#include <CQCanvas2D.h>
#include <CQSound.h>
#include <CAsteroidsLib.h>
#include <CDisplayRange2D.h>

#include <QApplication>
#include <QHBoxLayout>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>

class Canvas : public CQCanvas2D {
 public:
  Canvas(CQAsteroids *asteroids);

  void keyPressEvent(QKeyEvent *e);

 private:
  CQAsteroids *asteroids_;
};

//------

class CQAsteroidsRenderer : public CAsteroidsRenderer {
 public:
  CQAsteroidsRenderer(Canvas *canvas);

  void clear(const CRGBA &bg);

  void setForeground(const CRGBA &rgba);

  void drawLine(const CPoint2D &p1, const CPoint2D &p2);

 private:
  Canvas *canvas_;
};

//------

CQAsteroids::
CQAsteroids() :
 QWidget()
{
  QVBoxLayout *layout = new QVBoxLayout(this);
  layout->setMargin(0); layout->setSpacing(0);

  canvas_ = new Canvas(this);

  layout->addWidget(canvas_);

  renderer_ = new CQAsteroidsRenderer(canvas_);

  asteroids_ = new CAsteroids(renderer_);

  //CQSoundMgrInst->setActive(false);

  fire_sound_   = CQSoundMgrInst->addSound("sounds/shoot.wav");
  thrust_sound_ = CQSoundMgrInst->addSound("sounds/thrust.wav");

  timer_ = new QTimer(this);

  connect(timer_, SIGNAL(timeout()), this, SLOT(update()));

  timer_->start(50);
}

CQAsteroids::
~CQAsteroids()
{
  delete renderer_;
  delete asteroids_;
}

void
CQAsteroids::
update()
{
  asteroids_->update();

  canvas_->setChanged();
}

void
CQAsteroids::
newGame()
{
  asteroids_->newGame();
}

void
CQAsteroids::
shipTurnLeft()
{
  asteroids_->shipTurnLeft();
}

void
CQAsteroids::
shipTurnRight()
{
  asteroids_->shipTurnRight();
}

void
CQAsteroids::
shipThrust()
{
  CQSoundMgrInst->playSound(thrust_sound_);

  asteroids_->shipThrust();
}

void
CQAsteroids::
shipFire()
{
  if (asteroids_->shipFire())
    CQSoundMgrInst->playSound(fire_sound_);
}

void
CQAsteroids::
shipHyperspace()
{
  asteroids_->shipHyperspace();
}

//-------

Canvas::
Canvas(CQAsteroids *asteroids) :
 CQCanvas2D(NULL), asteroids_(asteroids)
{
  setDisplayRange(0, 1, 1, 0);
}

void
Canvas::
keyPressEvent(QKeyEvent *e)
{
  int key = e->key();

  if      (key == Qt::Key_Z)
    asteroids_->shipTurnRight();
  else if (key == Qt::Key_X)
    asteroids_->shipTurnLeft();
  else if (key == Qt::Key_Period)
    asteroids_->shipThrust();
  else if (key == Qt::Key_Slash)
    asteroids_->shipFire();
  else if (key == Qt::Key_Space)
    asteroids_->shipHyperspace();
  else if (key == Qt::Key_Escape)
    asteroids_->newGame();
}

//-------

CQAsteroidsRenderer::
CQAsteroidsRenderer(Canvas *canvas) :
 CAsteroidsRenderer(), canvas_(canvas)
{
}

void
CQAsteroidsRenderer::
clear(const CRGBA &bg)
{
  canvas_->setBackground(CQUtil::rgbaToColor(bg));

  canvas_->clear();

  QPainter *painter = canvas_->getPainter();

  if (painter)
    painter->setRenderHint(QPainter::Antialiasing, true);
}

void
CQAsteroidsRenderer::
setForeground(const CRGBA &rgba)
{
  QPen pen(CQUtil::rgbaToColor(rgba));

  QPainter *painter = canvas_->getPainter();
  if (! painter) return;

  pen.setWidth(0);

  painter->setPen(pen);
}

void
CQAsteroidsRenderer::
drawLine(const CPoint2D &p1, const CPoint2D &p2)
{
  QPainter *painter = canvas_->getPainter();
  if (! painter) return;

  painter->drawLine(CQUtil::toQPoint(p1), CQUtil::toQPoint(p2));
}
