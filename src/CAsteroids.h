#ifndef CAsteroids_H
#define CAsteroids_H

#include <CPoint2D.h>
#include <CRGBA.h>
#include <vector>

class CAsteroidsRenderer;
class CAsteroidsObjectMgr;
class CAsteroidsSaucerMgr;
class CAsteroidsBulletMgr;
class CAsteroidsRockMgr;
class CAsteroidsExplosionMgr;
class CAsteroidsShip;
class CAsteroidsScore;
class CConfigFile;

//------

class CAsteroids {
 public:
  using Points = std::vector<CPoint2D>;

 public:
  CAsteroids(CAsteroidsRenderer *renderer);
 ~CAsteroids();

  CAsteroidsObjectMgr    *getObjectMgr   () const { return objectMgr_   ; }
  CAsteroidsSaucerMgr    *getSaucerMgr   () const { return saucerMgr_   ; }
  CAsteroidsRockMgr      *getRockMgr     () const { return rockMgr_     ; }
  CAsteroidsExplosionMgr *getExplosionMgr() const { return explosionMgr_; }

  CAsteroidsShip *getShip() const { return ship_; }

  bool isGameOver() const { return gameOver_; }
  void setGameOver(bool b) { gameOver_ = b; }

  bool isColored() const { return colored_; }
  void setColored(bool b) { colored_ = b; }

  bool isFilled() const { return filled_; }
  void setFilled(bool b) { filled_ = b; }

  bool isShowStatus() const { return showStatus_; }
  void setShowStatus(bool b) { showStatus_ = b; }

  void newGame();

  void togglePause();

  void nextLevel();

  void shipTurnLeft();
  void shipTurnRight();
  void shipTurnStop();

  void shipThrust();
  void shipStopThrust();

  bool shipFire();

  void shipHyperspace();

  void explode(const CPoint2D &pos);

  void update();

  void setColor(const CRGBA &c) const;

  void drawPolygon(const Points &points) const;

  void fillPolygon(const Points &points) const;

  void drawLine(const CPoint2D &p1, const CPoint2D &p2) const;

  void drawLine(double x1, double y1, double x2, double y2) const;

  void drawCenteredString(const CPoint2D &p, double size, const std::string &str) const;

  void drawString(const CPoint2D &p, double size, const std::string &str) const;

  void drawChar(const CPoint2D &p, double size, char c) const;

  void addScore(int score) const;

  void shipDestroyed() const;

  bool getConfigValue(const std::string &section,
                      const std::string &name, std::string &value) const;
  bool getConfigValue(const std::string &section,
                      const std::string &name, int &value) const;
  bool getConfigValue(const std::string &section,
                      const std::string &name, double &value) const;

  virtual void playSound(const std::string &) const { }

 private:
  CAsteroidsRenderer*     renderer_     { nullptr };
  CConfigFile*            config_       { nullptr };

  CAsteroidsObjectMgr*    objectMgr_    { nullptr };
  CAsteroidsSaucerMgr*    saucerMgr_    { nullptr };
  CAsteroidsRockMgr*      rockMgr_      { nullptr };
  CAsteroidsExplosionMgr* explosionMgr_ { nullptr };

  CAsteroidsShip*         ship_         { nullptr };
  CAsteroidsScore*        score_        { nullptr };

  int                     level_        { 0 };
  bool                    gameOver_     { false };
  bool                    paused_       { false };

  bool                    colored_      { false };
  bool                    filled_       { false };
  bool                    showStatus_   { false };
};

#endif
