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

  CAsteroidsObject *parent() const { return parent_; }

  void init();

  void move() override;

  void draw() override;

 private:
  struct Line {
    CPoint2D  p1;
    CPoint2D  p2;
    CVector2D v;
    double    da   { 0.0 };
    int       life { 0 };

    Line(const CPoint2D &p1, const CPoint2D &p2) :
     p1(p1), p2(p2) {
    }
  };

  using Lines = std::vector<Line>;

  static const int initLife_ { 100 };

  CAsteroidsObject *parent_ = { nullptr };
  Lines             lines_;
  int               life_ { initLife_ };
};

#endif
