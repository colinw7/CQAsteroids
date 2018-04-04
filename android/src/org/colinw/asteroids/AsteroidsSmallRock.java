package org.colinw.asteroids;

class AsteroidsSmallRock extends AsteroidsRock {
  public AsteroidsSmallRock(AsteroidsView view, double x, double y, double a, double dx, double dy, double da) {
   super(view, x, y, a, dx, dy, da, AsteroidsRockType.ASTEROIDS_ROCK_SMALL);
  }
}
