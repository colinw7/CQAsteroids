package org.colinw.asteroids;

public class Line {
  public Point start;
  public Point end;
  
  Line(double x1, double y1, double x2, double y2) {
    start = new Point(x1, y1);
    end   = new Point(x2, y2);
  }
}
