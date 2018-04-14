'use strict';

var asteroids = new Asteroids();

window.addEventListener("load", eventWindowLoaded, false);

var RockType   = Object.freeze({ "NONE":0, "BIG":1, "MEDIUM":2, "SMALL":3 });
var SaucerType = Object.freeze({ "NONE":0, "BIG":1, "SMALL":2 });
var ObjectType = Object.freeze({ "NONE":0, "SHIP":1, "ROCK":2, "BULLET":3,
                                 "SAUCER":4, "EXPLOSION":5 });
var ShapeType  = Object.freeze({ "NONE":0, "SHIP":1, "SHIP_THRUST":2,
                                 "ROCK1":3, "ROCK2":4, "ROCK3":5,
                                 "SMALL_SAUCER":6, "BIG_SAUCER":7,
                                 "BULLET":8 });

//------

function eventWindowLoaded () {
  if (canvasSupport()) {
    asteroids.init();

    (function drawFrame () {
      var canvas = document.getElementById("canvas");

      window.requestAnimationFrame(drawFrame, canvas);

      asteroids.update();
    }());
  }
}

function canvasSupport () {
  return true;
  //return Modernizr.canvas;
}

function randInRange(low, high) {
  return Math.random()*(high - low) + low;
}

//------

function Asteroids () {
  this.rockMgr      = new AsteroidsRockMgr     ();
  this.objectMgr    = new AsteroidsObjectMgr   ();
  this.saucerMgr    = new AsteroidsSaucerMgr   ();
  this.explosionMgr = new AsteroidsExplosionMgr();
  this.shapeMgr     = new AsteroidsShapeMgr    ();

  this.score = new AsteroidsScore();

  this.level = 0;

  this.paused = false;

  this.gameOver = false;

  this.lfont = new LFont();

  this.lfont.init();

  this.leftKey       = 90;  // z
  this.rightKey      = 88;  // x
  this.thrustKey     = 190; // .
  this.fireKey       = 191; // /
  this.hyperspaceKey = 32;  // Space
  this.newgameKey    = 27;  // Escape
  this.pauseKey      = 80;  // P
  this.colorKey      = 112; // F1
  this.fillKey       = 113; // F2

  this.colored = false;
  this.filled  = false;

  this.showStatus = false;
  this.refresh    = 60;
}

Asteroids.prototype.init = function() {
  this.canvas = document.getElementById("canvas");
  this.gc     = this.canvas.getContext("2d");

  //---

  window.addEventListener("keydown", function(e) {
    if      (e.which === asteroids.leftKey      ) asteroids.shipTurnLeft();
    else if (e.which === asteroids.rightKey     ) asteroids.shipTurnRight();
    else if (e.which === asteroids.thrustKey    ) asteroids.shipThrust();
    else if (e.which === asteroids.fireKey      ) asteroids.shipFire();
    else if (e.which === asteroids.hyperspaceKey) asteroids.shipHyperspace();
    else if (e.which === asteroids.newgameKey   ) asteroids.newGame();
    else if (e.which === asteroids.pauseKey     ) asteroids.togglePause();
    else if (e.which === asteroids.colorKey     ) asteroids.colored = ! asteroids.colored;
    else if (e.which === asteroids.fillKey      ) asteroids.filled  = ! asteroids.filled;
    else                                          console.log(e.which);

    e.preventDefault();
  }, false);

  window.addEventListener("keyup", function(e) {
    if      (e.which === asteroids.leftKey  ) asteroids.shipTurnStop();
    else if (e.which === asteroids.rightKey ) asteroids.shipTurnStop();
    else if (e.which === asteroids.thrustKey) asteroids.shipStopThrust();

    e.preventDefault();
  }, false);

  //---

  this.ship = this.objectMgr.createShip();

  this.saucerMgr.init();

  this.nextLevel();

  this.shootSound   = new Audio("sounds/shoot.wav");
  this.explodeSound = new Audio("sounds/explosion.wav");
  this.hyperSound   = new Audio("sounds/hyperspace.wav");
  this.thrustSound  = new Audio("sounds/thrust.wav");
};

Asteroids.prototype.newGame = function() {
  this.gameOver = false;
  this.paused   = false;

  this.ship.visible = true;

  this.level = 0;

  this.ship.init();

  this.score.reset();

  this.rockMgr.removeAll();

  this.saucerMgr.reset();

  this.explosionMgr.removeAll();

  this.nextLevel();
};

Asteroids.prototype.togglePause = function(b) {
  this.paused = ! this.paused;
};

Asteroids.prototype.nextLevel = function() {
  ++this.level;

  this.objectMgr.createBigRock(new Point(0.0, 0.0), 0.0, this.scaledSpeed( 0.05,  0.05), 0.003);
  this.objectMgr.createBigRock(new Point(1.0, 0.0), 0.0, this.scaledSpeed(-0.06,  0.06), 0.004);
  this.objectMgr.createBigRock(new Point(0.0, 1.0), 0.0, this.scaledSpeed( 0.07, -0.07), 0.005);
  this.objectMgr.createBigRock(new Point(1.0, 1.0), 0.0, this.scaledSpeed(-0.08, -0.08), 0.006);
};

Asteroids.prototype.shipTurnLeft = function() {
  this.ship.turnLeft();
};

Asteroids.prototype.shipTurnRight = function() {
  this.ship.turnRight();
};

Asteroids.prototype.shipTurnStop = function() {
  this.ship.turnStop();
};

Asteroids.prototype.shipThrust = function() {
  if (! this.ship.thrust())
    return;

  this.playSound("ship.thrust");
};

Asteroids.prototype.shipStopThrust = function() {
  if (! this.ship.stopThrust())
    return;
};

Asteroids.prototype.shipFire = function() {
  if (! this.ship.fire())
    return false;

  this.playSound("ship.fire");

  return true;
};

Asteroids.prototype.shipHyperspace = function() {
  if (! this.ship.hyperspace())
    return;

  this.playSound("ship.hyperspace");
};

Asteroids.prototype.explode = function(pos) {
  this.explosionMgr.addExplosion(null, pos);
};

Asteroids.prototype.update = function() {
  if (! this.paused) {
    this.objectMgr.move();

    if (! this.gameOver)
      this.objectMgr.intersect();

    if (! this.gameOver)
      this.saucerMgr.update();

    this.explosionMgr.update();
  }

  //---

  this.gc.fillStyle = "#000000";

  this.gc.fillRect(0, 0, this.canvas.width, this.canvas.height);

  this.setColor(new Color(1.0,1.0,1.0,1.0));

  //---

  this.objectMgr.draw();

  this.explosionMgr.draw();

  this.score.draw();

  if (! this.gameOver) {
    if (this.rockMgr.rocks.length === 0)
      this.nextLevel();
  }

  if      (this.paused) {
    var p = new Point(0.5, 0.66);
    var s = 0.07;

    this.drawCenteredString(p, s, "PAUSED");
  }
  else if (this.gameOver) {
    var p = new Point(0.5, 0.46);
    var s = 0.07;

    this.drawCenteredString(p, s, "GAME OVER");
  }

  if (this.showStatus) {
    var p = new Point(0.5, 0.8);

    var s = 0.01;

    var statusStr = "";

    statusStr += this.saucerMgr.statusStr();

    this.drawCenteredString(p, s, statusStr);
  }
};

Asteroids.prototype.setColor = function(c) {
  this.gc.strokeStyle = c.encodeRGB();
  this.gc.fillStyle   = c.encodeRGB();
};

Asteroids.prototype.drawPolygon = function(points) {
  this.gc.beginPath();

  for (var i = 0; i < points.length; ++i) {
    var p = this.mapPoint(points[i]);

    if (i === 0)
      this.gc.moveTo(p.x, p.y);
    else
      this.gc.lineTo(p.x, p.y);
  }

  this.gc.closePath();

  this.gc.stroke();
};

Asteroids.prototype.fillPolygon = function(points) {
  this.gc.beginPath();

  for (var i = 0; i < points.length; ++i) {
    var p = this.mapPoint(points[i]);

    if (i === 0)
      this.gc.moveTo(p.x, p.y);
    else
      this.gc.lineTo(p.x, p.y);
  }

  this.gc.closePath();

  this.gc.fill();
  this.gc.stroke();
};

Asteroids.prototype.drawLine = function(p1, p2) {
  var p1m = this.mapPoint(p1);
  var p2m = this.mapPoint(p2);

  this.gc.beginPath();

  this.gc.moveTo(p1m.x, p1m.y);
  this.gc.lineTo(p2m.x, p2m.y);

  this.gc.stroke();
};

Asteroids.prototype.drawCenteredString = function(p, size, str) {
  this.drawString(new Point(p.x - size*str.length/2.0, p.y), size, str);
};

