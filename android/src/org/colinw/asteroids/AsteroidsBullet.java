package org.colinw.asteroids;

import java.util.LinkedList;
import java.util.ListIterator;

public class AsteroidsBullet extends AsteroidsObject {
  static Point draw_coords_[] = {
    new Point(-0.1, -0.1),
    new Point( 0.1, -0.1),
    new Point(-0.1,  0.1),
    new Point( 0.1,  0.1),
  };

  static int num_draw_coords_ = 4;

  static Point collision_coords_[] = {
    new Point(-0.1, -0.1),
    new Point( 0.1, -0.1),
    new Point(-0.1,  0.1),
    new Point( 0.1,  0.1),
  };

  static int num_collision_coords_ = 4;

  private double speed_;
  private double life_;

  private double d_;

  public AsteroidsBullet(AsteroidsView view, double x, double y, double a, double size, double speed, double life) {
    super(view, x, y, a, 0.0, 0.0, 0.0, size, 0, true);

    speed_ = speed;
    life_  = life;

    matrix_.setRotation(2*Math.PI*a_);

    Point p = matrix_.multiplyPoint(speed_, 0);

    dx_ = p.x();
    dy_ = p.y();
    
    d_ = 0.0;

    setDrawCoords(draw_coords_, num_draw_coords_);

    setCollisionCoords(collision_coords_, num_collision_coords_);
  }

  @Override
  public void move() {
    d_ += speed_;

    if (d_ > life_)
      setRemove();

    super.move();
  }

  @Override
  public void intersect() {
    intersectRocks();

    intersectSaucers();
  }

  public void intersectRocks() {
    LinkedList<AsteroidsRock> rocks = view_.getRockMgr().getRocks();

    ListIterator<AsteroidsRock> itr = rocks.listIterator();
    
    while (itr.hasNext()) {
      AsteroidsRock rock = itr.next();
      
      if (rock.pointInside(x_, y_)) {
        rock.hit();
        
        setRemove();
        
        break;
      }
    }
  }

  public void intersectSaucers() {
    AsteroidsSaucerMgr saucer_mgr = view_.getSaucerMgr();

    LinkedList<AsteroidsSaucer> saucers = saucer_mgr.getSaucers();

    ListIterator<AsteroidsSaucer> itr = saucers.listIterator();

    while (itr.hasNext()) {
      AsteroidsSaucer saucer = itr.next();
      
      if (saucer.pointInside(x_, y_)) {
        saucer.hit();
        
        setRemove();
        
        break;
      }
    }
  }

  public void destroy() {
    hit();
  }
}