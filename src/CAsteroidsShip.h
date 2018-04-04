#ifndef CAsteroidsShip_H
#define CAsteroidsShip_H

#include <CAsteroidsObject.h>

class CAsteroidsBulletMgr;

class CAsteroidsShip : public CAsteroidsObject {
 public:
  CAsteroidsShip(const CAsteroids &app, const CPoint2D &p=CPoint2D(0.5, 0.5), double a=0.0,
                 const CVector2D &v=CVector2D(0.0, 0.0), double da=0.0);

 ~CAsteroidsShip();

  void init();

  void resetPosition();

  bool isVisible() const { return visible_; }
  void setVisible(bool visible) { visible_ = visible; }

  CRGBA color() const override;

  void move() override;

  void intersect() override;

  void turnLeft ();
  void turnRight();
  void turnStop ();

  bool thrust();

  void stopThrust();

  bool fire();

  bool hyperspace();

  void destroy();

  void draw() override;

  void hit() override;

 private:
  CAsteroidsBulletMgr *bulletMgr_ = { nullptr };

  double rotateSpeed_ { 0.008 };
  double thrust_      { 0.003 };
  double thrustMax_   { 0.01 };
  double bulletSize_  { 0.02 };
  double bulletSpeed_ { 0.01 };
  double bulletLife_  { 0.6 };
  int    bulletNum_   { 4 };

  bool visible_     { true };
  int  exploding_   { 0 };
  int  invunerable_ { 0 };
};

#endif
