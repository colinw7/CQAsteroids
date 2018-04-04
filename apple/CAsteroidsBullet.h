#include "CAsteroidsObject.h"

class CAsteroidsBulletMgr {
 private:
  const CAsteroids              &app_;
  std::list<CAsteroidsBullet *>  bullets_;

 public:
  CAsteroidsBulletMgr(const CAsteroids &app);
 ~CAsteroidsBulletMgr();

  int getNumBullets();

  void addBullet(double x, double y, double a, double size, double speed, double life);

  void removeBullet(CAsteroidsBullet *bullet);

  void move();

  void intersect();

  void draw();
};

class CAsteroidsBullet : public CAsteroidsObject {
 private:
  static CPoint2D draw_coords_[];
  static int      num_draw_coords_;

  static CPoint2D collision_coords_[];
  static int      num_collision_coords_;

  CAsteroidsBulletMgr *bullet_mgr_;

  double size_;
  double speed_;
  double life_;

  double d_;

 public:
  CAsteroidsBullet(const CAsteroids &app, CAsteroidsBulletMgr *bullet_mgr,
                   double x, double y, double a,
                   double size, double speed, double life);
 ~CAsteroidsBullet();

  void move();

  void intersect();
  void intersectRocks();
  void intersectSaucers();

  void destroy();
};
