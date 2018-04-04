package org.colinw.asteroids;

public class AsteroidsBigRock extends AsteroidsRock {
  public AsteroidsBigRock(AsteroidsView view, double x, double y, double a, double dx, double dy, double da) {
   super(view, x, y, a, dx, dy, da, AsteroidsRockType.ASTEROIDS_ROCK_BIG);
  }

  @Override
  public void hit() {
    super.hit();

    view_.getObjectMgr().createMediumRock(x_, y_, a_ + 0.25, -dx_,  dy_, da_);
    view_.getObjectMgr().createMediumRock(x_, y_, a_ - 0.25,  dx_, -dy_, da_);
  }
}
