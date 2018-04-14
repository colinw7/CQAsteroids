'use strict';

//------

function BBox (x1, y1, x2, y2) {
  if (x1 != undefined) {
    this.x1 = x1;
    this.y1 = y1;
    this.x2 = x2;
    this.y2 = y2;

    this.set = true;
  }
  else {
    this.set = false;
  }
}

BBox.prototype.reset = function() {
  this.set = false;
};

BBox.prototype.add = function(p) {
  if (! this.set) {
    this.x1 = p.x;
    this.y1 = p.y;
    this.x2 = p.x;
    this.y2 = p.y;

    this.set = true;
  }
  else {
    this.x1 = Math.min(this.x1, p.x);
    this.y1 = Math.min(this.y1, p.y);
    this.x2 = Math.max(this.x2, p.x);
    this.y2 = Math.max(this.y2, p.y);
  }
};

BBox.prototype.inside = function(p) {
  if (! this.set)
    return false;

  return (p.x >= this.x1 && p.x <= this.x2 && p.y >= this.y1 && p.y <= this.y2);
};
