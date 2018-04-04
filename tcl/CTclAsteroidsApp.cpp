#include "std_c++.h"
#include "CTclApp/CTclApp.h"
#include "CTclAsteroids.h"

#include "CTclAsteroids.k"

class CTclAsteroidsApp : public CTclApp {
 private:
  CTclAsteroidsCanvasCmd *cmd_;

 public:
  CTclAsteroidsApp(int argc, char **argv);
 ~CTclAsteroidsApp();

 protected:
  void addCommands();

  string getTclStr() {
    return CTclAsteroids_TK;
  }
};

int
main(int argc, char **argv)
{
  CTclAsteroidsApp app(argc, argv);
}

CTclAsteroidsApp::
CTclAsteroidsApp(int argc, char **argv) :
 CTclApp(argc, argv), cmd_(NULL)
{
  init();
}

CTclAsteroidsApp::
~CTclAsteroidsApp()
{
  delete cmd_;
}

void
CTclAsteroidsApp::
addCommands()
{
  cmd_ = new CTclAsteroidsCanvasCmd(this);
}
