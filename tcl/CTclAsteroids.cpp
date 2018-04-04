#include "std_c++.h"
#include "std_Xt.h"
#include "CTclCanvas/CTclCanvas.h"
#include "CTclAsteroids/CTclAsteroids.h"
#include "CAsteroidsLib/CAsteroidsLib.h"
#include "CTclCanvasPixelRenderer/CTclCanvasPixelRenderer.h"

class CTclAsteroidsRenderer;

class CTclAsteroids {
 private:
  CTclAsteroidsCanvas     *canvas_;
  CTclCanvasPixelRenderer *renderer_;
  CTclAsteroidsRenderer   *arenderer_;
  CAsteroids              *asteroids_;

 public:
  CTclAsteroids(CTclAsteroidsCanvas *canvas);
 ~CTclAsteroids();

  void update();

  void shipTurnLeft();
  void shipTurnRight();
  void shipThrust();
  void shipFire();
};

//--------

class CTclAsteroidsCanvas : public CTclCanvas {
 private:
  CTclAsteroids *asteroids_;

 public:
  CTclAsteroidsCanvas(CTclApp *app);
 ~CTclAsteroidsCanvas();

  bool instanceCommand(int argc, const char **argv);
  bool instanceConfigure(int argc, const char **argv);

  void draw();

  void keyPress();
  void keyRelease();
};

//---------

class CTclAsteroidsRenderer : public CAsteroidsRenderer {
 public:
  CTclAsteroidsRenderer(CPixelRenderer *renderer) :
   renderer_(renderer) {
  }

  void clear(const CRGBA &bg) {
    setForeground(bg);

    renderer_->clear();
  }

  void setForeground(const CRGBA &rgba) {
    renderer_->setForeground(rgba);
  }

  void drawLine(const CPoint2D &p1, const CPoint2D &p2) {
    CIPoint2D pp1(p1.x*renderer_->getWidth(), p1.y*renderer_->getHeight());
    CIPoint2D pp2(p2.x*renderer_->getWidth(), p2.y*renderer_->getHeight());

    renderer_->drawLine(pp1, pp2);
  }

 private:
  CPixelRenderer *renderer_;
};

//--------

CTclAsteroidsCanvasCmd::
CTclAsteroidsCanvasCmd(CTclApp *app) :
 CTclAppCanvasCmd(app), asteroids_canvas_(NULL)
{
  init();
}

CTclAsteroidsCanvasCmd::
~CTclAsteroidsCanvasCmd()
{
  delete asteroids_canvas_;
}

CTclAppCanvas *
CTclAsteroidsCanvasCmd::
createInstance(CTclApp *app)
{
  asteroids_canvas_ = new CTclAsteroidsCanvas(app);

  return (CTclAppCanvas *) asteroids_canvas_->getCanvasWidget();
}

void
CTclAsteroidsCanvasCmd::
initInstance(CTclApp *)
{
}

CTclAsteroidsCanvas::
CTclAsteroidsCanvas(CTclApp *app) :
 CTclCanvas(app)
{
  asteroids_ = new CTclAsteroids(this);
}

CTclAsteroidsCanvas::
~CTclAsteroidsCanvas()
{
  delete asteroids_;
}

bool
CTclAsteroidsCanvas::
instanceCommand(int argc, const char **argv)
{
  if (argc > 0 && strcmp(argv[0], "timeout") == 0) {
    asteroids_->update();

    return true;
  }

  return false;
}

bool
CTclAsteroidsCanvas::
instanceConfigure(int, const char **)
{
  return false;
}

void
CTclAsteroidsCanvas::
draw()
{
}

void
CTclAsteroidsCanvas::
keyPress()
{
  string str = getKeyStr();

  if      (str == "z")
    asteroids_->shipTurnLeft();
  else if (str == "x")
    asteroids_->shipTurnRight();
  else if (str == ".")
    asteroids_->shipThrust();
  else if (str == "/")
    asteroids_->shipFire();
}

void
CTclAsteroidsCanvas::
keyRelease()
{
}

CTclAsteroids::
CTclAsteroids(CTclAsteroidsCanvas *canvas) :
 canvas_(canvas)
{
  renderer_  = new CTclCanvasPixelRenderer(canvas);
  arenderer_ = new CTclAsteroidsRenderer(renderer_);
  asteroids_ = new CAsteroids(arenderer_);
}

CTclAsteroids::
~CTclAsteroids()
{
  delete renderer_;
  delete asteroids_;
}

void
CTclAsteroids::
update()
{
  renderer_->updateSize(100, 100);

  asteroids_->update();
}

void
CTclAsteroids::
shipTurnLeft()
{
  asteroids_->shipTurnLeft();
}

void
CTclAsteroids::
shipTurnRight()
{
  asteroids_->shipTurnRight();
}

void
CTclAsteroids::
shipThrust()
{
  asteroids_->shipThrust();
}

void
CTclAsteroids::
shipFire()
{
  asteroids_->shipFire();
}
