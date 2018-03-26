#include <CRGBA.h>

class CConfigFile;

class CAsteroidsRenderer {
 public:
  CAsteroidsRenderer() { }

  virtual ~CAsteroidsRenderer() { }

  virtual void clear(const CRGBA &bg) = 0;

  virtual void setForeground(const CRGBA &rgba) = 0;

  virtual void drawLine(const CPoint2D &p1, const CPoint2D &p2) = 0;
};

class CAsteroids {
 private:
  CAsteroidsRenderer  *renderer_;
  CConfigFile         *config_;

  CAsteroidsObjectMgr *object_mgr_;
  CAsteroidsSaucerMgr *saucer_mgr_;
  CAsteroidsBulletMgr *bullet_mgr_;
  CAsteroidsRockMgr   *rock_mgr_;

  CAsteroidsShip      *ship_;
  CAsteroidsScore     *score_;

  int                  level_;
  bool                 game_over_;

 public:
  CAsteroids(CAsteroidsRenderer *renderer);
 ~CAsteroids();

  CAsteroidsObjectMgr *getObjectMgr() const { return object_mgr_; }
  CAsteroidsSaucerMgr *getSaucerMgr() const { return saucer_mgr_; }
  CAsteroidsBulletMgr *getBulletMgr() const { return bullet_mgr_; }
  CAsteroidsRockMgr   *getRockMgr  () const { return rock_mgr_  ; }

  CAsteroidsShip *getShip() const { return ship_; }

  void newGame();

  void nextLevel();

  void shipTurnLeft();
  void shipTurnRight();
  void shipThrust();
  bool shipFire();
  void shipHyperspace();

  void update();

  void drawLine(double x1, double y1, double x2, double y2) const;
  void drawChar(double x, double y, double size, char c) const;

  void addScore(int score) const;

  void shipDestroyed() const;

  bool getConfigValue(const std::string &section,
                      const std::string &name, std::string &value) const;
  bool getConfigValue(const std::string &section,
                      const std::string &name, int &value) const;
  bool getConfigValue(const std::string &section,
                      const std::string &name, double &value) const;
};