Asteroids.prototype.drawString = function(p, size, str) {
  for (var i = 0; i < str.length; ++i) {
    this.drawChar(p, size, str[i]);

    p.x += size;
  }
};

Asteroids.prototype.drawChar = function(p, size, c) {
  this.setColor(new Color(1.0, 1.0, 1.0, 1.0));

  var font_def = this.lfont.getFontDef(c);

  for (var i = 0; i < font_def.lines.length; ++i) {
    var line = font_def.lines[i];

    var x1 = line.start.x*size;
    var y1 = line.start.y*size;
    var x2 = line.end  .x*size;
    var y2 = line.end  .y*size;

    this.drawLine(new Point(p.x + x1, p.y + y1), new Point(p.x + x2, p.y + y2));
  }
};

Asteroids.prototype.addScore = function(score) {
  this.score.add(score);
};

Asteroids.prototype.shipDestroyed = function() {
  this.playSound("ship.hit");

  if (this.score.lives > 0) {
    this.score.die();
  }
  else {
    this.ship.visible = false;

    this.gameOver = true;
  }
};

Asteroids.prototype.scaledValue = function(v) {
  return v/this.refresh;
};

Asteroids.prototype.scaledSpeed = function(x, y) {
  return new Vector(x/this.refresh, y/this.refresh);
};

Asteroids.prototype.playSound = function(name) {
  if      (name == "ship.thrust")
    this.thrustSound.play();
  else if (name == "ship.fire")
    this.shootSound.play();
  else if (name == "ship.hyperspace")
    this.hyperSound.play();
  else if (name == "ship.hit")
    this.explodeSound.play();
  else if (name == "rock.hit")
    this.explodeSound.play();
  else if (name == "saucer.fire")
    this.shootSound.play();
  else if (name == "saucer.hit")
    this.explodeSound.play();
  else
    assert(false, "bad sound");
};

Asteroids.prototype.mapPoint = function(p) {
  return new Point(p.x *this.canvas.width, (1.0 - p.y)*this.canvas.height);
};

//------

function AsteroidsRockMgr () {
  this.bigRockScore    = 20;
  this.bigRockSize     = 0.0700;
  this.mediumRockScore = 50;
  this.mediumRockSize  = 0.0350;
  this.smallRockScore  = 100;
  this.smallRockSize   = 0.0175;
  
  this.rocks = [];
}

AsteroidsRockMgr.prototype.createBigRock = function(p, angle, v, da) {
  var rock = new AsteroidsBigRock(p, angle, v, da);

  rock.init();

  this.rocks.push(rock);

  return rock;
};

AsteroidsRockMgr.prototype.createMediumRock = function(p, angle, v, da) {
  var rock = new AsteroidsMediumRock(p, angle, v, da); 

  rock.init();

  this.rocks.push(rock);

  return rock;
};

AsteroidsRockMgr.prototype.createSmallRock = function(p, angle, v, da) {
  var rock = new AsteroidsSmallRock(p, angle, v, da); 

  rock.init();

  this.rocks.push(rock);

  return rock;
};

AsteroidsRockMgr.prototype.removeRock = function(rock) {
  var n = this.rocks.length;

  for (var i = 0; i < n; ++i) {
    if (this.rocks[i] === rock) {
      for (var j = i + 1; j < n; ++j) {
        this.rocks[j - 1] = this.rocks[j];
      }
      this.rocks.pop();
      return;
    }
  }
};

AsteroidsRockMgr.prototype.removeAll = function() {
  for (var i = 0; i < this.rocks.length; ++i)
    this.rocks[i].remove = true;
};

//------

function AsteroidsBigRock (p, angle, v, da) {
  // inherit from rock
  AsteroidsRock.call(this, p, angle, v, da);

  AsteroidsBigRock.prototype.setDrawCoords    = AsteroidsRock.prototype.setDrawCoords;
  AsteroidsBigRock.prototype.updateDrawCoords = AsteroidsRock.prototype.updateDrawCoords;

  AsteroidsBigRock.prototype.setCollisionCoords =
    AsteroidsRock.prototype.setCollisionCoords;
  AsteroidsBigRock.prototype.updateCollisionCoords =
    AsteroidsRock.prototype.updateCollisionCoords;

  AsteroidsBigRock.prototype.move         = AsteroidsRock.prototype.move;
  AsteroidsBigRock.prototype.intersect    = AsteroidsRock.prototype.intersect;
  AsteroidsBigRock.prototype.intersectObj = AsteroidsRock.prototype.intersectObj;
  AsteroidsBigRock.prototype.removeLater  = AsteroidsRock.prototype.removeLater;
  AsteroidsBigRock.prototype.pointInside  = AsteroidsRock.prototype.pointInside;
  AsteroidsBigRock.prototype.getColor     = AsteroidsRock.prototype.getColor;

  AsteroidsBigRock.prototype.init    = AsteroidsRock.prototype.init;
  AsteroidsBigRock.prototype.draw    = AsteroidsRock.prototype.draw;
  AsteroidsBigRock.prototype.destroy = AsteroidsRock.prototype.destroy;

  //---

  this.objType  = ObjectType.ROCK;
  this.rockType = RockType.BIG;
}

AsteroidsBigRock.prototype.hit = function() {
  AsteroidsRock.prototype.hit.call(this);

  var breakSpeed = randInRange(1.1, 1.3);

  var vx = this.v.x*breakSpeed;
  var vy = this.v.y*breakSpeed;

  asteroids.objectMgr.createMediumRock(this.p, this.angle + 0.25, new Vector(-vx,  vy), this.da);
  asteroids.objectMgr.createMediumRock(this.p, this.angle - 0.25, new Vector( vx, -vy), this.da);
};

//------

function AsteroidsMediumRock (p, angle, v, da) {
  // inherit from rock
  AsteroidsRock.call(this, p, angle, v, da);

  AsteroidsMediumRock.prototype.setDrawCoords    = AsteroidsRock.prototype.setDrawCoords;
  AsteroidsMediumRock.prototype.updateDrawCoords = AsteroidsRock.prototype.updateDrawCoords;

  AsteroidsMediumRock.prototype.setCollisionCoords =
    AsteroidsRock.prototype.setCollisionCoords;
  AsteroidsMediumRock.prototype.updateCollisionCoords =
    AsteroidsRock.prototype.updateCollisionCoords;

  AsteroidsMediumRock.prototype.move         = AsteroidsRock.prototype.move;
  AsteroidsMediumRock.prototype.intersect    = AsteroidsRock.prototype.intersect;
  AsteroidsMediumRock.prototype.intersectObj = AsteroidsRock.prototype.intersectObj;
  AsteroidsMediumRock.prototype.removeLater  = AsteroidsRock.prototype.removeLater;
  AsteroidsMediumRock.prototype.pointInside  = AsteroidsRock.prototype.pointInside;
  AsteroidsMediumRock.prototype.getColor     = AsteroidsRock.prototype.getColor;

  AsteroidsMediumRock.prototype.init    = AsteroidsRock.prototype.init;
  AsteroidsMediumRock.prototype.draw    = AsteroidsRock.prototype.draw;
  AsteroidsMediumRock.prototype.destroy = AsteroidsRock.prototype.destroy;

  //---

  this.objType  = ObjectType.ROCK;
  this.rockType = RockType.MEDIUM;
}

AsteroidsMediumRock.prototype.hit = function() {
  AsteroidsRock.prototype.hit.call(this);

  var breakSpeed = randInRange(1.1, 1.3);

  var vx = this.v.x*breakSpeed;
  var vy = this.v.y*breakSpeed;

  asteroids.objectMgr.createSmallRock(this.p, this.angle + 0.25, new Vector(-vx,  vy), this.da);
  asteroids.objectMgr.createSmallRock(this.p, this.angle + 0.25, new Vector(-vx, -vy), this.da);
};

//------

function AsteroidsSmallRock (p, angle, v, da) {
  // inherit from rock
  AsteroidsRock.call(this, p, angle, v, da);

  AsteroidsSmallRock.prototype.setDrawCoords    = AsteroidsRock.prototype.setDrawCoords;
  AsteroidsSmallRock.prototype.updateDrawCoords = AsteroidsRock.prototype.updateDrawCoords;

  AsteroidsSmallRock.prototype.setCollisionCoords =
    AsteroidsRock.prototype.setCollisionCoords;
  AsteroidsSmallRock.prototype.updateCollisionCoords =
    AsteroidsRock.prototype.updateCollisionCoords;

  AsteroidsSmallRock.prototype.move         = AsteroidsRock.prototype.move;
  AsteroidsSmallRock.prototype.intersect    = AsteroidsRock.prototype.intersect;
  AsteroidsSmallRock.prototype.intersectObj = AsteroidsRock.prototype.intersectObj;
  AsteroidsSmallRock.prototype.removeLater  = AsteroidsRock.prototype.removeLater;
  AsteroidsSmallRock.prototype.pointInside  = AsteroidsRock.prototype.pointInside;
  AsteroidsSmallRock.prototype.getColor     = AsteroidsRock.prototype.getColor;

  AsteroidsSmallRock.prototype.init    = AsteroidsRock.prototype.init;
  AsteroidsSmallRock.prototype.hit     = AsteroidsRock.prototype.hit;
  AsteroidsSmallRock.prototype.draw    = AsteroidsRock.prototype.draw;
  AsteroidsSmallRock.prototype.destroy = AsteroidsRock.prototype.destroy;

  //---

  this.objType  = ObjectType.ROCK;
  this.rockType = RockType.SMALL;
}

