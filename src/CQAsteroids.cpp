#include <CQAsteroids.h>
#include <CAsteroids.h>

#include <CQUtil.h>
#include <CQCanvas2D.h>
#include <CQSound.h>
#include <CDisplayRange2D.h>

#include <QApplication>
#include <QHBoxLayout>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>

class Canvas : public CQCanvas2D {
 public:
  Canvas(CQAsteroidsApp *asteroids);

  void keyPressEvent(QKeyEvent *e);

  void keyReleaseEvent(QKeyEvent *e);

 private:
  CQAsteroidsApp *asteroids_;
};

//------

#include <CAsteroidsRenderer.h>

class CQAsteroidsRenderer : public CAsteroidsRenderer {
 public:
  CQAsteroidsRenderer(Canvas *canvas);

  void clear(const CRGBA &bg) override;

  void setForeground(const CRGBA &rgba) override;

  void drawLine(const CPoint2D &p1, const CPoint2D &p2) override;

  void drawPolygon(const Points &points) override;

  void fillPolygon(const Points &points) override;

 private:
  Canvas *canvas_;
};

//------

class CQAsteroids : public CAsteroids {
 public:
  CQAsteroids(CQAsteroidsApp *app, CAsteroidsRenderer *renderer) :
   CAsteroids(renderer), app_(app) {
  }

  virtual ~CQAsteroids() { }

  void playSound(const std::string &name) const override {
    app_->playSound(name);
  };

 private:
  CQAsteroidsApp *app_ { nullptr };
};

//------

CQAsteroidsApp::
CQAsteroidsApp() :
 QWidget()
{
  setObjectName("asteroidsApp");

  QVBoxLayout *layout = new QVBoxLayout(this);
  layout->setMargin(0); layout->setSpacing(0);

  canvas_ = new Canvas(this);

  layout->addWidget(canvas_);

  renderer_ = new CQAsteroidsRenderer(canvas_);

  asteroids_ = new CQAsteroids(this, renderer_);

  //CQSoundMgrInst->setActive(false);

  fire_sound_    = CQSoundMgrInst->addSound("sounds/shoot.wav");
  thrust_sound_  = CQSoundMgrInst->addSound("sounds/thrust.wav");
  explode_sound_ = CQSoundMgrInst->addSound("sounds/explosion.wav");
  hyper_sound_   = CQSoundMgrInst->addSound("sounds/hyperspace.wav");

  timer_ = new QTimer(this);

  connect(timer_, SIGNAL(timeout()), this, SLOT(update()));

  timer_->start(50);
}

CQAsteroidsApp::
~CQAsteroidsApp()
{
  delete renderer_;
  delete asteroids_;
}

bool
CQAsteroidsApp::
isFilled() const
{
  return asteroids_->isFilled();
}

void
CQAsteroidsApp::
setFilled(bool b)
{
  asteroids_->setFilled(b);

  update();
}

bool
CQAsteroidsApp::
isColored() const
{
  return asteroids_->isColored();
}

void
CQAsteroidsApp::
setColored(bool b)
{
  asteroids_->setColored(b);

  update();
}

void
CQAsteroidsApp::
update()
{
  asteroids_->update();

  canvas_->setChanged();
}

void
CQAsteroidsApp::
newGame()
{
  asteroids_->newGame();
}

void
CQAsteroidsApp::
togglePause()
{
  asteroids_->togglePause();
}

void
CQAsteroidsApp::
shipTurnLeft()
{
  asteroids_->shipTurnLeft();
}

void
CQAsteroidsApp::
shipTurnRight()
{
  asteroids_->shipTurnRight();
}

void
CQAsteroidsApp::
shipTurnStop()
{
  asteroids_->shipTurnStop();
}

void
CQAsteroidsApp::
shipThrust()
{
  asteroids_->shipThrust();
}

void
CQAsteroidsApp::
shipStopThrust()
{
  asteroids_->shipStopThrust();
}

void
CQAsteroidsApp::
shipFire()
{
  asteroids_->shipFire();
}

