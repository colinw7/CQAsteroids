#ifndef CAsteroidsSaucer_H
#define CAsteroidsSaucer_H

#include <CAsteroidsObject.h>

enum class CAsteroidsSaucerType {
  NONE,
  BIG,
  SMALL
};

class CAsteroids;
class CAsteroidsSaucer;
class CAsteroidsBigSaucer;
class CAsteroidsSmallSaucer;
class CAsteroidsBulletMgr;

class CAsteroidsSaucerMgr {
 public:
  using Saucers = std::list<CAsteroidsSaucer*>;

 public:
  CAsteroidsSaucerMgr(const CAsteroids &app);
 ~CAsteroidsSaucerMgr();

  void init();

  void showBigSaucer  (const CPoint2D &p, const CVector2D &v);
  void showSmallSaucer(const CPoint2D &p, const CVector2D &v);

  double getBigSaucerSize        () const { return bigSaucerSize_        ; }
  int    getBigSaucerScore       () const { return bigSaucerScore_       ; }
  double getBigSaucerBulletSize  () const { return bigSaucerBulletSize_  ; }
  double getBigSaucerBulletSpeed () const { return bigSaucerBulletSpeed_ ; }
  int    getBigSaucerBulletLife  () const { return bigSaucerBulletLife_  ; }
  int    getBigSaucerBulletNum   () const { return bigSaucerBulletNum_   ; }
  int    getBigSaucerFireInterval() const { return bigSaucerFireInterval_; }

  double getSmallSaucerSize        () const { return smallSaucerSize_       ; }
  int    getSmallSaucerScore       () const { return smallSaucerScore_      ; }
  double getSmallSaucerBulletSize  () const { return smallSaucerBulletSize_ ; }
  double getSmallSaucerBulletSpeed () const { return smallSaucerBulletSpeed_; }
  int    getSmallSaucerBulletLife  () const { return smallSaucerBulletLife_ ; }
  int    getSmallSaucerBulletNum   () const { return smallSaucerBulletNum_  ; }
  int    getSmallSaucerFireInterval() const { return smallSaucerFireInterval_; }

  void update();

  void reset();

  void restart(CAsteroidsSaucerType type=CAsteroidsSaucerType::SMALL);

  CAsteroidsSaucer *getVisibleSaucer() const;

  std::string statusStr() const;

 private:
  const CAsteroids& app_;

  int t1_ { 0 };
  int t2_ { 0 };

  CAsteroidsBigSaucer   *bigSaucer_;
  CAsteroidsSmallSaucer *smallSaucer_;

  int    bigSaucerScore_        = 500;
  double bigSaucerSize_         = 0.03;
  double bigSaucerBulletSize_   = 0.01;
  double bigSaucerBulletSpeed_  = 0.3;
  int    bigSaucerBulletLife_   = 100;
  int    bigSaucerBulletNum_    = 4;
  int    bigSaucerDelay_        = 250;
  int    bigSaucerFireInterval_ = 20;

  int    smallSaucerScore_        = 1000;
  double smallSaucerSize_         = 0.015;
  double smallSaucerBulletSize_   = 0.01;
  double smallSaucerBulletSpeed_  = 0.2;
  int    smallSaucerBulletLife_   = 100;
  int    smallSaucerBulletNum_    = 4;
  int    smallSaucerDelay_        = 3;
  int    smallSaucerFireInterval_ = 30;
};

//---

class CAsteroidsSaucer : public CAsteroidsObject {
 public:
  CAsteroidsSaucer(const CAsteroids &app, CAsteroidsSaucerType type);

  virtual ~CAsteroidsSaucer();

  bool isVisible() const { return visible_; }
  void setVisible(bool b) { visible_ = b; }

  void reset();

  void move() override;

  void intersect() override;

  void intersectRocks();

  void draw() override;

  void destroy() override;

  void hit() override;

  void removeLater() override;

 private:
  CAsteroidsBulletMgr* bulletMgr_    { nullptr };
  CAsteroidsSaucerType saucerType_   { CAsteroidsSaucerType::NONE };
  double               bulletSize_   { 0.01 };
  double               bulletSpeed_  { 0.2 };
  int                  bulletLife_   { 100 };
  int                  bulletNum_    { 4 };
  int                  fireInterval_ { 20 };
  int                  t_            { 0 };
  bool                 visible_      { false };
};

#endif
