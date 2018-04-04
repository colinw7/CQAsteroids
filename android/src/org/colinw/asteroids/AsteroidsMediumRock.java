package org.colinw.asteroids;

public class AsteroidsMediumRock extends AsteroidsRock {
  public AsteroidsMediumRock(AsteroidsView view, double x, double y, double a, double dx, double dy, double da) {
    super(view, x, y, a, dx, dy, da, AsteroidsRockType.ASTEROIDS_ROCK_MEDIUM);
  }

  @Override
  public void hit() {
    super.hit();

    view_.getObjectMgr().createSmallRock(x_, y_, a_ + 0.25, -dx_,  dy_, da_);
    view_.getObjectMgr().createSmallRock(x_, y_, a_ - 0.25,  dx_, -dy_, da_);
  }
}
