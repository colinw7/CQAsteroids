package org.colinw.asteroids;

public class AsteroidsRock extends AsteroidsObject {
  private static int num_draw_coords1_ = 11;
  private static int num_draw_coords2_ = 11;
  private static int num_draw_coords3_ = 11;

  private static Point draw_coords1_[] = {
    new Point(-0.250, -0.500),
    new Point( 0.125, -0.500),
    new Point( 0.250, -0.250),
    new Point( 0.500, -0.250),
    new Point( 0.500,  0.125),
    new Point( 0.250,  0.125),
    new Point( 0.375,  0.500),
    new Point(-0.250,  0.500),
    new Point(-0.500,  0.125),
    new Point(-0.250,  0.000),
    new Point(-0.500, -0.250),
  };

  private static Point draw_coords2_[] = {
    new Point(-0.125, -0.500),
    new Point( 0.375, -0.500),
    new Point( 0.500, -0.250),
    new Point( 0.500,  0.125),
    new Point( 0.250,  0.500),
    new Point(-0.375,  0.500),
    new Point(-0.250,  0.250),
    new Point(-0.500,  0.250),
    new Point(-0.500, -0.125),
    new Point(-0.125, -0.125),
    new Point(-0.375, -0.250),
  };

  private static Point draw_coords3_[] = {
    new Point(-0.250, -0.500),
    new Point( 0.125, -0.500),
    new Point( 0.250, -0.250),
    new Point( 0.500, -0.375),
    new Point( 0.500,  0.000),
    new Point( 0.250,  0.125),
    new Point( 0.125,  0.500),
    new Point(-0.125,  0.500),
    new Point(-0.250,  0.125),
    new Point(-0.500,  0.125),
    new Point(-0.500, -0.250),
    new Point(-0.250, -0.250),
  };

  private Point collision_coords_[] = {
    new Point( 0.5, -0.5),
    new Point( 0.5,  0.5),
    new Point(-0.5,  0.5),
    new Point(-0.5, -0.5),
  };

  private static int num_collision_coords_ = 4;

  private static int current_rock_num_ = 0;

  private int rock_num_;

  public AsteroidsRock(AsteroidsView view, double x, double y, double a, double dx, double dy, double da, AsteroidsRockType type) {
    super(view, x, y, a, dx, dy, da, 0.1, 0, true);

    if      (type == AsteroidsRockType.ASTEROIDS_ROCK_BIG) {
      size_  = view_.getRockMgr().getBigRockSize();
      score_ = view_.getRockMgr().getBigRockScore();
    }
    else if (type == AsteroidsRockType.ASTEROIDS_ROCK_MEDIUM) {
      size_  = view_.getRockMgr().getMediumRockSize();
      score_ = view_.getRockMgr().getMediumRockScore();
    }
    else if (type == AsteroidsRockType.ASTEROIDS_ROCK_SMALL) {
      size_  = view_.getRockMgr().getSmallRockSize();
      score_ = view_.getRockMgr().getSmallRockScore();
    }

    ++current_rock_num_;

    current_rock_num_ %= 3;

    rock_num_ = current_rock_num_;

    switch (rock_num_) {
      case 0:
        setDrawCoords(draw_coords1_, num_draw_coords1_);
        break;
      case 1:
        setDrawCoords(draw_coords2_, num_draw_coords2_);
        break;
      case 2:
        setDrawCoords(draw_coords3_, num_draw_coords3_);
        break;
      default:
        setDrawCoords(draw_coords1_, num_draw_coords1_);
        break;
    }

    setCollisionCoords(collision_coords_, num_collision_coords_);
  }
}
