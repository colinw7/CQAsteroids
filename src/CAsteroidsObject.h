#ifndef CAsteroidsObject_H
#define CAsteroidsObject_H

#include <CBBox2D.h>
#include <CMatrix2D.h>
#include <CVector2D.h>
#include <CPoint2D.h>
#include <CRGBA.h>
#include <list>
#include <vector>

class CAsteroids;
class CAsteroidsObject;
class CAsteroidsShip;
class CAsteroidsBigSaucer;
class CAsteroidsSmallSaucer;
class CAsteroidsBigRock;
class CAsteroidsMediumRock;
class CAsteroidsSmallRock;

class CAsteroidsObjectMgr {
 public:
  CAsteroidsObjectMgr(const CAsteroids &app);
 ~CAsteroidsObjectMgr();

  CAsteroidsShip *createShip();

  CAsteroidsBigSaucer   *createBigSaucer  ();
  CAsteroidsSmallSaucer *createSmallSaucer();

  CAsteroidsBigRock    *createBigRock(const CPoint2D &p, double a,
                                      const CVector2D &v, double da);
  CAsteroidsMediumRock *createMediumRock(const CPoint2D &p, double a,
                                         const CVector2D &v, double da);
  CAsteroidsSmallRock  *createSmallRock(const CPoint2D &p, double a,
                                        const CVector2D &v, double da);

  void move();

  void intersect();

  void draw();

 private:
  void addObject   (CAsteroidsObject *object);
  void removeObject(CAsteroidsObject *object);

 protected:
  using Objects = std::list<CAsteroidsObject *>;

  const CAsteroids& app_;
  Objects           objects_;
};

//------

class CAsteroidsObject {
 public:
  enum class Type {
    NONE,
    SHIP,
    ROCK,
    BULLET,
    SAUCER,
    EXPLOSION
  };

  using Points = std::vector<CPoint2D>;

 public:
  CAsteroidsObject(const CAsteroids &app, Type type, const CPoint2D &pos, double a,
                   const CVector2D &v, double da, double size, int score,
                   bool wrapOnEdge);

  virtual ~CAsteroidsObject();

  const Type &type() const { return type_; }

  const CPoint2D &pos() const { return p_; }
  void setPos(const CPoint2D &p) { p_ = p; }

  const CVector2D &velocity() const { return v_; }
  void setVelocity(const CVector2D &v) { v_ = v; }

  bool isRemove() const { return remove_; }
  void setRemove() { remove_ = true; }

  void setDrawCoords(const Points &draw_coords);

  void setCollisionCoords(const Points &coll_coords);

  virtual CRGBA color() const { return color_; }

  virtual void move();

  virtual void intersect() { }

  bool pointInside(const CPoint2D &p) const;

  bool intersectObj(const CAsteroidsObject *obj) const;

  virtual void draw();

  virtual void hit();

  virtual void removeLater();

  virtual void destroy();

 private:
  void updateDrawCoords();
  void updateCollisionCoords();

 protected:
  const CAsteroids& app_;
  Type              type_;

  CPoint2D          p_ { 0.0, 0.0 }; // current position
  CVector2D         v_ { 0.0, 0.0 }; // velocity
  CVector2D         a_ { 0.0, 0.0 }; // acceleration

  double            angle_ { 0 }; // current angle
  double            da_    { 0 }; // delta angle

  double            size_  { 0 };
  int               score_ { 0 };

  bool              wrapOnEdge_ { false };

  CMatrix2D         matrix_;
  bool              remove_ { false };

  Points            draw_coords_;
  Points            draw_coords1_;

  Points            coll_coords_;
  Points            coll_coords1_;

  CBBox2D           bbox_;

  CRGBA             color_ { 1, 1, 1 };
};

#endif
