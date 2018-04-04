#ifndef CAsteroidsRock_H
#define CAsteroidsRock_H

#include <CAsteroidsObject.h>
#include <list>

enum class CAsteroidsRockType {
  BIG,
  MEDIUM,
  SMALL
};

class CAsteroids;
class CAsteroidsRock;
class CAsteroidsBigRock;
class CAsteroidsMediumRock;
class CAsteroidsSmallRock;

class CAsteroidsRockMgr {
 public:
  using RockList = std::list<CAsteroidsRock *>;

 public:
  CAsteroidsRockMgr(const CAsteroids &app);

  CAsteroidsBigRock    *createBigRock(const CPoint2D &p, double a,
                                      const CVector2D &v, double da);
  CAsteroidsMediumRock *createMediumRock(const CPoint2D &p, double a,
                                         const CVector2D &v, double da);
  CAsteroidsSmallRock  *createSmallRock(const CPoint2D &p, double a,
                                        const CVector2D &v, double da);

  const RockList getRocks   () { return rocks_; }
  std::size_t    getNumRocks() { return rocks_.size(); }

  void removeRock(CAsteroidsRock *rock);

  void removeAll();

  int    getBigRockScore   () const { return big_rock_score_   ; }
  double getBigRockSize    () const { return big_rock_size_    ; }
  int    getMediumRockScore() const { return medium_rock_score_; }
  double getMediumRockSize () const { return medium_rock_size_ ; }
  int    getSmallRockScore () const { return small_rock_score_ ; }
  double getSmallRockSize  () const { return small_rock_size_  ; }

 private:
  void addRock(CAsteroidsRock *rock);

 private:
  const CAsteroids &app_;

  int    big_rock_score_    { 20 };
  double big_rock_size_     { 0.0700 };
  int    medium_rock_score_ { 50 };
  double medium_rock_size_  { 0.0350 };
  int    small_rock_score_  { 100 };
  double small_rock_size_   { 0.0175 };

  RockList rocks_;
};

//------

class CAsteroidsRock : public CAsteroidsObject {
 public:
  CAsteroidsRock(const CAsteroids &app, const CPoint2D &p, double a,
                 const CVector2D &v, double da, CAsteroidsRockType type);

  virtual ~CAsteroidsRock();

  void destroy() override;

  void hit() override;

 private:
  static int current_rock_num_;

  int rock_num_ { 0 };
};

#endif
