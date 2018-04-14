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

  CAsteroidsBigRock    *createBigRock(const CPoint2D &p, double angle,
                                      const CVector2D &v, double da);
  CAsteroidsMediumRock *createMediumRock(const CPoint2D &p, double angle,
                                         const CVector2D &v, double da);
  CAsteroidsSmallRock  *createSmallRock(const CPoint2D &p, double angle,
                                        const CVector2D &v, double da);

  const RockList getRocks   () { return rocks_; }
  std::size_t    getNumRocks() { return rocks_.size(); }

  void removeRock(CAsteroidsRock *rock);

  void removeAll();

  int    getBigRockScore   () const { return bigRockScore_   ; }
  double getBigRockSize    () const { return bigRockSize_    ; }
  int    getMediumRockScore() const { return mediumRockScore_; }
  double getMediumRockSize () const { return mediumRockSize_ ; }
  int    getSmallRockScore () const { return smallRockScore_ ; }
  double getSmallRockSize  () const { return smallRockSize_  ; }

 private:
  void addRock(CAsteroidsRock *rock);

 private:
  const CAsteroids &app_;

  int    bigRockScore_    { 20 };
  double bigRockSize_     { 0.0700 };
  int    mediumRockScore_ { 50 };
  double mediumRockSize_  { 0.0350 };
  int    smallRockScore_  { 100 };
  double smallRockSize_   { 0.0175 };

  RockList rocks_;
};

//------

class CAsteroidsRock : public CAsteroidsObject {
 public:
  CAsteroidsRock(const CAsteroids &app, const CPoint2D &p, double angle,
                 const CVector2D &v, double da, CAsteroidsRockType type);

  virtual ~CAsteroidsRock();

  void destroy() override;

  void hit() override;

 private:
  static int currentRockNum_;

  int rockNum_ { 0 };
};

#endif
