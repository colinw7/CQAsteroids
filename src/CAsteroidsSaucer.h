enum CAsteroidsSaucerType {
  CASTEROIDS_BIG_SAUCER,
  CASTEROIDS_SMALL_SAUCER
};

class CAsteroidsBigSaucer;

class CAsteroidsSaucerMgr {
 public:
  CAsteroidsSaucerMgr(const CAsteroids &app);

  CAsteroidsBigSaucer *createBigSaucer(double x, double y, double dx, double dy);

  std::list<CAsteroidsSaucer *> getSaucers() const { return saucers_; }

  double getBigSaucerSize        () const {
    return big_saucer_size_        ;
  }
  int    getBigSaucerScore       () const {
    return big_saucer_score_       ;
  }
  double getBigSaucerBulletSize  () const {
    return big_saucer_bulletSize_  ;
  }
  double getBigSaucerBulletSpeed () const {
    return big_saucer_bulletSpeed_ ;
  }
  double getBigSaucerBulletLife  () const {
    return big_saucer_bulletLife_  ;
  }
  int    getBigSaucerBulletNum   () const {
    return big_saucer_bulletNum_   ;
  }
  int    getBigSaucerFireInterval() const {
    return big_saucer_fireInterval_;
  }

  double getSmallSaucerSize        () const {
    return small_saucer_size_       ;
  }
  int    getSmallSaucerScore       () const {
    return small_saucer_score_      ;
  }
  double getSmallSaucerBulletSize  () const {
    return small_saucer_bulletSize_ ;
  }
  double getSmallSaucerBulletSpeed () const {
    return small_saucer_bulletSpeed_;
  }
  double getSmallSaucerBulletLife  () const {
    return small_saucer_bulletLife_ ;
  }
  int    getSmallSaucerBulletNum   () const {
    return small_saucer_bulletNum_  ;
  }
  int    getSmallSaucerFireInterval() const {
    return small_saucer_fireInterval_;
  }

  void update();

  void addSaucer   (CAsteroidsSaucer *saucer);
  void removeSaucer(CAsteroidsSaucer *saucer);

  void restart();

 private:
  const CAsteroids&            app_;
  int                          t_;
  std::list<CAsteroidsSaucer*> saucers_;

  int    big_saucer_score_;
  double big_saucer_size_;
  double big_saucer_bulletSize_;
  double big_saucer_bulletSpeed_;
  double big_saucer_bulletLife_;
  int    big_saucer_bulletNum_;
  int    big_saucer_delay_;
  int    big_saucer_fireInterval_;

  int    small_saucer_score_;
  double small_saucer_size_;
  double small_saucer_bulletSize_;
  double small_saucer_bulletSpeed_;
  double small_saucer_bulletLife_;
  int    small_saucer_bulletNum_;
  int    small_saucer_delay_;
  int    small_saucer_fireInterval_;
};

//---

class CAsteroidsSaucer : public CAsteroidsObject {
 public:
  CAsteroidsSaucer(const CAsteroids &app, double x, double y,
                   double dx, double dy, CAsteroidsSaucerType type);

  virtual ~CAsteroidsSaucer();

  void move();

  void intersect();
  void intersectRocks();

  void draw();

  void destroy();

 private:
  static CPoint2D draw_coords1_[];
  static int      num_draw_coords1_;
  static CPoint2D draw_coords2_[];
  static int      num_draw_coords2_;

  static CPoint2D collision_coords_[];
  static int      num_collision_coords_;

  CAsteroidsBulletMgr  bullet_mgr_;
  CAsteroidsSaucerType type_;
  double               bulletSize_;
  double               bulletSpeed_;
  double               bulletLife_;
  int                  bulletNum_;
  int                  fireInterval_;
  int                  t_;
};
