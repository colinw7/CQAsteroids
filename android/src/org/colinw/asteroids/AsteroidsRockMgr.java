package org.colinw.asteroids;

import java.util.LinkedList;
import java.util.ListIterator;

public class AsteroidsRockMgr {
  private AsteroidsView view_;

  private int    big_rock_score_;
  private double big_rock_size_;
  private int    medium_rock_score_;
  private double medium_rock_size_;
  private int    small_rock_score_;
  private double small_rock_size_;

  private LinkedList<AsteroidsRock> rocks_;

  public AsteroidsRockMgr(AsteroidsView view) {
    view_ = view;

    rocks_ = new LinkedList<AsteroidsRock>();
    
    big_rock_score_ = 20;
    big_rock_size_  = 0.07;

    medium_rock_score_ = 50;
    medium_rock_size_  = 0.035;

    small_rock_score_ = 100;
    small_rock_size_  = 0.0175;
  }

  public AsteroidsBigRock createBigRock(double x, double y, double a, double dx, double dy, double da) {
    AsteroidsBigRock rock = new AsteroidsBigRock(view_, x, y, a, dx,  dy, da);

    rocks_.add(rock);

    return rock;
  }

  public AsteroidsMediumRock createMediumRock(double x, double y, double a, double dx, double dy, double da) {
    AsteroidsMediumRock rock = new AsteroidsMediumRock(view_, x, y, a, dx,  dy, da);

    rocks_.add(rock);

    return rock;
  }

  public AsteroidsSmallRock createSmallRock(double x, double y, double a, double dx, double dy, double da) {
    AsteroidsSmallRock rock = new AsteroidsSmallRock(view_, x, y, a, dx,  dy, da);

    rocks_.add(rock);

    return rock;
  }

  public LinkedList<AsteroidsRock> getRocks   () { return rocks_; }
  public int                       getNumRocks() { return rocks_.size(); }

  public void removeAll() {
    rocks_.clear();
  }

  public int    getBigRockScore   () { return big_rock_score_   ; }
  public double getBigRockSize    () { return big_rock_size_    ; }
  public int    getMediumRockScore() { return medium_rock_score_; }
  public double getMediumRockSize () { return medium_rock_size_ ; }
  public int    getSmallRockScore () { return small_rock_score_ ; }
  public double getSmallRockSize  () { return small_rock_size_  ; }

  public void addRock(AsteroidsRock rock) {
    rocks_.add(rock);
  }
}
