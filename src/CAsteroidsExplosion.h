#ifndef CAsteroidsExplosion_H
#define CAsteroidsExplosion_H

#include <CAsteroidsObject.h>

class CAsteroidsExplosion;

class CAsteroidsExplosionMgr {
 public:
  CAsteroidsExplosionMgr(CAsteroids &app);
 ~CAsteroidsExplosionMgr();

  void addExplosion(CAsteroidsObject *parent, const CPoint2D &p);

  void removeAll();

  void update();

  void draw();

 private:
  using Explosions = std::vector<CAsteroidsExplosion *>;

  CAsteroids& app_;
  Explosions  explosions_;
};

//------

class CAsteroidsExplosion : public CAsteroidsObject {
 public:
  CAsteroidsExplosion(const CAsteroids &app, CAsteroidsObject *parent,
                      const CPoint2D &p=CPoint2D(0.5, 0.5));

 ~CAsteroidsExplosion();

  void init();

  void move() override;

  void draw() override;

 private:
  struct Line {
    CPoint2D  p1;
    CPoint2D  p2;
    CVector2D v;
    double    da;
    int       life;

    Line(const CPoint2D &p1, const CPoint2D &p2) :
     p1(p1), p2(p2) {
    }
  };

  using Lines = std::vector<Line>;

  CAsteroidsObject *parent_ = { nullptr };
  Lines             lines_;
  int               life_ { 50 };
};

#endif
