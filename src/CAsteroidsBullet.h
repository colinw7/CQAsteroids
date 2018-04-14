#ifndef CAsteroidsBullet_H
#define CAsteroidsBullet_H

#include <CAsteroidsObject.h>

class CAsteroidsBullet;
class CAstreroidsObject;

class CAsteroidsBulletMgr {
 public:
  CAsteroidsBulletMgr(const CAsteroids &app, CAsteroidsObject *parent);
 ~CAsteroidsBulletMgr();

  CAsteroidsObject *parent() const { return parent_; }

  int getNumBullets();

  CAsteroidsBullet *addBullet(const CPoint2D &p, double a, double size, double speed, int life);

  void removeBullet(CAsteroidsBullet *bullet);

  void reset();

  void move();

  void intersect();

  void draw();

 private:
  using Bullets = std::list<CAsteroidsBullet *>;

  const CAsteroids& app_;
  CAsteroidsObject* parent_ { nullptr };
  Bullets           bullets_;
};

//---

class CAsteroidsBullet : public CAsteroidsObject {
 public:
  CAsteroidsBullet(const CAsteroids &app, CAsteroidsBulletMgr *bulletMgr,
                   const CPoint2D &p, double a, double size, double speed, int life);
 ~CAsteroidsBullet();

  CAsteroidsObject *target() const { return target_; }
  void setTarget(CAsteroidsObject *obj) { target_ = obj; }

  void setDirection(double a);

  void move() override;

  void intersect() override;

  void intersectRocks  ();
  void intersectSaucers(CAsteroidsObject *parent);

  void destroy() override;

 private:
  CAsteroidsBulletMgr *bulletMgr_ = nullptr;

  double speed_ { 0.0 };
  int    life_  { 100 };
  int    age_   { 0 };

  CAsteroidsObject *target_ { nullptr };
};

#endif
