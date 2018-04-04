#ifndef CAsteroidsRenderer_H
#define CAsteroidsRenderer_H

#include <CPoint2D.h>
#include <CRGBA.h>
#include <vector>

class CAsteroidsRenderer {
 public:
  using Points = std::vector<CPoint2D>;

 public:
  CAsteroidsRenderer() { }

  virtual ~CAsteroidsRenderer() { }

  virtual void clear(const CRGBA &bg) = 0;

  virtual void setForeground(const CRGBA &rgba) = 0;

  virtual void drawLine(const CPoint2D &p1, const CPoint2D &p2) = 0;

  virtual void drawPolygon(const Points &points);

  virtual void fillPolygon(const Points &points);
};

#endif
