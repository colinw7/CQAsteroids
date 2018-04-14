'use strict';

//------

function Vector (x, y) {
  this.x = x;
  this.y = y;
}

Vector.prototype.lengthSqr = function() {
  return (this.x*this.x + this.y*this.y);
};

Vector.prototype.length = function() {
  return Math.sqrt(this.x*this.x + this.y*this.y);
};
