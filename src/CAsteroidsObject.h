#ifndef CAsteroidsObject_H
#define CAsteroidsObject_H

class CAsteroidsShip;
class CAsteroidsBigSaucer;
class CAsteroidsBigRock;
class CAsteroidsMediumRock;
class CAsteroidsSmallRock;

class CAsteroidsObjectMgr {
 public:
  CAsteroidsObjectMgr(const CAsteroids &app);
 ~CAsteroidsObjectMgr();

  CAsteroidsShip *createShip();

  CAsteroidsBigSaucer *createBigSaucer(double x, double y, double dx, double dy);

  CAsteroidsBigRock    *createBigRock(double x, double y, double a,
                                      double dx, double dy, double da);
  CAsteroidsMediumRock *createMediumRock(double x, double y, double a,
                                         double dx, double dy, double da);
  CAsteroidsSmallRock  *createSmallRock(double x, double y, double a,
                                        double dx, double dy, double da);

  void move();
  void intersect();
  void draw();

 private:
  void addObject(CAsteroidsObject *object);
  void removeObject(CAsteroidsObject *object);

 protected:
  const CAsteroids &app_;

  std::list<CAsteroidsObject *> objects_;
};

//------

class CAsteroidsObject {
 public:
  CAsteroidsObject(const CAsteroids &app, double x, double y, double a,
                   double dx, double dy, double da,
                   double size, int score, bool wrap_on_edge);

  virtual ~CAsteroidsObject();

  void setRemove() { remove_ = true; }

  bool getRemove() const { return remove_; }

  void setDrawCoords(CPoint2D *draw_coords, unsigned int num_draw_coords);
  void setCollisionCoords(CPoint2D *coll_coords, unsigned int num_coll_coords);

  virtual void move();

  virtual void intersect() { }

  bool pointInside(double x, double y);

  virtual void draw();

  virtual void hit();

  virtual void destroy();

 private:
  void updateDrawCoords();
  void updateCollisionCoords();

 protected:
  const CAsteroids&     app_;
  double                x_;
  double                y_;
  double                a_;
  double                dx_;
  double                dy_;
  double                da_;
  double                size_;
  int                   score_;
  bool                  wrap_on_edge_;

  CMatrix2D             matrix_;
  bool                  remove_;

  std::vector<CPoint2D> draw_coords_;
  std::vector<CPoint2D> draw_coords1_;
  int                   num_draw_coords_;

  std::vector<CPoint2D> coll_coords_;
  std::vector<CPoint2D> coll_coords1_;
  int                   num_coll_coords_;

  CBBox2D               bbox_;
};

#endif
