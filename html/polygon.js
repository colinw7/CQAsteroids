'use strict';

//------

function Polygon (points) {
  this.points = points;
}

Polygon.prototype.inside = function(point) {
  var counter = 0;

  var i2     = this.points.length - 1;
  var point2 = this.points[i2];

  // iterate through all lines of the polygon
  for (var i1 = 0; i1 < this.points.length; ++i1) {
    var point1 = this.points[i1];

    // intersect current line with horizontal line at inside point
    if (point.y > Math.min(point1.y, point2.y)) {
      if (point.y <= Math.max(point1.y, point2.y)) {
        if (point.x <= Math.max(point1.x, point2.x)) {
          if (point1.y != point2.y) {
            // if we have an intersection, increase count
            var xinters = (point.y  - point1.y)*(point2.x - point1.x)/
                          (point2.y - point1.y) + point1.x;

            if (point1.x == point2.x || point.x <= xinters)
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
};