AsteroidsSmallRock.prototype.hit = function() {
  asteroids.explosionMgr.addExplosion(this, this.p);

  AsteroidsRock.prototype.hit.call(this);
};

//------

function AsteroidsRock (p, angle, v, da) {
  // inherit from object
  AsteroidsObject.call(this, p, angle, v, da, 0.1, 0, true);

  AsteroidsRock.prototype.setDrawCoords    = AsteroidsObject.prototype.setDrawCoords;
  AsteroidsRock.prototype.updateDrawCoords = AsteroidsObject.prototype.updateDrawCoords;

  AsteroidsRock.prototype.setCollisionCoords    = AsteroidsObject.prototype.setCollisionCoords;
  AsteroidsRock.prototype.updateCollisionCoords = AsteroidsObject.prototype.updateCollisionCoords;

  AsteroidsRock.prototype.move         = AsteroidsObject.prototype.move;
  AsteroidsRock.prototype.intersect    = AsteroidsObject.prototype.intersect;
  AsteroidsRock.prototype.intersectObj = AsteroidsObject.prototype.intersectObj;
  AsteroidsRock.prototype.removeLater  = AsteroidsObject.prototype.removeLater;
  AsteroidsRock.prototype.pointInside  = AsteroidsObject.prototype.pointInside;
  AsteroidsRock.prototype.getColor     = AsteroidsObject.prototype.getColor;

  //--

  this.current_rock_num = 0;

  this.rock_num = 0;

  this.objType  = ObjectType.ROCK;
  this.rockType = RockType.NONE;

  this.color = new Color(0.76, 0.57, 0.27, 1.0);
}

AsteroidsRock.prototype.init = function() {
  if      (this.rockType === RockType.BIG) {
    this.size  = asteroids.rockMgr.bigRockSize;
    this.score = asteroids.rockMgr.bigRockScore;
  }
  else if (this.rockType === RockType.MEDIUM) {
    this.size  = asteroids.rockMgr.mediumRockSize;
    this.score = asteroids.rockMgr.mediumRockScore;
  }
  else if (this.rockType === RockType.SMALL) {
    this.size  = asteroids.rockMgr.smallRockSize;
    this.score = asteroids.rockMgr.smallRockScore;
  }

  ++this.current_rock_num;

  this.current_rock_num %= 3;

  this.rock_num = this.current_rock_num;

  //---

  if      (this.rock_num === 0) {
    this.setDrawCoords     (asteroids.shapeMgr.drawPoints     (ShapeType.ROCK1));
    this.setCollisionCoords(asteroids.shapeMgr.collisionPoints(ShapeType.ROCK1));
  }
  else if (this.rock_num === 1) {
    this.setDrawCoords     (asteroids.shapeMgr.drawPoints     (ShapeType.ROCK2));
    this.setCollisionCoords(asteroids.shapeMgr.collisionPoints(ShapeType.ROCK2));
  }
  else if (this.rock_num === 2) {
    this.setDrawCoords     (asteroids.shapeMgr.drawPoints     (ShapeType.ROCK3));
    this.setCollisionCoords(asteroids.shapeMgr.collisionPoints(ShapeType.ROCK3));
  }
};

AsteroidsRock.prototype.destroy = function() {
  asteroids.rockMgr.removeRock(this);
};

AsteroidsRock.prototype.hit = function() {
  asteroids.playSound("rock.hit");

  AsteroidsObject.prototype.hit.call(this);
};

AsteroidsRock.prototype.draw = function() {
  AsteroidsObject.prototype.draw.call(this);
};

//------

function AsteroidsSaucerMgr () {
  this.t1 = 0;
  this.t2 = 0;

  this.bigSaucerScore        = 500;
  this.bigSaucerSize         = 0.03;
  this.bigSaucerBulletSize   = 0.01;
  this.bigSaucerBulletSpeed  = 0.3;
  this.bigSaucerBulletLife   = 100;
  this.bigSaucerBulletNum    = 4;
  this.bigSaucerDelay        = 250;
  this.bigSaucerFireInterval = 20;

  this.smallSaucerScore        = 1000;
  this.smallSaucerSize         = 0.015;
  this.smallSaucerBulletSize   = 0.01;
  this.smallSaucerBulletSpeed  = 0.2;
  this.smallSaucerBulletLife   = 100;
  this.smallSaucerBulletNum    = 4;
  this.smallSaucerDelay        = 3;
  this.smallSaucerFireInterval = 30;

  this.bigSaucer   = null;
  this.smallSaucer = null;
}

AsteroidsSaucerMgr.prototype.init = function() {
  this.bigSaucer   = asteroids.objectMgr.createBigSaucer  ();
  this.smallSaucer = asteroids.objectMgr.createSmallSaucer();
};

AsteroidsSaucerMgr.prototype.getVisibleSaucer = function() {
  if (this.bigSaucer.visible)
    return this.bigSaucer;

  if (this.smallSaucer.visible)
    return this.smallSaucer;

  return null;
};

AsteroidsSaucerMgr.prototype.update = function() {
  this.t1 += 1;

  if (this.bigSaucer.visible || this.smallSaucer.visible)
    return;

  if (this.t1 >= this.bigSaucerDelay) {
    this.t2 += 1;

    var y = randInRange(0.0, 0.5);

    if (y < 0.25)
      y = 0.625 + y;
    else
      y = 0.375 - (y - 0.25);

    if (this.t2 >= this.smallSaucerDelay)
      this.showSmallSaucer(new Point(0.0, 0.75), asteroids.scaledSpeed(0.3, 0.0));
    else
      this.showBigSaucer(new Point(0.0, 0.75), asteroids.scaledSpeed(0.2, 0.0));
  }
};

AsteroidsSaucerMgr.prototype.showBigSaucer = function(p, v) {
  this.bigSaucer.visible = true;
  this.bigSaucer.p       = p;
  this.bigSaucer.v       = v;
};

AsteroidsSaucerMgr.prototype.showSmallSaucer = function(p, v) {
  this.smallSaucer.visible = true;
  this.smallSaucer.p       = p;
  this.smallSaucer.v       = v;
};

AsteroidsSaucerMgr.prototype.reset = function() {
  this.smallSaucer.visible = false;
  this.bigSaucer  .visible = false;

  this.bigSaucer  .reset();
  this.smallSaucer.reset();

  this.t1 = 0;
  this.t2 = 0;
};

AsteroidsSaucerMgr.prototype.restart = function(type) {
  if      (type === SaucerType.BIG) {
    this.t1 = 0;
  }
  else if (type === SaucerType.SMALL) {
    this.t1 = 0;
    this.t2 = 0;
  }
};

AsteroidsSaucerMgr.prototype.statusStr = function() {
  var str = "SaucerMgr:";

  str += " " + String(t1_) + "," + String(t2_);

  if (this.bigSaucer.visible)
    str += " Big";

  if (this.smallSaucer.visible)
    str += " Small";

  return str;
};

//------

function AsteroidsBigSaucer () {
  // inherit from saucer
  AsteroidsSaucer.call(this);

  AsteroidsBigSaucer.prototype.setDrawCoords    = AsteroidsSaucer.prototype.setDrawCoords;
  AsteroidsBigSaucer.prototype.updateDrawCoords = AsteroidsSaucer.prototype.updateDrawCoords;

  AsteroidsBigSaucer.prototype.setCollisionCoords =
    AsteroidsSaucer.prototype.setCollisionCoords;
  AsteroidsBigSaucer.prototype.updateCollisionCoords =
    AsteroidsSaucer.prototype.updateCollisionCoords;

  AsteroidsBigSaucer.prototype.init           = AsteroidsSaucer.prototype.init;
  AsteroidsBigSaucer.prototype.move           = AsteroidsSaucer.prototype.move;
  AsteroidsBigSaucer.prototype.intersect      = AsteroidsSaucer.prototype.intersect;
  AsteroidsBigSaucer.prototype.intersectRocks = AsteroidsSaucer.prototype.intersectRocks;
  AsteroidsBigSaucer.prototype.intersectObj   = AsteroidsSaucer.prototype.intersectObj;
  AsteroidsBigSaucer.prototype.pointInside    = AsteroidsSaucer.prototype.pointInside;
  AsteroidsBigSaucer.prototype.hit            = AsteroidsSaucer.prototype.hit;
  AsteroidsBigSaucer.prototype.getColor       = AsteroidsSaucer.prototype.getColor;
  AsteroidsBigSaucer.prototype.draw           = AsteroidsSaucer.prototype.draw;
  AsteroidsBigSaucer.prototype.destroy        = AsteroidsSaucer.prototype.destroy;
  AsteroidsBigSaucer.prototype.reset          = AsteroidsSaucer.prototype.reset;
  AsteroidsBigSaucer.prototype.removeLater    = AsteroidsSaucer.prototype.removeLater;

  //---

  this.objType    = ObjectType.SAUCER;
  this.saucerType = SaucerType.BIG;
}

