#include "CAsteroidsTypes.h"

class CAsteroidsRenderer {
 public:
  CAsteroidsRenderer() { }

  virtual ~CAsteroidsRenderer() { }

  virtual void clear(const CGFloat *bg) = 0;

  virtual void setForeground(const CGFloat *rgba) = 0;

  virtual void drawLine(double x1, double y1, double x2, double y2) = 0;
};

class CAsteroids {
 private:
  CAsteroidsRenderer  *renderer_;

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

  bool getGameOver() const { return game_over_; }

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
};
