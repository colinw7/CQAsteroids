package org.colinw.asteroids;

public class BBox {
  private boolean set_;
  private double  xmin_, ymin_, xmax_, ymax_;
  
  BBox() {
    set_ = false;
  }
  
  BBox(double xmin, double ymin, double xmax, double ymax) {
    xmin_ = xmin;
    ymin_ = ymin;
    xmax_ = xmax;
    ymax_ = ymax;
    
    set_ = true;
  }
  
  public double xmin() { return xmin_; }
  public double ymin() { return ymin_; }
  public double xmax() { return xmax_; }
  public double ymax() { return ymax_; }
  
  void reset() {
    set_ = false;
  }
  
  void add(double x, double y) {
    if (! set_) {
      xmin_ = x; ymin_ = y;
      xmax_ = x; ymax_ = y;
      
      set_ = true;
    }
    else {
      xmin_ = Math.min(xmin_, x);
      ymin_ = Math.min(ymin_, y);
      xmax_ = Math.max(xmax_, x);
      ymax_ = Math.max(ymax_, y);
    }
  }
  
  boolean inside(double x, double y) {
    return ((x >= xmin_ && x <= xmax_) && (y >= ymin_ && y <= ymax_));
  }
}