//------

function AsteroidsSmallSaucer () {
  // inherit from saucer
  AsteroidsSaucer.call(this);

  AsteroidsSmallSaucer.prototype.setDrawCoords    = AsteroidsSaucer.prototype.setDrawCoords;
  AsteroidsSmallSaucer.prototype.updateDrawCoords = AsteroidsSaucer.prototype.updateDrawCoords;

  AsteroidsSmallSaucer.prototype.setCollisionCoords =
    AsteroidsSaucer.prototype.setCollisionCoords;
  AsteroidsSmallSaucer.prototype.updateCollisionCoords =
    AsteroidsSaucer.prototype.updateCollisionCoords;

  AsteroidsSmallSaucer.prototype.init           = AsteroidsSaucer.prototype.init;
  AsteroidsSmallSaucer.prototype.move           = AsteroidsSaucer.prototype.move;
  AsteroidsSmallSaucer.prototype.intersect      = AsteroidsSaucer.prototype.intersect;
  AsteroidsSmallSaucer.prototype.intersectRocks = AsteroidsSaucer.prototype.intersectRocks;
  AsteroidsSmallSaucer.prototype.intersectObj   = AsteroidsSaucer.prototype.intersectObj;
  AsteroidsSmallSaucer.prototype.pointInside    = AsteroidsSaucer.prototype.pointInside;
  AsteroidsSmallSaucer.prototype.hit            = AsteroidsSaucer.prototype.hit;
  AsteroidsSmallSaucer.prototype.getColor       = AsteroidsSaucer.prototype.getColor;
  AsteroidsSmallSaucer.prototype.draw           = AsteroidsSaucer.prototype.draw;
  AsteroidsSmallSaucer.prototype.destroy        = AsteroidsSaucer.prototype.destroy;
  AsteroidsSmallSaucer.prototype.reset          = AsteroidsSaucer.prototype.reset;
  AsteroidsSmallSaucer.prototype.removeLater    = AsteroidsSaucer.prototype.removeLater;

  //---

  this.objType    = ObjectType.SAUCER;
  this.saucerType = SaucerType.SMALL;
}

//------

function AsteroidsSaucer () {
  // inherit from object
  AsteroidsObject.call(this, new Point(0.0, 0.0), 0.0, new Vector(0.0, 0.0), 0.0, 0.1, 0, false);

  AsteroidsSaucer.prototype.setDrawCoords    = AsteroidsObject.prototype.setDrawCoords;
  AsteroidsSaucer.prototype.updateDrawCoords = AsteroidsObject.prototype.updateDrawCoords;

  AsteroidsSaucer.prototype.setCollisionCoords =
    AsteroidsObject.prototype.setCollisionCoords;
  AsteroidsSaucer.prototype.updateCollisionCoords =
    AsteroidsObject.prototype.updateCollisionCoords;

  AsteroidsSaucer.prototype.intersectObj = AsteroidsObject.prototype.intersectObj;
  AsteroidsSaucer.prototype.pointInside  = AsteroidsObject.prototype.pointInside;
  AsteroidsSaucer.prototype.hit          = AsteroidsObject.prototype.hit;
  AsteroidsSaucer.prototype.getColor     = AsteroidsObject.prototype.getColor;

  //---

  this.bulletMgr = new AsteroidsBulletMgr(this);

  this.t = 0;

  this.visible = false;

  //---

  this.color = new Color(0.9, 0.0, 0.0, 1.0);

  this.objType    = ObjectType.SAUCER;
  this.saucerType = SaucerType.NONE;
}

AsteroidsSaucer.prototype.init = function() {
  if      (this.saucerType === SaucerType.BIG) {
    this.size         = asteroids.saucerMgr.bigSaucerSize;
    this.score        = asteroids.saucerMgr.bigSaucerScore;
    this.bulletSize   = asteroids.saucerMgr.bigSaucerBulletSize;
    this.bulletSpeed  = asteroids.saucerMgr.bigSaucerBulletSpeed;
    this.bulletLife   = asteroids.saucerMgr.bigSaucerBulletLife;
    this.bulletNum    = asteroids.saucerMgr.bigSaucerBulletNum;
    this.fireInterval = asteroids.saucerMgr.bigSaucerFireInterval;
  }
  else if (this.saucerType === SaucerType.SMALL) {
    this.size         = asteroids.saucerMgr.smallSaucerSize;
    this.score        = asteroids.saucerMgr.smallSaucerScore;
    this.bulletSize   = asteroids.saucerMgr.smallSaucerBulletSize;
    this.bulletSpeed  = asteroids.saucerMgr.smallSaucerBulletSpeed;
    this.bulletLife   = asteroids.saucerMgr.smallSaucerBulletLife;
    this.bulletNum    = asteroids.saucerMgr.smallSaucerBulletNum;
    this.fireInterval = asteroids.saucerMgr.smallSaucerFireInterval;
  }

  if      (this.saucerType === SaucerType.BIG) {
    this.setDrawCoords     (asteroids.shapeMgr.drawPoints(ShapeType.BIG_SAUCER));
    this.setCollisionCoords(asteroids.shapeMgr.drawPoints(ShapeType.BIG_SAUCER));
  }
  else if (this.saucerType === SaucerType.SMALL) {
    this.setDrawCoords     (asteroids.shapeMgr.drawPoints(ShapeType.SMALL_SAUCER));
    this.setCollisionCoords(asteroids.shapeMgr.drawPoints(ShapeType.SMALL_SAUCER));
  }
};

AsteroidsSaucer.prototype.reset = function() {
  this.bulletMgr.reset();
};

AsteroidsSaucer.prototype.move = function() {
  if (this.visible)
    AsteroidsObject.prototype.move.call(this);

  this.bulletMgr.move();
};

AsteroidsSaucer.prototype.intersect = function() {
  if (this.visible)
    this.intersectRocks();

  this.bulletMgr.intersect();
};

AsteroidsSaucer.prototype.draw = function() {
  if (this.visible) {
    AsteroidsObject.prototype.draw.call(this);

    ++this.t;

    if ((this.t % this.fireInterval) === 0) {
      if (this.bulletMgr.bullets.length >= this.bulletNum)
        return;

      var p = this.matrix.multiplyPoint(new Point(0.5*this.size, 0));

      var bulletPos = new Point(this.p.x + p.x, this.p.y + p.y);

      var shipPos = asteroids.ship.p;

      var bulletSpeed = asteroids.scaledValue(this.bulletSpeed);

      var bullet =
        this.bulletMgr.addBullet(bulletPos, 0.0, this.bulletSize, bulletSpeed, this.bulletLife);

      var a = Math.atan2(shipPos.y - bulletPos.y, shipPos.x - bulletPos.x)/(2*Math.PI);

      a += randInRange(-0.1, 0.1);

      bullet.setDirection(a);

      if (this.type === SaucerType.SMALL)
        bullet.setTarget(astreroids.ship);

      asteroids.playSound("saucer.fire");
    }

    this.bulletMgr.draw();
  }
};

AsteroidsSaucer.prototype.intersectRocks = function() {
  assert(this.visible);

  for (var i = 0; i < asteroids.rockMgr.rocks.length; ++i) {
    var rock = asteroids.rockMgr.rocks[i];

    if (rock.intersectObj(this)) {
      rock.hit();

      this.destroy();

      break;
    }
  }
};

AsteroidsSaucer.prototype.removeLater = function() {
  this.destroy();
};

AsteroidsSaucer.prototype.destroy = function() {
  if (! this.visible)
    return;

  asteroids.explosionMgr.addExplosion(this, this.p);

  asteroids.saucerMgr.restart();

  this.visible = false;
};

AsteroidsSaucer.prototype.hit = function() {
  if (! this.visible)
    return;

  asteroids.playSound("saucer.hit");

  AsteroidsObject.prototype.hit.call(this);
};

//------

function AsteroidsBulletMgr (parent) {
  this.parent  = parent;
  this.bullets = [];
}

