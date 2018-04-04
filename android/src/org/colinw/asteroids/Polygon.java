package org.colinw.asteroids;

public class Polygon {
  private Point points_[];
  private int   num_points_;
  
  Polygon(Point points[], int num_points) {
    points_     = points;
    num_points_ = num_points;
  }
  
  boolean inside(double x, double y) {
    double xinters;

    int counter = 0;

    int   i2     = num_points_ - 1;
    Point point2 = points_[i2];

    // iterate through all lines of the polygon
    for (int i1 = 0; i1 < num_points_; ++i1) {
      Point point1 = points_[i1];

      // intersect current line with horizontal line at inside point
      if (y > Math.min(point1.y(), point2.y())) {
        if (y <= Math.max(point1.y(), point2.y())) {
          if (x <= Math.max(point1.x(), point2.x())) {
            if (point1.y() != point2.y()) {
              // if we have an intersection, increase count
              xinters = (y          - point1.y())*(point2.x() - point1.x())/
                        (point2.y() - point1.y()) + point1.x();

              if (point1.x() == point2.x() || x <= xinters)
                ++counter;
            }
          }
        }
      }

      // next line
      i2     = i1;
      point2 = point1;
    }

    // if odd then success
    return ((counter % 2) != 0);
  }
}
