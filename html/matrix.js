'use strict';

//------

// a b tx
// c d ty
// 0 0 1
function Matrix () {
  this.a = 1.0; this.b = 0.0;
  this.c = 0.0; this.d = 1.0;

  this.tx = 0.0; this.ty = 0.0;
}

Matrix.prototype.multiplyPoint = function(p) {
  return new Point(this.a*p.x + this.b*p.y + this.tx,
                   this.c*p.x + this.d*p.y + this.ty);
};

Matrix.prototype.setRotation = function(a) {
  var c = Math.cos(a);
  var s = Math.sin(a);

  this.a = c; this.b = -s;
  this.c = s; this.d =  c;

  this.tx = 0.0; this.ty = 0.0;
};