AsteroidsBulletMgr.prototype.addBullet = function(p, angle, size, speed, life) {
  var bullet = new AsteroidsBullet(p, angle, size, speed, life);

  bullet.bulletMgr = this;

  bullet.init();

  this.bullets.push(bullet);

  return bullet;
};

AsteroidsBulletMgr.prototype.removeBullet = function(bullet) {
  var n = this.bullets.length;

  for (var i = 0; i < n; ++i) {
    if (this.bullets[i] === bullet) {
      for (var j = i + 1; j < n; ++j) {
        this.bullets[j - 1] = this.bullets[j];
      }
      this.bullets.pop();
      return;
    }
  }
};

AsteroidsBulletMgr.prototype.reset = function() {
  this.bullets = [];
};

AsteroidsBulletMgr.prototype.move = function() {
  var nb = this.bullets.length;

  if (nb === 0)
    return;

  for (var i = 0; i < nb; ++i)
    this.bullets[i].move();

  var nr = 0;

  for (var i = 0; i < nb; ++i) {
    var bullet = this.bullets[i];

    if (bullet.remove)
      ++nr;
  }

  if (nr > 0) {
    var newBullets = [];
    var oldBullets = [];

    for (var i = 0; i < nb; ++i) {
      var bullet = this.bullets[i];

      if (! bullet.remove)
        newBullets.push(bullet);
      else
        oldBullets.push(bullet);
    }

    this.bullets = newBullets;

    for (var i = 0; i < oldBullets.length; ++i)
      oldBullets[i].destroy();
  }
};

AsteroidsBulletMgr.prototype.intersect = function() {
  for (var i = 0; i < this.bullets.length; ++i)
    this.bullets[i].intersect();
};

AsteroidsBulletMgr.prototype.draw = function() {
  for (var i = 0; i < this.bullets.length; ++i)
    this.bullets[i].draw();
};

//------

function AsteroidsBullet (p, angle, size, speed, life) {
  // inherit from object
  AsteroidsObject.call(this, p, angle, new Vector(0.0, 0.0), 0.0, size, 0, true);

  AsteroidsBullet.prototype.setDrawCoords    = AsteroidsObject.prototype.setDrawCoords;
  AsteroidsBullet.prototype.updateDrawCoords = AsteroidsObject.prototype.updateDrawCoords;

  AsteroidsBullet.prototype.setCollisionCoords =
    AsteroidsObject.prototype.setCollisionCoords;
  AsteroidsBullet.prototype.updateCollisionCoords =
    AsteroidsObject.prototype.updateCollisionCoords;

  AsteroidsBullet.prototype.removeLater = AsteroidsObject.prototype.removeLater;
  AsteroidsBullet.prototype.getColor    = AsteroidsObject.prototype.getColor;

  //---

  this.bulletMgr = null;

  this.speed = speed;
  this.life  = life;
  this.age   = 0;

  this.objType = ObjectType.BULLET;
}

AsteroidsBullet.prototype.init = function() {
  this.setDirection(this.angle);

  this.setDrawCoords     (asteroids.shapeMgr.drawPoints(ShapeType.BULLET));
  this.setCollisionCoords(asteroids.shapeMgr.drawPoints(ShapeType.BULLET));
};

AsteroidsBullet.prototype.setDirection = function(angle) {
  this.angle = angle;

  this.matrix.setRotation(2*Math.PI*this.angle);

  var d = this.matrix.multiplyPoint(new Point(this.speed, 0));

  this.v = new Vector(d.x, d.y);
};

AsteroidsBullet.prototype.move = function() {
  if (this.target) {
    var pos = this.target.p;

    var angle = Math.atan2(pos.y - this.p.y, pos.x - this.p.x)/(2*Math.PI);

    this.setDirection(angle);
  }

  this.age += 1;

  if (this.age > this.life)
    this.removeLater();

  AsteroidsObject.prototype.move.call(this);
};

AsteroidsBullet.prototype.intersect = function() {
  this.intersectRocks();

  if      (this.bulletMgr.parent.objType === ObjectType.SHIP) {
    this.intersectSaucers();
  }
  else if (this.bulletMgr.parent.objType === ObjectType.SAUCER) {
    var ship = asteroids.ship;

    if (ship.pointInside(this.p)) {
      ship.destroy();

      this.removeLater();
    }
  }
  else
    assert(false);
};

AsteroidsBullet.prototype.intersectRocks = function() {
  for (var i = 0; i < asteroids.rockMgr.rocks.length; ++i) {
    var rock = asteroids.rockMgr.rocks[i];

    if (rock.pointInside(this.p)) {
      rock.hit();

      this.removeLater();

      break;
    }
  }
};

AsteroidsBullet.prototype.intersectSaucers = function() {
  var saucer = asteroids.saucerMgr.getVisibleSaucer();

  if (! saucer || saucer == parent)
    return;

  if (saucer.pointInside(this.p)) {
    saucer.hit();

    this.removeLater();
  }
};

AsteroidsBullet.prototype.draw = function() {
  AsteroidsObject.prototype.draw.call(this);
}

AsteroidsBullet.prototype.destroy = function() {
  this.bulletMgr.removeBullet(this);
};

//------

function AsteroidsShip (p, angle, v, da) {
  // inherit from object
  AsteroidsObject.call(this, p, angle, v, da, 0.1, 0, true);

  AsteroidsShip.prototype.setDrawCoords    = AsteroidsObject.prototype.setDrawCoords;
  AsteroidsShip.prototype.updateDrawCoords = AsteroidsObject.prototype.updateDrawCoords;

  AsteroidsShip.prototype.setCollisionCoords    = AsteroidsObject.prototype.setCollisionCoords;
  AsteroidsShip.prototype.updateCollisionCoords = AsteroidsObject.prototype.updateCollisionCoords;

  AsteroidsShip.prototype.pointInside = AsteroidsObject.prototype.pointInside;

  //---

  this.bulletMgr = new AsteroidsBulletMgr(this);

  this.size = 0.03;

  //---

  this.rotateSpeed = 0.50;
  this.thrustSize  = 0.0003;
  this.thrustMax   = 0.01;
  this.bulletSize  = 0.02;
  this.bulletSpeed = 0.3;
  this.bulletLife  = 100;
  this.bulletNum   = 4;

  this.color = new Color(0.9, 0.9, 0.0, 1.0);

  this.visible = true;

  this.objType = ObjectType.SAUCER;
}

AsteroidsShip.prototype.init = function() {
  this.setDrawCoords     (asteroids.shapeMgr.drawPoints(ShapeType.SHIP));
  this.setCollisionCoords(asteroids.shapeMgr.drawPoints(ShapeType.SHIP));

  //---

  this.resetPosition();

  this.visible = true;

  this.exploding   = 0;
  this.invunerable = 0;
};

AsteroidsShip.prototype.resetPosition = function() {
  this.p = new Point (0.5, 0.5);
  this.v = new Vector(0.0, 0.0);
  this.a = new Vector(0.0, 0.0);

  this.angle = 0;
  this.da    = 0;

  this.matrix = new Matrix();
};

AsteroidsShip.prototype.intersect = function() {
  if (! this.visible || this.exploding > 0 || this.invunerable > 0)
    return;

  var hit = false;

  for (var i = 0; i < asteroids.rockMgr.rocks.length; ++i) {
    var rock = asteroids.rockMgr.rocks[i];

    if (! rock.remove && rock.intersectObj(this)) {
      rock.hit();

      hit = true;

      break;
    }
  }

  var saucer = asteroids.saucerMgr.getVisibleSaucer();

  if (saucer && saucer.intersectObj(this)) {
    saucer.hit();

    hit = true;
  }

  if (hit)
    this.destroy();

  //---

  this.bulletMgr.intersect();
};

AsteroidsShip.prototype.destroy = function() {
  if (! this.visible || this.exploding > 0 || this.invunerable > 0)
    return;

  asteroids.shipDestroyed();

  this.exploding = 50;

  asteroids.explosionMgr.addExplosion(this, this.p);
};

AsteroidsShip.prototype.turnLeft = function() {
  if (! this.visible || this.exploding > 0) return;

  this.da = asteroids.scaledValue(this.rotateSpeed);
};

AsteroidsShip.prototype.turnRight = function() {
  if (! this.visible || this.exploding > 0) return;

  this.da = -asteroids.scaledValue(this.rotateSpeed);
};

AsteroidsShip.prototype.turnStop = function() {
  if (! this.visible || this.exploding > 0) return;

  this.da = 0.0;
};

