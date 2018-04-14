#include <CAsteroidsShapeMgr.h>

CAsteroidsShapeMgr::
CAsteroidsShapeMgr(const CAsteroids &app) :
 app_(app)
{
}

CAsteroidsShapeMgr::Points
CAsteroidsShapeMgr::
drawPoints(Type type)
{
  auto p = drawTypePoints_.find(type);

  if (p != drawTypePoints_.end())
    return (*p).second;

  //---

  if      (type == Type::SHIP) {
    static Points ship_points = {
      CPoint2D( 0.5,  0.0),
      CPoint2D(-0.5,  0.5),
      CPoint2D(-0.3,  0.0),
      CPoint2D(-0.5, -0.5)
    };

    return ship_points;
  }
  else if (type == Type::SHIP_THRUST) {
    static Points ship_thrust_points = {
      CPoint2D( 0.500,  0.000),
      CPoint2D(-0.500,  0.500),
      CPoint2D(-0.375,  0.125),
      CPoint2D(-0.675,  0.025),
      CPoint2D(-0.375, -0.150),
      CPoint2D(-0.500, -0.500)
    };

    return ship_thrust_points;
  }
  else if (type == Type::ROCK1) {
    static Points rock_points1 = {
      CPoint2D(-0.100, -0.475),
      CPoint2D( 0.325, -0.500),
      CPoint2D( 0.500, -0.250),
      CPoint2D( 0.450,  0.225),
      CPoint2D( 0.250,  0.500),
      CPoint2D(-0.250,  0.425),
      CPoint2D(-0.300,  0.225),
      CPoint2D(-0.475,  0.200),
      CPoint2D(-0.475, -0.075),
      CPoint2D(-0.250, -0.150),
      CPoint2D(-0.325, -0.325)
    };

    return rock_points1;
  }
  else if (type == Type::ROCK2) {
    static Points rock_points2 = {
      CPoint2D(-0.125, -0.500),
      CPoint2D( 0.325, -0.450),
      CPoint2D( 0.500, -0.250),
      CPoint2D( 0.425,  0.175),
      CPoint2D( 0.225,  0.450),
      CPoint2D(-0.250,  0.500),
      CPoint2D(-0.300,  0.250),
      CPoint2D(-0.450,  0.200),
      CPoint2D(-0.500, -0.125),
      CPoint2D(-0.300, -0.175),
      CPoint2D(-0.350, -0.300)
    };

    return rock_points2;
  }
  else if (type == Type::ROCK3) {
    static Points rock_points3 = {
      CPoint2D(-0.25, -0.500),
      CPoint2D( 0.10, -0.450),
      CPoint2D( 0.25, -0.275),
      CPoint2D( 0.45, -0.275),
      CPoint2D( 0.50,  0.050),
      CPoint2D( 0.30,  0.150),
      CPoint2D( 0.20,  0.450),
      CPoint2D(-0.15,  0.500),
      CPoint2D(-0.25,  0.175),
      CPoint2D(-0.45,  0.100),
      CPoint2D(-0.50, -0.250),
      CPoint2D(-0.30, -0.300)
    };

    return rock_points3;
  }
  else if (type == Type::SMALL_SAUCER) {
    static Points small_saucer_points = {
      CPoint2D( 0.50,  0.000),
      CPoint2D( 0.45,  0.125),
      CPoint2D( 0.25,  0.250),
      CPoint2D(-0.25,  0.250),
      CPoint2D(-0.45,  0.125),
      CPoint2D(-0.50,  0.000),
      CPoint2D(-0.25, -0.150),
      CPoint2D(-0.25, -0.250),
      CPoint2D( 0.25, -0.250),
      CPoint2D( 0.25, -0.150)
    };

    return small_saucer_points;
  }
  else if (type == Type::BIG_SAUCER) {
    static Points big_saucer_points = {
      CPoint2D( 0.500,  0.000),
      CPoint2D( 0.325,  0.100),
      CPoint2D( 0.200,  0.100),
      CPoint2D( 0.100,  0.250),
      CPoint2D(-0.100,  0.250),
      CPoint2D(-0.175,  0.100),
      CPoint2D(-0.325,  0.100),
      CPoint2D(-0.500,  0.000),
      CPoint2D(-0.500, -0.075),
      CPoint2D(-0.250, -0.250),
      CPoint2D( 0.250, -0.250),
      CPoint2D( 0.500, -0.075)
    };

    return big_saucer_points;
  }
  else if (type == Type::BULLET) {
    static Points bullet_points = {
      CPoint2D( 0.000, -0.100),
      CPoint2D( 0.025, -0.025),
      CPoint2D( 0.100,  0.000),
      CPoint2D( 0.025,  0.025),
      CPoint2D( 0.000,  0.100),
      CPoint2D(-0.025,  0.025),
      CPoint2D(-0.100,  0.000),
      CPoint2D(-0.025, -0.025)
    };

    return bullet_points;
  }
  else {
    return Points();
  }
}