void
CQAsteroidsApp::
shipHyperspace()
{
  asteroids_->shipHyperspace();
}

void
CQAsteroidsApp::
playSound(const std::string &name)
{
  if      (name == "ship.hit")
    CQSoundMgrInst->playSound(explode_sound_);
  else if (name == "ship.fire")
    CQSoundMgrInst->playSound(fire_sound_);
  else if (name == "ship.thrust")
    CQSoundMgrInst->playSound(thrust_sound_);
  else if (name == "ship.hyperspace")
    CQSoundMgrInst->playSound(hyper_sound_);
  else if (name == "saucer.fire")
    CQSoundMgrInst->playSound(fire_sound_);
  else if (name == "saucer.hit")
    CQSoundMgrInst->playSound(explode_sound_);
  else if (name == "rock.hit")
    CQSoundMgrInst->playSound(explode_sound_);
}

//-------

Canvas::
Canvas(CQAsteroidsApp *asteroids) :
 asteroids_(asteroids)
{
  setDisplayRange(0, 0, 1, 1);
}

void
Canvas::
keyPressEvent(QKeyEvent *e)
{
  if (e->isAutoRepeat())
    return;

  int key = e->key();

  if      (key == Qt::Key_Z)
    asteroids_->shipTurnLeft();
  else if (key == Qt::Key_X)
    asteroids_->shipTurnRight();
  else if (key == Qt::Key_Period)
    asteroids_->shipThrust();
  else if (key == Qt::Key_Slash)
    asteroids_->shipFire();
  else if (key == Qt::Key_Space)
    asteroids_->shipHyperspace();
  else if (key == Qt::Key_Escape)
    asteroids_->newGame();
  else if (key == Qt::Key_P)
    asteroids_->togglePause();
  else if (key == Qt::Key_E) {
    QPointF pos = mapFromGlobal(QCursor::pos());

    CPoint2D p(pos.x()/width(), (1.0 - pos.y()/height()));

    asteroids_->asteroids()->explode(p);
  }
}

void
Canvas::
keyReleaseEvent(QKeyEvent *e)
{
  if (e->isAutoRepeat())
    return;

  int key = e->key();

  if      (key == Qt::Key_Z)
    asteroids_->shipTurnStop();
  else if (key == Qt::Key_X)
    asteroids_->shipTurnStop();
  else if (key == Qt::Key_Period)
    asteroids_->shipStopThrust();
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
  QPainter *painter = canvas_->getPainter();
  if (! painter) return;

  QColor c = CQUtil::rgbaToColor(rgba);

  QPen   pen  (c);
  QBrush brush(c);

  pen.setWidth(0);

  painter->setPen  (pen);
  painter->setBrush(brush);
}

void
CQAsteroidsRenderer::
drawLine(const CPoint2D &p1, const CPoint2D &p2)
{
  QPainter *painter = canvas_->getPainter();
  if (! painter) return;

  painter->drawLine(CQUtil::toQPoint(p1), CQUtil::toQPoint(p2));
}

void
CQAsteroidsRenderer::
drawPolygon(const Points &points)
{
  QPainter *painter = canvas_->getPainter();
  if (! painter) return;

  assert(points.size());

  QPainterPath path;

  path.moveTo(CQUtil::toQPoint(points[0]));

  for (std::size_t i = 1; i < points.size(); ++i)
    path.lineTo(CQUtil::toQPoint(points[i]));

  path.closeSubpath();

  painter->strokePath(path, painter->pen());
}

void
CQAsteroidsRenderer::
fillPolygon(const Points &points)
{
  QPainter *painter = canvas_->getPainter();
  if (! painter) return;

  assert(points.size());

  QPainterPath path;

  path.moveTo(CQUtil::toQPoint(points[0]));

  for (std::size_t i = 1; i < points.size(); ++i)
    path.lineTo(CQUtil::toQPoint(points[i]));

  path.closeSubpath();

  painter->fillPath(path, painter->brush());
}
