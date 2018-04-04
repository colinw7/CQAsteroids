package org.colinw.asteroids;

import java.util.LinkedList;
import java.util.ListIterator;

public class AsteroidsSaucer extends AsteroidsObject {
  private static int num_draw_coords1_ = 6;
  private static int num_draw_coords2_ = 6;
  private static int num_collision_coords_ = 4;

  private static Point draw_coords1_[] = {
    new Point( 0.50,  0.00),
    new Point( 0.25,  0.25),
    new Point(-0.25,  0.25),
    new Point(-0.50,  0.00),
    new Point(-0.25, -0.25),
    new Point( 0.25, -0.25),
  };

  private static Point draw_coords2_[] = {
    new Point( 0.50,  0.00),
    new Point( 0.25,  0.25),
    new Point(-0.25,  0.25),
    new Point(-0.50,  0.00),
    new Point(-0.25, -0.25),
    new Point( 0.25, -0.25),
  };

  private static Point collision_coords_[] = {
    new Point( 0.5, -0.25),
    new Point( 0.5,  0.25),
    new Point(-0.5,  0.25),
    new Point(-0.5, -0.25),
  };

  private AsteroidsBulletMgr  bullet_mgr_;
  private AsteroidsSaucerType type_;
  private double              bulletSize_;
  private double              bulletSpeed_;
  private double              bulletLife_;
  private int                 bulletNum_;
  private int                 fireInterval_;
  private int                 t_;

  public AsteroidsSaucer(AsteroidsView view, double x, double y, double dx, double dy, AsteroidsSaucerType type) {
    super(view, x, y, 0.0, dx, dy, 0.0, 0.1, 0, false);

    bullet_mgr_ = new AsteroidsBulletMgr(view);

    type_ = type;

    if      (type_ == AsteroidsSaucerType.ASTEROIDS_BIG_SAUCER) {
      size_         = view_.getSaucerMgr().getBigSaucerSize        ();
      score_        = view_.getSaucerMgr().getBigSaucerScore       ();
      bulletSize_   = view_.getSaucerMgr().getBigSaucerBulletSize  ();
      bulletSpeed_  = view_.getSaucerMgr().getBigSaucerBulletSpeed ();
      bulletLife_   = view_.getSaucerMgr().getBigSaucerBulletLife  ();
      bulletNum_    = view_.getSaucerMgr().getBigSaucerBulletNum   ();
      fireInterval_ = view_.getSaucerMgr().getBigSaucerFireInterval();
    }
    else if (type_ == AsteroidsSaucerType.ASTEROIDS_SMALL_SAUCER) {
      size_         = view_.getSaucerMgr().getSmallSaucerSize        ();
      score_        = view_.getSaucerMgr().getSmallSaucerScore       ();
      bulletSize_   = view_.getSaucerMgr().getSmallSaucerBulletSize  ();
      bulletSpeed_  = view_.getSaucerMgr().getSmallSaucerBulletSpeed ();
      bulletLife_   = view_.getSaucerMgr().getSmallSaucerBulletLife  ();
      bulletNum_    = view_.getSaucerMgr().getSmallSaucerBulletNum   ();
      fireInterval_ = view_.getSaucerMgr().getSmallSaucerFireInterval();
    }

    t_ = 0;

    if (type_ == AsteroidsSaucerType.ASTEROIDS_BIG_SAUCER)
      setDrawCoords(draw_coords1_, num_draw_coords1_);
    else
      setDrawCoords(draw_coords2_, num_draw_coords2_);

    setCollisionCoords(collision_coords_, num_collision_coords_);
  }

  public void move() {
    super.move();

    bullet_mgr_.move();
  }

  public void intersect() {
    intersectRocks();

    bullet_mgr_.intersect();
  }

  public void intersectRocks() {
    LinkedList<AsteroidsRock> rocks = view_.getRockMgr().getRocks();

    ListIterator<AsteroidsRock> itr = rocks.listIterator();
    
    while (itr.hasNext()) {
      AsteroidsRock rock = itr.next();
      
      if (rock.pointInside(x_, y_)) {
        rock.hit();
        
        hit();
        
        break;
      }
    }
  }

  public void draw() {
    ++t_;

    if ((t_ % fireInterval_) == 0) {
      if (bullet_mgr_.getNumBullets() >= bulletNum_)
        return;

      Point p = matrix_.multiplyPoint(0.5*size_, 0);

      bullet_mgr_.addBullet(x_ + p.x(), y_ + p.y(), a_, bulletSize_, bulletSpeed_, bulletLife_);
    }

    bullet_mgr_.draw();
  }
}
