package org.colinw.asteroids;

public class Point {
  private double x_, y_;
  
  public Point(double x, double y) {
    x_ = x;
    y_ = y;
  }
  
  public Point(Point p) {
    x_ = p.x_;
    y_ = p.y_;
  }
  
  public double x() { return x_; }
  public double y() { return y_; }
  
  public void setX(double x) { x_ = x; }
  public void setY(double y) { y_ = y; }
}