CAsteroidsShapeMgr::Points
CAsteroidsShapeMgr::
collisionPoints(Type type)
{
  auto p = collisionTypePoints_.find(type);

  if (p != collisionTypePoints_.end())
    return (*p).second;

  //---

  if      (type == Type::SHIP) {
    static Points ship_points = {
      CPoint2D( 0.5,  0.0),
      CPoint2D(-0.5,  0.5),
      CPoint2D(-0.3,  0.0),
      CPoint2D(-0.5, -0.5)
    };

    return ship_points;
  }
  else if (type == Type::SHIP_THRUST) {
    static Points ship_thrust_points = {
      CPoint2D( 0.5,  0.0),
      CPoint2D(-0.5,  0.5),
      CPoint2D(-0.3,  0.0),
      CPoint2D(-0.5, -0.5)
    };

    return ship_thrust_points;
  }
  else if (type == Type::ROCK1) {
    static Points rock_points1 = {
      CPoint2D( 0.5, -0.5),
      CPoint2D( 0.5,  0.5),
      CPoint2D(-0.5,  0.5),
      CPoint2D(-0.5, -0.5)
    };

    return rock_points1;
  }
  else if (type == Type::ROCK2) {
    static Points rock_points2 = {
      CPoint2D( 0.5, -0.5),
      CPoint2D( 0.5,  0.5),
      CPoint2D(-0.5,  0.5),
      CPoint2D(-0.5, -0.5)
    };

    return rock_points2;
  }
  else if (type == Type::ROCK3) {
    static Points rock_points3 = {
      CPoint2D( 0.5, -0.5),
      CPoint2D( 0.5,  0.5),
      CPoint2D(-0.5,  0.5),
      CPoint2D(-0.5, -0.5)
    };

    return rock_points3;
  }
  else if (type == Type::SMALL_SAUCER) {
    static Points small_saucer_points = {
      CPoint2D( 0.5, -0.25),
      CPoint2D( 0.5,  0.25),
      CPoint2D(-0.5,  0.25),
      CPoint2D(-0.5, -0.25)
    };

    return small_saucer_points;
  }
  else if (type == Type::BIG_SAUCER) {
    static Points big_saucer_points = {
      CPoint2D( 0.5, -0.25),
      CPoint2D( 0.5,  0.25),
      CPoint2D(-0.5,  0.25),
      CPoint2D(-0.5, -0.25)
    };

    return big_saucer_points;
  }
  else if (type == Type::BULLET) {
    static Points bullet_points = {
      CPoint2D( 0.0, -0.1),
      CPoint2D( 0.1,  0.0),
      CPoint2D( 0.0,  0.1),
      CPoint2D(-0.1,  0.0)
    };

    return bullet_points;
  }
  else {
    return Points();
  }
}

void
CAsteroidsShapeMgr::
setDrawPoints(Type type, const Points &points)
{
  drawTypePoints_[type] = points;
}

void
CAsteroidsShapeMgr::
resetDrawPoints(Type type)
{
  drawTypePoints_.erase(type);
}

void
CAsteroidsShapeMgr::
setCollisionPoints(Type type, const Points &points)
{
  collisionTypePoints_[type] = points;
}

void
CAsteroidsShapeMgr::
resetCollisionPoints(Type type)
{
  collisionTypePoints_.erase(type);
}

std::string
CAsteroidsShapeMgr::
typeName(Type type) const
{
  switch (type) {
    case Type::SHIP        : return "Ship";
    case Type::SHIP_THRUST : return "Ship_Thrust";
    case Type::ROCK1       : return "Rock1";
    case Type::ROCK2       : return "Rock2";
    case Type::ROCK3       : return "Rock3";
    case Type::SMALL_SAUCER: return "Small_Saucer";
    case Type::BIG_SAUCER  : return "Big_Saucer";
    case Type::BULLET      : return "Bullet";
    default                : return "None";
  }
}
