#ifndef CTCL_ASTEROIDS_H
#define CTCL_ASTEROIDS_H

#include "CTclApp/CTclAppCanvas.h"

class CTclAsteroidsCanvas;

class CTclAsteroidsCanvasCmd : public CTclAppCanvasCmd {
 private:
  CTclAsteroidsCanvas *asteroids_canvas_;

 public:
  CTclAsteroidsCanvasCmd(CTclApp *app);
 ~CTclAsteroidsCanvasCmd();

  string getCommandName () const { return "CTclAsteroidsCanvas"; }
  string getCommandClass() const { return "CTclAsteroidsCanvas"; }

  CTclAppCanvas *createInstance(CTclApp *app);

  void initInstance(CTclApp *app);
};

#endif
