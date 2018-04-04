#include <CGLApp/CGLWindow.h>

class CAsteroids;
class CGLAsteroids;
class CGLAsteroidsRenderer;

#ifdef HAS_SOUND
class CSound;
#endif

class CGLAsteroids : public CGLWindow {
 private:
  CAsteroids           *asteroids_;
  CGLAsteroidsRenderer *renderer_;
#ifdef HAS_SOUND
  CSound               *fire_sound_;
  CSound               *thrust_sound_;
#endif
  bool                  lturn_pressed_;
  bool                  rturn_pressed_;
  bool                  thurst_pressed_;
  bool                  fire_pressed_;

 public:
  CGLAsteroids();
 ~CGLAsteroids();

  void setup();

  void newGame();

  void shipTurnLeft();
  void shipTurnRight();
  void shipThrust();
  void shipFire();
  void shipHyperspace();

  void update();

  bool resizeEvent();
  bool exposeEvent();

  bool keyPressEvent  (const CKeyEvent &event);
  bool keyReleaseEvent(const CKeyEvent &event);

  bool timerEvent();
};