AsteroidsShip.prototype.thrust = function() {
  if (! this.visible || this.exploding > 0)
    return false;

  var tp = this.matrix.multiplyPoint(new Point(this.thrustSize, 0.0));

/*
  var dx1 = this.v.x + tp.x;
  var dy1 = this.v.y + tp.y;

  var d = this.v.lengthSqr();

  if (d < this.thrustMax)
    this.v = new Vector(dx1, dy1);
*/
  var a = new Vector(tp.x, tp.y);

  var d = a.lengthSqr();

  if (d < this.thrustMax)
    this.a = a;

  this.setDrawCoords(asteroids.shapeMgr.drawPoints(ShapeType.SHIP_THRUST));

  return true;
};

AsteroidsShip.prototype.stopThrust = function() {
  this.da = 0;

  this.setDrawCoords(asteroids.shapeMgr.drawPoints(ShapeType.SHIP));
};

AsteroidsShip.prototype.fire = function() {
  if (! this.visible || this.exploding > 0) return false;

  if (this.bulletMgr.bullets.length >= this.bulletNum)
    return false;

  var p1r = this.matrix.multiplyPoint(new Point(0.5*this.size, 0));

  var bulletSpeed = asteroids.scaledValue(this.bulletSpeed) + this.v.length();

  this.bulletMgr.addBullet(new Point(this.p.x + p1r.x, this.p.y + p1r.y), this.angle,
                           this.bulletSize, bulletSpeed, this.bulletLife);

  return true;
};

AsteroidsShip.prototype.hyperspace = function() {
  if (! this.visible || this.exploding > 0)
    return false;

  this.resetPosition();

  this.p = new Point(randInRange(0.0, 1.0), randInRange(0.0, 1.0));

  return true;
};

AsteroidsShip.prototype.move = function() {
  if (! this.visible)
    return;

  assert(! asteroids.gameOver);

  if (this.exploding > 0) {
    --this.exploding;

    if (this.exploding <= 0) {
      this.init();

      this.invunerable = 50;

      AsteroidsObject.prototype.move.call(this);
    }

    return;
  }

  if (this.invunerable > 0)
    --this.invunerable;

  this.a.x *= 0.95;
  this.a.y *= 0.95;

  AsteroidsObject.prototype.move.call(this);

  this.bulletMgr.move();
};

AsteroidsShip.prototype.getColor = function() {
  if (this.invunerable > 0) {
    var c = new Color(0.5, 0.5, 0.5, 1.0);

    c.a = (50.0 - this.invunerable)/50.0;

    return c;
  }
  else {
    return AsteroidsObject.prototype.getColor.call(this);
  }
};

AsteroidsShip.prototype.draw = function() {
  if (! this.visible || this.exploding > 0) return;

  AsteroidsObject.prototype.draw.call(this);

  this.bulletMgr.draw();
};

AsteroidsShip.prototype.hit = function() {
  AsteroidsObject.prototype.hit.call(this);
};

//------

function AsteroidsExplosionMgr () {
  this.explosions = [];
}

AsteroidsExplosionMgr.prototype.addExplosion = function(parent, p) {
  var explosion = new AsteroidsExplosion(parent, p);

  this.explosions.push(explosion);
};

AsteroidsExplosionMgr.prototype.removeAll = function() {
  this.explosions = [];
};

AsteroidsExplosionMgr.prototype.update = function() {
  var newExplosions = [];

  for (var i = 0; i < this.explosions.length; ++i) {
    var explosion = this.explosions[i];

    explosion.move();

    if (! explosion.remove)
      newExplosions.push(explosion);
  }

  this.explosions = newExplosions;
};

AsteroidsExplosionMgr.prototype.draw = function() {
  for (var i = 0; i < this.explosions.length; ++i)
    this.explosions[i].draw();
};

//------

function AsteroidsExplosionLine (p1, p2) {
  this.p1 = p1;
  this.p2 = p2;

  this.v    = new Vector(0.0, 0.0);
  this.da   = 0.0;
  this.life = 0;
}

//------

function AsteroidsExplosion (parent, p) {
  AsteroidsObject.call(this, p, 0.0, new Vector(0.0, 0.0), 0.0, 0.1, 0, false);

  AsteroidsExplosion.prototype.removeLater = AsteroidsObject.prototype.removeLater;

  //---

  this.parent   = parent;
  this.lines    = [];
  this.initLife = 100;
  this.life     = this.initLife;

  var num_lines = 10;

  for (var i = 0; i < num_lines; ++i) {
    var dx = randInRange(-0.01, 0.01);
    var dy = randInRange(-0.01, 0.01);
    var lx = randInRange(0.5, 1.0);
    var ly = randInRange(0.5, 1.0);
    var vx = randInRange( 5, 10);
    var vy = randInRange( 5, 10);

    var p1 = new Point(this.p.x +    dx, this.p.y +    dy);
    var p2 = new Point(p1.x     + lx*dx, p1.y     + ly*dy);

    var l = new AsteroidsExplosionLine(p1, p2);

    l.v = asteroids.scaledSpeed(vx*dx, vy*dy);

    l.da = randInRange(0.0, 0.1);

    l.life = randInRange(0, this.life);

    this.lines.push(l);
  }

  this.objType = ObjectType.EXPLOSTION;
}

AsteroidsExplosion.prototype.move = function() {
  --this.life;

  for (var i = 0; i < this.lines.length; ++i) {
    var line = this.lines[i];

    --line.life;

    line.p1.x += line.v.x;
    line.p1.y += line.v.y;

    line.p2.x += line.v.x;
    line.p2.y += line.v.y;
  }
};

AsteroidsExplosion.prototype.draw = function() {
  if (asteroids.colored) {
    var r = 1.0;
    var g = 1.0;
    var b = 0.0;
    var a = this.life/this.initLife;

    asteroids.setColor(new Color(r, g, b, a));
  }

  var numDrawn = 0;

  for (var i = 0; i < this.lines.length; ++i) {
    var line = this.lines[i];

    if (line.life <= 0)
      continue;

    asteroids.drawLine(line.p1, line.p2);

    ++numDrawn;
  }

  if (numDrawn === 0)
    this.removeLater();
};

//------

function AsteroidsObjectMgr () {
  this.objects = [];

  this.poly_f     = [];
  this.poly_num_f = 0;

  this.poly_f[0] = [];
  this.poly_f[1] = [];
}

AsteroidsObjectMgr.prototype.createShip = function() {
  var ship = new AsteroidsShip(new Point(0.5, 0.5), 0.0, 0.0, 0.0, 0.0);

  ship.init();

  this.addObject(ship);

  return ship;
};

AsteroidsObjectMgr.prototype.createBigRock = function(p, angle, v, da) {
  var rock = asteroids.rockMgr.createBigRock(p, angle, v, da);

  this.addObject(rock);

  return rock;
};

AsteroidsObjectMgr.prototype.createMediumRock = function(p, angle, v, da) {
  var rock = asteroids.rockMgr.createMediumRock(p, angle, v, da);

  this.addObject(rock);

  return rock;
};

AsteroidsObjectMgr.prototype.createSmallRock = function(p, angle, v, da) {
  var rock = asteroids.rockMgr.createSmallRock(p, angle, v, da);

  this.addObject(rock);

  return rock;
};

AsteroidsObjectMgr.prototype.createBigSaucer = function() {
  var saucer = new AsteroidsBigSaucer();

  saucer.init();

  this.addObject(saucer);

  return saucer;
};

AsteroidsObjectMgr.prototype.createSmallSaucer = function() {
  var saucer = new AsteroidsSmallSaucer();

  saucer.init();

  this.addObject(saucer);

  return saucer;
};

AsteroidsObjectMgr.prototype.addObject = function(object) {
  this.objects.push(object);
};

AsteroidsObjectMgr.prototype.removeObject = function(object) {
  var n = this.objects.length;

  for (var i = 0; i < n; ++i) {
    if (this.objects[i] === object) {
      for (var j = i + 1; j < n; ++j) {
        this.objects[j - 1] = this.objects[j];
      }
      this.objects.pop();
      return;
    }
  }
};

AsteroidsObjectMgr.prototype.move = function() {
  for (var i = 0; i < this.objects.length; ++i) {
    this.objects[i].move();
  }

  var newObjects = [];
  var oldObjects = [];

  for (var i = 0; i < this.objects.length; ++i) {
    var object = this.objects[i];

    if (object.remove)
      oldObjects.push(object);
    else
      newObjects.push(object);
  }

  for (var i = 0; i < oldObjects.length; ++i)
    oldObjects[i].destroy();

  this.objects = newObjects;
};

AsteroidsObjectMgr.prototype.intersect = function() {
  for (var i = 0; i < this.objects.length; ++i) {
    var object = this.objects[i];

    object.intersect();
  }
};

AsteroidsObjectMgr.prototype.draw = function() {
  for (var i = 0; i < this.objects.length; ++i) {
    var object = this.objects[i];

    object.draw();
  }
};

//------

