package org.colinw.asteroids;

public class AsteroidsScore {
  private AsteroidsView view_;
  private int           score_;
  private double        size_;
  private int           lives_;

  public AsteroidsScore(AsteroidsView view) {
    view_ = view;

    reset();
  }

  public void reset() {
    score_ = 0;
    size_  = 0.03;
    lives_ = 3;
  }

  public void add(int score) {
    score_ += score;
  }

  public void die() {
    if (lives_ > 0)
      --lives_;
  }

  public int numLives() { return lives_; }

  public void draw() {
    String str = new String();
    
    str += score_;

    while (str.length() < 5)
      str = "0" + str;

    double x = 0.0;
    double y = 0.01;

    int len = str.length();

    for (int i = 0; i < len; i++) {
      view_.drawChar(x, y, size_, str.charAt(i));

      x += size_;
    }

    x = 0.99 - size_;
    y = 0.01;

    for (int i = 0; i < lives_; i++) {
      view_.drawChar(x, y, size_, 'A');

      x -= size_;
    }
  }
}
