#ifndef CAsteroidsShapeMgr_H
#define CAsteroidsShapeMgr_H

#define CAsteroidsShapeMgrInst CAsteroidsShapeMgr::instance()

#include <CPoint2D.h>
#include <map>
#include <vector>

class CAsteroidsShapeMgr {
 public:
  enum class Type {
    SHIP,
    SHIP_THRUST,
    ROCK1,
    ROCK2,
    ROCK3,
    SMALL_SAUCER,
    BIG_SAUCER,
    BULLET
  };

 public:
  using Points = std::vector<CPoint2D>;

 public:
  static CAsteroidsShapeMgr *instance();

  Points drawPoints(Type type);
  void setDrawPoints(Type type, const Points &points);

  void resetDrawPoints(Type type);

  Points collisionPoints(Type type);
  void setCollisionPoints(Type type, const Points &points);

  void resetCollisionPoints(Type type);

  Type nextType(Type type) {
    if (type == Type::BULLET) return type;

    return (Type)(int(type) + 1);
  }

  Type prevType(Type type) {
    if (type == Type::SHIP) return type;

    return (Type)(int(type) - 1);
  }

  std::string typeName(Type type) const;

 private:
  CAsteroidsShapeMgr();

 private:
  using TypePoints = std::map<Type,Points>;

  TypePoints drawTypePoints_;
  TypePoints collisionTypePoints_;
};

#endif
