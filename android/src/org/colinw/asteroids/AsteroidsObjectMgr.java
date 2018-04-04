package org.colinw.asteroids;

import java.util.LinkedList;
import java.util.ListIterator;

public class AsteroidsObjectMgr {
  protected AsteroidsView view_;

  private LinkedList<AsteroidsObject> objects_;
  private LinkedList<AsteroidsObject> newObjects_;

  public AsteroidsObjectMgr(AsteroidsView view) {
    view_ = view;
    
    objects_    = new LinkedList<AsteroidsObject>();
    newObjects_ = new LinkedList<AsteroidsObject>();
  }

  public AsteroidsShip createShip() {
    AsteroidsShip ship = new AsteroidsShip(view_);

    newObjects_.add(ship);

    return ship;
  }

  public AsteroidsBigSaucer createBigSaucer(double x, double y, double dx, double dy) {
    AsteroidsBigSaucer saucer = view_.getSaucerMgr().createBigSaucer(x, y, dx, dy);

    newObjects_.add(saucer);

    return saucer;
  }

  public AsteroidsBigRock createBigRock(double x, double y, double a, double dx, double dy, double da) {
    AsteroidsBigRock rock = view_.getRockMgr().createBigRock(x, y, a, dx,  dy, da);

    newObjects_.add(rock);

    return rock;
  }

  public AsteroidsMediumRock createMediumRock(double x, double y, double a, double dx, double dy, double da) {
    AsteroidsMediumRock rock = view_.getRockMgr().createMediumRock(x, y, a, dx,  dy, da);

    newObjects_.add(rock);

    return rock;
  }

  public AsteroidsSmallRock createSmallRock(double x, double y, double a, double dx, double dy, double da) {
    AsteroidsSmallRock rock = view_.getRockMgr().createSmallRock(x, y, a, dx,  dy, da);

    newObjects_.add(rock);

    return rock;
  }

  public void removeAll() {
    objects_.clear();
      
    newObjects_.clear();
  }
  
  public void move() {
    ListIterator<AsteroidsObject> itr = objects_.listIterator();
    
    while (itr.hasNext()) {
      AsteroidsObject object = itr.next();
      
      object.move();
    }
  }
  
  public void cleanup() {
    LinkedList<AsteroidsObject> oldObjects = new LinkedList<AsteroidsObject>();
    
    ListIterator<AsteroidsObject> itr1 = objects_.listIterator();
    
    while (itr1.hasNext()) {
      AsteroidsObject object = itr1.next();
      
      object.cleanup();
      
      if (object.getRemove())
        oldObjects.add(object);
    }

    ListIterator<AsteroidsObject> itr2 = oldObjects.listIterator();
    
    while (itr2.hasNext()) {
      AsteroidsObject object = itr2.next();
      
      objects_.remove(object); 
    }
    
    ListIterator<AsteroidsObject> itr3 = newObjects_.listIterator();
    
    while (itr3.hasNext()) {
      AsteroidsObject object = itr3.next();
      
      objects_.add(object); 
    }
    
    newObjects_.clear();
  }

  public void intersect() {
    ListIterator<AsteroidsObject> itr = objects_.listIterator();
    
    while (itr.hasNext()) {
      AsteroidsObject object = itr.next();
      
      object.intersect();
    }
  }

  public void draw() {
    ListIterator<AsteroidsObject> itr = objects_.listIterator();
    
    while (itr.hasNext()) {
      AsteroidsObject object = itr.next();
      
      object.draw();
    }
  }
}