function AsteroidsObject (p, angle, v, da, size, score, wrapOnEdge) {
  this.p = new Point (p.x, p.y);
  this.v = new Vector(v.x, v.y);
  this.a = new Vector(0.0, 0.0);

  this.angle = angle;
  this.da    = da;

  this.size  = size;
  this.score = score;

  this.wrapOnEdge = wrapOnEdge;

  this.remove = false;

  this.matrix = new Matrix();

  this.matrix.setRotation(2*Math.PI*this.angle);

  this.draw_coords  = [];
  this.draw_coords1 = [];

  this.coll_coords  = [];
  this.coll_coords1 = [];

  this.bbox = new BBox();

  this.color = new Color(1.0, 1.0, 1.0, 1.0);

  this.objType = ObjectType.NONE;
}

AsteroidsObject.prototype.setDrawCoords = function(draw_coords) {
  var num_draw_coords = draw_coords.length;

  this.draw_coords .length = num_draw_coords;
  this.draw_coords1.length = num_draw_coords;

  for (var i = 0; i < num_draw_coords; ++i)
    this.draw_coords[i] = draw_coords[i];

  this.updateDrawCoords();
};

AsteroidsObject.prototype.setCollisionCoords = function(coll_coords) {
  var num_coll_coords = coll_coords.length;

  this.coll_coords .length = num_coll_coords;
  this.coll_coords1.length = num_coll_coords;

  for (var i = 0; i < num_coll_coords; ++i)
    this.coll_coords[i] = coll_coords[i];

  this.updateCollisionCoords();
};

AsteroidsObject.prototype.move = function() {
  this.v.x += this.a.x;
  this.v.y += this.a.y;

  this.p.x += this.v.x;
  this.p.y += this.v.y;

  this.angle += this.da;

  if (this.wrapOnEdge) {
    if (this.p.x > 1.0) this.p.x = 0.0;
    if (this.p.x < 0.0) this.p.x = 1.0;
    if (this.p.y > 1.0) this.p.y = 0.0;
    if (this.p.y < 0.0) this.p.y = 1.0;
  }
  else {
    if (this.p.x > 1.0) this.removeLater();
    if (this.p.x < 0.0) this.removeLater();
    if (this.p.y > 1.0) this.removeLater();
    if (this.p.y < 0.0) this.removeLater();
  }

  if (this.angle < 0.0) this.angle += 1.0;
  if (this.angle > 1.0) this.angle -= 1.0;

  this.matrix.setRotation(2*Math.PI*this.angle);

  this.updateDrawCoords     ();
  this.updateCollisionCoords();
};

AsteroidsObject.prototype.updateDrawCoords = function() {
  for (var i = 0; i < this.draw_coords.length; ++i) {
    var x = this.draw_coords[i].x*this.size;
    var y = this.draw_coords[i].y*this.size;

    this.draw_coords1[i] = this.matrix.multiplyPoint(new Point(x, y));

    this.draw_coords1[i].x += this.p.x;
    this.draw_coords1[i].y += this.p.y;
  }

  this.bbox.reset();

  for (var i = 0; i < this.draw_coords.length; ++i)
    this.bbox.add(this.draw_coords1[i]);
};

AsteroidsObject.prototype.updateCollisionCoords = function() {
  for (var i = 0; i < this.coll_coords.length; ++i) {
    var x = this.coll_coords[i].x*this.size;
    var y = this.coll_coords[i].y*this.size;

    this.coll_coords1[i] = this.matrix.multiplyPoint(new Point(x, y));

    this.coll_coords1[i].x += this.p.x;
    this.coll_coords1[i].y += this.p.y;
  }
};

AsteroidsObject.prototype.pointInside = function(p) {
  if (! this.bbox.inside(p))
    return false;

  // TODO: use algroithm directly
  var poly = new Polygon(this.coll_coords1);

  return poly.inside(p);
};

AsteroidsObject.prototype.intersect = function() {
  // NOOP
};

AsteroidsObject.prototype.intersectObj = function(obj) {
  var ipoints = [];

  if (! AsteroidsObject.prototype.intersectPolygons.
          call(this, this.coll_coords1, obj.coll_coords1, ipoints))
    return false;

  return true;
};

AsteroidsObject.prototype.polygonOrientation = function(points) {
  var dx1 = points[1].x - points[0].x;
  var dy1 = points[1].y - points[0].y;

  var dx2 = points[2].x - points[1].x;
  var dy2 = points[2].y - points[1].y;

  return Math.sign(dx1*dy2 - dy1*dx2);
};

AsteroidsObject.prototype.intersectPolygons = function(points1, points2, ipoints) {
  asteroids.objectMgr.poly_f[0] = [];
  asteroids.objectMgr.poly_f[1] = [];

  ipoints = [];

  var num_points1 = points1.length;
  var num_points2 = points2.length;

  // fail if polygons are degenerate
  if (num_points1 < 3 || num_points2 < 3)
    return false;

  var orient1 = AsteroidsObject.prototype.polygonOrientation.call(this, points1);
  var orient2 = AsteroidsObject.prototype.polygonOrientation.call(this, points2);

  // max number of intersection
  var ni = num_points1*num_points2;

  // make sure intersection buffer is large enough
  while (asteroids.objectMgr.poly_num_f < ni) {
    asteroids.objectMgr.poly_f[0][asteroids.objectMgr.poly_num_f] = new Point(0.0, 0.0);
    asteroids.objectMgr.poly_f[1][asteroids.objectMgr.poly_num_f] = new Point(0.0, 0.0);

    ++asteroids.objectMgr.poly_num_f;
  }

  // store polygon one in start point array
  // Note: if orients don't match we invert the first polygon's point order
  var l1 = 0;

  ni = num_points1;

  if (orient1 === orient2) {
    for (var i = 0; i < ni; ++i)
      asteroids.objectMgr.poly_f[l1][i] = points1[i];
  }
  else {
    for (var i = 0, j = ni - 1; i < ni; ++i, --j)
      asteroids.objectMgr.poly_f[l1][i] = points1[j];
  }

  // intersect current set of points with each line (end1, end2)
  // of the second polygon (points2)
  var end1 = points2[num_points2 - 1];

  for (var i = 0; i < num_points2; ++i) {
    var end2 = points2[i];

    // l2 is destination point index (inverse of current l1)
    var l2 = 1 - l1;

    // calc line coefficients
    var ca = end2.x - end1.x; // (x2 - x1), (y2 - y1)
    var cb = end1.y - end2.y; // (x2 - x1), (y2 - y1)
    var cc = -end1.x*cb - end1.y*ca; // -x1*(y2 - y1) - y1*(x2 - x1)

    // calc side of line for first point
    var v1     = asteroids.objectMgr.poly_f[l1][ni - 1];
    var fv1    = ca*v1.y + cb*v1.x + cc;
    var absfv1 = Math.abs(fv1);

    var index1 = 0;

    if (absfv1 >= 1E-6)
      index1 = Math.sign(fv1)*orient2;

    var ni1 = 0;

    for (var j = 0; j < ni; ++j) {
      // calc side of line for second point
      var v2     = asteroids.objectMgr.poly_f[l1][j];
      var fv2    = ca*v2.y + cb*v2.x + cc;
      var absfv2 = Math.abs(fv2);

      var index2 = 0;

      if (absfv2 >= 1E-6)
        index2 = Math.sign(fv2)*orient2;

      // add start point
      if (index1 >= 0)
        asteroids.objectMgr.poly_f[l2][ni1++] = v1;

      // add intersection point (if changed sides)
      if (index1 !== 0 && index1 !== index2 && index2 !== 0) {
        var delta = absfv1 + absfv2;

        var xi = (absfv2*v1.x + absfv1*v2.x)/delta;
        var yi = (absfv2*v1.y + absfv1*v2.y)/delta;

        asteroids.objectMgr.poly_f[l2][ni1++] = new Point(xi, yi);
      }

      // move to next line
      v1     = v2;
      absfv1 = absfv2;
      index1 = index2;
    }

    // degenerate result so fail
    if (ni1 < 3)
      return false;

    l1   = l2;
    end1 = end2;
    ni   = ni1;
  }

  ipoints = [];

  for (var i = 0; i < ni; ++i)
    ipoints[i] = asteroids.objectMgr.poly_f[l1][i];

  return true;
};

AsteroidsObject.prototype.draw = function() {
  if (this.remove) return;

  if (asteroids.colored)
    asteroids.setColor(this.getColor());

  if (asteroids.filled)
    asteroids.fillPolygon(this.draw_coords1);
  else
    asteroids.drawPolygon(this.draw_coords1);

/*
  asteroids.drawPolygon(this.coll_coords1);
*/

/*
  var x1 = this.bbox.xmin; var y1 = this.bbox.ymin;
  var x2 = this.bbox.xmax; var y2 = this.bbox.ymax;

  asteroids.drawLine(new Point(x1, y1), new Point(x2, y1));
  asteroids.drawLine(new Point(x2, y1), new Point(x2, y2));
  asteroids.drawLine(new Point(x2, y2), new Point(x1, y2));
  asteroids.drawLine(new Point(x1, y2), new Point(x1, y1));
*/
};

