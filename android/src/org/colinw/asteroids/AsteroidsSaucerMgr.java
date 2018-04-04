package org.colinw.asteroids;

import java.util.LinkedList;

public class AsteroidsSaucerMgr {
  private AsteroidsView               view_;
  private int                         t_;
  private LinkedList<AsteroidsSaucer> saucers_;

  private int    big_saucer_score_;
  private double big_saucer_size_;
  private double big_saucer_bulletSize_;
  private double big_saucer_bulletSpeed_;
  private double big_saucer_bulletLife_;
  private int    big_saucer_bulletNum_;
  private int    big_saucer_delay_;
  private int    big_saucer_fireInterval_;

  private int    small_saucer_score_;
  private double small_saucer_size_;
  private double small_saucer_bulletSize_;
  private double small_saucer_bulletSpeed_;
  private double small_saucer_bulletLife_;
  private int    small_saucer_bulletNum_;
  private int    small_saucer_fireInterval_;

  public AsteroidsSaucerMgr(AsteroidsView view) {
    view_ = view;

    big_saucer_score_        = 500;
    big_saucer_size_         = 0.03;
    big_saucer_bulletSize_   = 0.01;
    big_saucer_bulletSpeed_  = 0.01;
    big_saucer_bulletLife_   = 0.6;
    big_saucer_bulletNum_    = 4;
    big_saucer_delay_        = 100;
    big_saucer_fireInterval_ = 10;

    small_saucer_score_        = 1000;
    small_saucer_size_         = 0.015;
    small_saucer_bulletSize_   = 0.01;
    small_saucer_bulletSpeed_  = 0.01;
    small_saucer_bulletLife_   = 0.6;
    small_saucer_bulletNum_    = 4;
    small_saucer_fireInterval_ = 5;

    t_ = 0;
    
    saucers_ = new LinkedList<AsteroidsSaucer>();
  }

  public void update() {
    t_ += 1;

    if (t_ >= big_saucer_delay_) {
      if (saucers_.isEmpty())
        view_.getObjectMgr().createBigSaucer(0.0, 0.5, 0.004, 0.0);
    }

    if (saucers_.isEmpty())
      restart();
  }

  public AsteroidsBigSaucer createBigSaucer(double x, double y, double dx, double dy) {
    AsteroidsBigSaucer saucer = new AsteroidsBigSaucer(view_, x, y, dx, dy);

    saucers_.add(saucer);

    return saucer;
  }

  public LinkedList<AsteroidsSaucer> getSaucers() { return saucers_; }

  public double getBigSaucerSize        () { return big_saucer_size_        ; }
  public int    getBigSaucerScore       () { return big_saucer_score_       ; }
  public double getBigSaucerBulletSize  () { return big_saucer_bulletSize_  ; }
  public double getBigSaucerBulletSpeed () { return big_saucer_bulletSpeed_ ; }
  public double getBigSaucerBulletLife  () { return big_saucer_bulletLife_  ; }
  public int    getBigSaucerBulletNum   () { return big_saucer_bulletNum_   ; }
  public int    getBigSaucerFireInterval() { return big_saucer_fireInterval_; }

  public double getSmallSaucerSize        () { return small_saucer_size_       ; }
  public int    getSmallSaucerScore       () { return small_saucer_score_      ; }
  public double getSmallSaucerBulletSize  () { return small_saucer_bulletSize_ ; }
  public double getSmallSaucerBulletSpeed () { return small_saucer_bulletSpeed_; }
  public double getSmallSaucerBulletLife  () { return small_saucer_bulletLife_ ; }
  public int    getSmallSaucerBulletNum   () { return small_saucer_bulletNum_  ; }
  public int    getSmallSaucerFireInterval() { return small_saucer_fireInterval_; }

  public void addSaucer(AsteroidsSaucer saucer) {
    saucers_.add(saucer);
  }

  public void restart() {
    t_ = 0;
  }
}
