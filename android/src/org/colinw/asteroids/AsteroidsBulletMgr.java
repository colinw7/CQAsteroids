package org.colinw.asteroids;

import java.util.LinkedList;
import java.util.ListIterator;

public class AsteroidsBulletMgr {
  private AsteroidsView               view_;
  private LinkedList<AsteroidsBullet> bullets_;

  public AsteroidsBulletMgr(AsteroidsView view) {
   view_ = view;
   
   bullets_ = new LinkedList<AsteroidsBullet>();
  }

  public int getNumBullets() {
    return bullets_.size();
  }

  public void addBullet(double x, double y, double a, double size, double speed, double life) {
    AsteroidsBullet bullet = new AsteroidsBullet(view_, x, y, a, size, speed, life);

    bullets_.add(bullet);
  }

  public void move() {
    ListIterator<AsteroidsBullet> itr1 = bullets_.listIterator();

    while (itr1.hasNext()) {
      AsteroidsBullet bullet = itr1.next();

      bullet.move();
    }
  }
  
  public void cleanup() {
    LinkedList<AsteroidsBullet> oldObjects = new LinkedList<AsteroidsBullet>();

    ListIterator<AsteroidsBullet> itr2 = bullets_.listIterator();

    while (itr2.hasNext()) {
      AsteroidsBullet bullet = itr2.next();

      if (bullet.getRemove())
        oldObjects.add(bullet);
    }

    ListIterator<AsteroidsBullet> itr3 = oldObjects.listIterator();

    while (itr3.hasNext()) {
      AsteroidsBullet bullet = itr3.next();

      bullets_.remove(bullet);
    }
  }

  public void intersect() {
    ListIterator<AsteroidsBullet> itr = bullets_.listIterator();

    while (itr.hasNext()) {
      AsteroidsBullet bullet = itr.next();

      bullet.intersect();
    }
  }

  public void draw() {
    ListIterator<AsteroidsBullet> itr = bullets_.listIterator();

    while (itr.hasNext()) {
      AsteroidsBullet bullet = itr.next();

      bullet.draw();
    }
  }
}
