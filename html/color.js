'use strict';

function Color (r, g, b, a) {
  this.r = r;
  this.g = g;
  this.b = b;
  this.a = a;
}

Color.prototype.encodeRGB = function() {
  var s = "rgba(" + String(255*this.r) + "," +
                    String(255*this.g) + "," +
                    String(255*this.b) + "," +
                    String(this.a) + ")";

  return s;
};
