package org.colinw.asteroids;

import java.util.LinkedList;
import java.util.ListIterator;

public class AsteroidsShip extends AsteroidsObject {
  private static int num_draw_coords_ = 4;
  private static int num_collision_coords_ = 4;

  private static Point draw_coords_[] = {
    new Point( 0.5,  0.0),
    new Point(-0.5,  0.5),
    new Point(-0.3,  0.0),
    new Point(-0.5, -0.5),
  };

  private static Point collision_coords_[] = {
    new Point( 0.5,  0.0),
    new Point(-0.5,  0.5),
    new Point(-0.3,  0.0),
    new Point(-0.5, -0.5),
  };

  private AsteroidsBulletMgr bullet_mgr_;

  private double rotateSpeed_;
  private double thrust_;
  private double thrustMax_;
  private double bulletSize_;
  private double bulletSpeed_;
  private double bulletLife_;
  private int    bulletNum_;

  private boolean visible_;

  public AsteroidsShip(AsteroidsView view) {
    this(view, 0.5, 0.5, 0.0, 0.0, 0.0, 0.0);
  }
  
  public AsteroidsShip(AsteroidsView view, double x, double y, double a, double dx, double dy, double da) {
    super(view, x, y, a, dx, dy, da, 0.1, 0, true);

    bullet_mgr_ = new AsteroidsBulletMgr(view);

    visible_ = true;

    size_        = 0.03;
    rotateSpeed_ = 0.008;
    thrust_      = 0.003;
    thrustMax_   = 0.01;
    bulletSize_  = 0.01;
    bulletSpeed_ = 0.01;
    bulletLife_  = 0.6;
    bulletNum_   = 4;

    setDrawCoords(draw_coords_, num_draw_coords_);

    setCollisionCoords(collision_coords_, num_collision_coords_);
  }

  public void init() {
    x_ = 0.5;
    y_ = 0.5;
    a_ = 0;

    dx_ = 0;
    dy_ = 0;
    da_ = 0;

    matrix_.setIdentity();
  }

  public void setVisible(boolean visible) { visible_ = visible; }

  @Override
  public void move() {
    super.move();

    bullet_mgr_.move();
  }

  @Override
  public void intersect() {
    if (! visible_) return;

    LinkedList<AsteroidsRock> rocks = view_.getRockMgr().getRocks();

    ListIterator<AsteroidsRock> itr = rocks.listIterator();

    while (itr.hasNext()) {
      AsteroidsRock rock = itr.next();
      
      if (! rock.getRemove() && rock.pointInside(x_, y_)) {
        rock.hit();

        view_.shipDestroyed();

        init();

        break;
      }
    }

    bullet_mgr_.intersect();
  }

  @Override
  public void cleanup() {
    bullet_mgr_.cleanup();
  }
  
  public void turnLeft() {
    if (! visible_) return;

    da_ += rotateSpeed_;
  }

  public void turnRight() {
    if (! visible_) return;

    da_ -= rotateSpeed_;
  }

  public void turnStop() {
    if (! visible_) return;

    da_ = 0.0;
  }

  public void thrust() {
    if (! visible_) return;

    double t = thrust_;

    Point p = matrix_.multiplyPoint(t, 0.0);

    double dx1 = dx_ + p.x();
    double dy1 = dy_ + p.y();

    double d = Math.abs(dx_*dx_ + dy_*dy_);

    if (d < thrustMax_) {
      dx_ = dx1;
      dy_ = dy1;
    }
  }

  public boolean fire() {
    if (! visible_) return false;

    if (bullet_mgr_.getNumBullets() >= bulletNum_)
      return false;

    Point p = matrix_.multiplyPoint(0.5*size_, 0);

    bullet_mgr_.addBullet(x_ + p.x(), y_ + p.y(), a_, bulletSize_, bulletSpeed_, bulletLife_);

    return true;
  }

  public void hyperspace() {
    if (! visible_) return;

    x_ = Math.random();
    y_ = Math.random();
  }

  @Override
  public void draw() {
    if (! visible_) return;

    super.draw();

    bullet_mgr_.draw();
  }
}