AsteroidsObject.prototype.hit = function() {
  this.removeLater();

  asteroids.addScore(this.score);
};

AsteroidsObject.prototype.removeLater = function() {
  this.remove = true;
};

AsteroidsObject.prototype.destroy = function() {
  // NO OP
};

AsteroidsObject.prototype.getColor = function() {
  return this.color;
};

//------

function AsteroidsScore () {
  this.score = 0;
  this.size  = 0.03;
  this.lives = 3;
}

AsteroidsScore.prototype.reset = function() {
  this.score = 0;
  this.size  = 0.03;
  this.lives = 3;
};

AsteroidsScore.prototype.add = function(score) {
  this.score += score;
};

AsteroidsScore.prototype.die = function() {
  if (this.lives > 0)
    --this.lives;
};

AsteroidsScore.prototype.draw = function() {
  var str = String(this.score);

  while (str.length < 5)
    str = "0" + str;

  var x = 0.01;
  var y = 0.96;

  var len = str.length;

  for (var i = 0; i < len; i++) {
    asteroids.drawChar(new Point(x, y), this.size, str[i]);

    x += this.size;
  }

  x = 0.99 - this.size;
  y = 0.96;

  for (var i = 0; i < this.lives; ++i) {
    asteroids.drawChar(new Point(x, y), this.size, 'A');

    x -= this.size;
  }
};

//------

function AsteroidsShapeMgr () {
}

AsteroidsShapeMgr.prototype.drawPoints = function(type) {
  if      (type === ShapeType.SHIP) {
    this.ship_points = [
      new Point( 0.5,  0.0),
      new Point(-0.5,  0.5),
      new Point(-0.3,  0.0),
      new Point(-0.5, -0.5)
    ];

    return this.ship_points;
  }
  else if (type === ShapeType.SHIP_THRUST) {
    this.ship_thrust_points = [
      new Point( 0.500,  0.000),
      new Point(-0.500,  0.500),
      new Point(-0.375,  0.125),
      new Point(-0.675,  0.025),
      new Point(-0.375, -0.150),
      new Point(-0.500, -0.500)
    ];

    return this.ship_thrust_points;
  }
  else if (type === ShapeType.ROCK1) {
    this.rock_points1 = [
      new Point(-0.100, -0.475),
      new Point( 0.325, -0.500),
      new Point( 0.500, -0.250),
      new Point( 0.450,  0.225),
      new Point( 0.250,  0.500),
      new Point(-0.250,  0.425),
      new Point(-0.300,  0.225),
      new Point(-0.475,  0.200),
      new Point(-0.475, -0.075),
      new Point(-0.250, -0.150),
      new Point(-0.325, -0.325)
    ];

    return this.rock_points1;
  }
  else if (type === ShapeType.ROCK2) {
    this.rock_points2 = [
      new Point(-0.125, -0.500),
      new Point( 0.325, -0.450),
      new Point( 0.500, -0.250),
      new Point( 0.425,  0.175),
      new Point( 0.225,  0.450),
      new Point(-0.250,  0.500),
      new Point(-0.300,  0.250),
      new Point(-0.450,  0.200),
      new Point(-0.500, -0.125),
      new Point(-0.300, -0.175),
      new Point(-0.350, -0.300)
    ];

    return this.rock_points2;
  }
  else if (type === ShapeType.ROCK3) {
    this.rock_points3 = [
      new Point(-0.25, -0.500),
      new Point( 0.10, -0.450),
      new Point( 0.25, -0.275),
      new Point( 0.45, -0.275),
      new Point( 0.50,  0.050),
      new Point( 0.30,  0.150),
      new Point( 0.20,  0.450),
      new Point(-0.15,  0.500),
      new Point(-0.25,  0.175),
      new Point(-0.45,  0.100),
      new Point(-0.50, -0.250),
      new Point(-0.30, -0.300)
    ];

    return this.rock_points3;
  }
  else if (type === ShapeType.SMALL_SAUCER) {
    this.small_saucer_points = [
      new Point( 0.50,  0.000),
      new Point( 0.45,  0.125),
      new Point( 0.25,  0.250),
      new Point(-0.25,  0.250),
      new Point(-0.45,  0.125),
      new Point(-0.50,  0.000),
      new Point(-0.25, -0.150),
      new Point(-0.25, -0.250),
      new Point( 0.25, -0.250),
      new Point( 0.25, -0.150)
    ];

    return this.small_saucer_points;
  }
  else if (type === ShapeType.BIG_SAUCER) {
    this.big_saucer_points = [
      new Point( 0.500,  0.000),
      new Point( 0.325,  0.100),
      new Point( 0.200,  0.100),
      new Point( 0.100,  0.250),
      new Point(-0.100,  0.250),
      new Point(-0.175,  0.100),
      new Point(-0.325,  0.100),
      new Point(-0.500,  0.000),
      new Point(-0.500, -0.075),
      new Point(-0.250, -0.250),
      new Point( 0.250, -0.250),
      new Point( 0.500, -0.075)
    ];

    return this.big_saucer_points;
  }
  else if (type === ShapeType.BULLET) {
    this.bullet_points = [
      new Point( 0.000, -0.100),
      new Point( 0.025, -0.025),
      new Point( 0.100,  0.000),
      new Point( 0.025,  0.025),
      new Point( 0.000,  0.100),
      new Point(-0.025,  0.025),
      new Point(-0.100,  0.000),
      new Point(-0.025, -0.025)
    ];

    return this.bullet_points;
  }
  else {
    assert(false);
    return [];
  }
};

AsteroidsShapeMgr.prototype.collisionPoints = function(type) {
  if      (type === ShapeType.SHIP) {
    this.ship_points = [
      new Point( 0.5,  0.0),
      new Point(-0.5,  0.5),
      new Point(-0.3,  0.0),
      new Point(-0.5, -0.5)
    ];

    return this.ship_points;
  }
  else if (type === ShapeType.SHIP_THRUST) {
    this.ship_thrust_points = [
      new Point( 0.5,  0.0),
      new Point(-0.5,  0.5),
      new Point(-0.3,  0.0),
      new Point(-0.5, -0.5)
    ];

    return this.ship_thrust_points;
  }
  else if (type === ShapeType.ROCK1) {
    this.rock_points1 = [
      new Point( 0.5, -0.5),
      new Point( 0.5,  0.5),
      new Point(-0.5,  0.5),
      new Point(-0.5, -0.5)
    ];

    return this.rock_points1;
  }
  else if (type === ShapeType.ROCK2) {
    this.rock_points2 = [
      new Point( 0.5, -0.5),
      new Point( 0.5,  0.5),
      new Point(-0.5,  0.5),
      new Point(-0.5, -0.5)
    ];

    return this.rock_points2;
  }
  else if (type === ShapeType.ROCK3) {
    this.rock_points3 = [
      new Point( 0.5, -0.5),
      new Point( 0.5,  0.5),
      new Point(-0.5,  0.5),
      new Point(-0.5, -0.5)
    ];

    return this.rock_points3;
  }
  else if (type === ShapeType.SMALL_SAUCER) {
    this.small_saucer_points = [
      new Point( 0.5, -0.25),
      new Point( 0.5,  0.25),
      new Point(-0.5,  0.25),
      new Point(-0.5, -0.25)
    ];

    return this.small_saucer_points;
  }
  else if (type === ShapeType.BIG_SAUCER) {
    this.big_saucer_points = [
      new Point( 0.5, -0.25),
      new Point( 0.5,  0.25),
      new Point(-0.5,  0.25),
      new Point(-0.5, -0.25)
    ];

    return this.big_saucer_points;
  }
  else if (type === ShapeType.BULLET) {
    this.bullet_points = [
      new Point( 0.0, -0.1),
      new Point( 0.1,  0.0),
      new Point( 0.0,  0.1),
      new Point(-0.1,  0.0)
    ];

    return this.bullet_points;
  }
  else {
    assert(false);
    return [];
  }
};

AsteroidsShapeMgr.prototype.typeName = function(type) {
  switch (type) {
    case ShapeType.SHIP        : return "Ship";
    case ShapeType.SHIP_THRUST : return "Ship_Thrust";
    case ShapeType.ROCK1       : return "Rock1";
    case ShapeType.ROCK2       : return "Rock2";
    case ShapeType.ROCK3       : return "Rock3";
    case ShapeType.SMALL_SAUCER: return "Small_Saucer";
    case ShapeType.BIG_SAUCER  : return "Big_Saucer";
    case ShapeType.BULLET      : return "Bullet";
    default                    : return "None";
  }
};
