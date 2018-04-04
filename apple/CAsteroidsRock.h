#ifndef CASTEROIDS_ROCK_H
#define CASTEROIDS_ROCK_H

#include "CAsteroidsObject.h"

enum CAsteroidsRockType {
  CASTEROIDS_ROCK_BIG,
  CASTEROIDS_ROCK_MEDIUM,
  CASTEROIDS_ROCK_SMALL
};

class CAsteroidsRock;
class CAsteroidsBigRock;
class CAsteroidsMediumRock;
class CAsteroidsSmallRock;

class CAsteroidsRockMgr {
 private:
  typedef std::list<CAsteroidsRock *> RockList;

  const CAsteroids &app_;

  uint   big_rock_score_;
  double big_rock_size_;
  uint   medium_rock_score_;
  double medium_rock_size_;
  uint   small_rock_score_;
  double small_rock_size_;

  RockList rocks_;

 public:
  CAsteroidsRockMgr(const CAsteroids &app);

  CAsteroidsBigRock    *createBigRock(double x, double y, double a,
                                      double dx, double dy, double da);
  CAsteroidsMediumRock *createMediumRock(double x, double y, double a,
                                         double dx, double dy, double da);
  CAsteroidsSmallRock  *createSmallRock(double x, double y, double a,
                                        double dx, double dy, double da);

  const RockList getRocks   () { return rocks_; }
  uint           getNumRocks() { return rocks_.size(); }

  void removeRock(CAsteroidsRock *rock);

  void removeAll();

  uint   getBigRockScore   () const { return big_rock_score_   ; }
  double getBigRockSize    () const { return big_rock_size_    ; }
  uint   getMediumRockScore() const { return medium_rock_score_; }
  double getMediumRockSize () const { return medium_rock_size_ ; }
  uint   getSmallRockScore () const { return small_rock_score_ ; }
  double getSmallRockSize  () const { return small_rock_size_  ; }

 private:
  void addRock(CAsteroidsRock *rock);
};

class CAsteroidsRock : public CAsteroidsObject {
 private:
  static CPoint2D draw_coords1_[];
  static uint     num_draw_coords1_;
  static CPoint2D draw_coords2_[];
  static uint     num_draw_coords2_;
  static CPoint2D draw_coords3_[];
  static uint     num_draw_coords3_;

  static CPoint2D collision_coords_[];
  static uint     num_collision_coords_;

  static uint current_rock_num_;

  uint rock_num_;

 public:
  CAsteroidsRock(const CAsteroids &app, double x, double y, double a,
                 double dx, double dy, double da, CAsteroidsRockType type);

  virtual ~CAsteroidsRock();

  void destroy();
};

#endif
