#ifndef CBBOX_2D_H
#define CBBOX_2D_H

#include "CPoint2D.h"

template<typename T>
class CBBox2DT {
 private:
  typedef CPoint2DT<T> Point;
  typedef CBBox2DT<T>  BBox;

 private:
  Point pmin_;
  Point pmax_;
  bool  set_;

 public:
  CBBox2DT() :
   pmin_(), pmax_(), set_(false) {
  }

  CBBox2DT(const BBox &bbox) :
   pmin_(bbox.pmin_), pmax_(bbox.pmax_), set_(bbox.set_) {
  }

  CBBox2DT(const Point &point) :
   pmin_(point), pmax_(point), set_(true) {
  }

  CBBox2DT(const Point &point1, const Point &point2) :
   pmin_(), pmax_(), set_(true) {
    pmin_.x = std::min(point1.x, point2.x);
    pmin_.y = std::min(point1.y, point2.y);
    pmax_.x = std::max(point1.x, point2.x);
    pmax_.y = std::max(point1.y, point2.y);
  }

  CBBox2DT(T x1, T y1, T x2, T y2) :
   pmin_(), pmax_(), set_(true) {
    pmin_.x = std::min(x1, x2);
    pmin_.y = std::min(y1, y2);
    pmax_.x = std::max(x1, x2);
    pmax_.y = std::max(y1, y2);
  }

  void reset() { set_ = false; }

  bool isSet() const { return set_; }

  BBox operator+(const Point &rhs) const {
    BBox t(*this);

    t += rhs;

    return t;
  }

  BBox &operator+=(const Point &rhs) {
    add(rhs.x, rhs.y);

    return *this;
  }

  BBox operator+(const BBox &rhs) const {
    BBox t(*this);

    t += rhs;

    return t;
  }

  BBox &operator+=(const BBox &rhs) {
    add(rhs);

    return *this;
  }

  void add(const Point &point) {
    add(point.x, point.y);
  }

  void add(T x, T y) {
    if (! set_) {
      pmin_ = CPoint2D(x, y);
      pmax_ = pmin_;

      set_ = true;
    }
    else {
      pmin_.x = std::min(pmin_.x, x);
      pmin_.y = std::min(pmin_.y, y);
      pmax_.x = std::max(pmax_.x, x);
      pmax_.y = std::max(pmax_.y, y);
    }
  }

  void add(const BBox &bbox) {
    if (! bbox.set_) return;

    if (! set_) {
      pmin_ = bbox.pmin_;
      pmax_ = bbox.pmax_;

      set_ = true;
    }
    else {
      pmin_.x = std::min(pmin_.x, bbox.pmin_.x);
      pmin_.y = std::min(pmin_.y, bbox.pmin_.y);
      pmax_.x = std::max(pmax_.x, bbox.pmax_.x);
      pmax_.y = std::max(pmax_.y, bbox.pmax_.y);
    }
  }

  bool overlaps(const BBox &bbox) const {
    if (! set_ || ! bbox.set_) return false;

    return ((pmax_.x >= bbox.pmin_.x && pmin_.x <= bbox.pmax_.x) &&
            (pmax_.y >= bbox.pmin_.y && pmin_.y <= bbox.pmax_.y));
  }

  bool inside(T x, T y) const {
    if (! set_) return false;

    return ((x >= pmin_.x && x <= pmax_.x) &&
            (y >= pmin_.y && y <= pmax_.y));
  }

  bool inside(const Point &point) const {
    if (! set_) return false;

    return ((point.x >= pmin_.x && point.x <= pmax_.x) &&
            (point.y >= pmin_.y && point.y <= pmax_.y));
  }

  bool inside(const BBox &bbox) const {
    if (! set_) return false;

    return ((bbox.pmin_.x >= pmin_.x && bbox.pmax_.x <= pmax_.x) &&
            (bbox.pmin_.y >= pmin_.y && bbox.pmax_.y <= pmax_.y));
  }

  void expand(T delta) {
    if (! set_) return;

    pmin_ += delta;
    pmax_ += delta;
  }

  void expand(T x1, T y1, T x2, T y2) {
    if (! set_) return;

    pmin_.x += x1;
    pmin_.y += y1;
    pmax_.x += x2;
    pmax_.y += y2;

    update();
  }

  T area() const {
    if (! set_) return 0.0;

    T dx = fabs(pmax_.x - pmin_.x);
    T dy = fabs(pmax_.y - pmin_.y);

    return dx*dy;
  }

  Point getMin() const { return set_ ? pmin_ : Point(0,0); }
  Point getMax() const { return set_ ? pmax_ : Point(0,0); }

  T getXMin() const { return set_ ? pmin_.x : 0.0; }
  T getYMin() const { return set_ ? pmin_.y : 0.0; }
  T getXMax() const { return set_ ? pmax_.x : 0.0; }
  T getYMax() const { return set_ ? pmax_.y : 0.0; }

  T getXMid() const { return set_ ? (pmin_.x + pmax_.x)/2 : 0.0; }
  T getYMid() const { return set_ ? (pmin_.y + pmax_.y)/2 : 0.0; }

  Point getCenter() const {
    return 0.5*(getMin() + getMax());
  }

  void setLL(const Point &point) {
    pmin_ = point;

    if (! set_) {
      pmax_ = point;
      set_  = true;
    }
  }

  void setUR(const Point &point) {
    pmax_ = point;

    if (! set_) {
      pmin_ = point;
      set_  = true;
    }
  }

  void setX(T x) {
    pmin_.x = x;
    set_    = true;
  }

  void setY(T y) {
    pmin_.y = y;
    set_    = true;
  }

  void setWidth(T width) {
    pmax_.x = pmin_.x + width;
    set_    = true;
  }

  void setHeight(T height) {
    pmax_.y = pmin_.y + height;
    set_    = true;
  }

  void setXMin(T x) {
    pmin_.x = x;
    set_    = true;
  }

  void setYMin(T y) {
    pmin_.y = y;
    set_    = true;
  }

  void setXMax(T x) {
    pmax_.x = x;
    set_    = true;
  }

  void setYMax(T y) {
    pmax_.y = y;
    set_    = true;
  }

  Point getLL() const {
    return pmin_;
  }

  Point getLR() const {
    return Point(pmax_.x, pmin_.y);
  }

  Point getUL() const {
    return Point(pmin_.x, pmax_.y);
  }

  Point getUR() const {
    return pmax_;
  }

  T getWidth() const {
    return fabs(getXMax() - getXMin());
  }

  T getHeight() const {
    return fabs(getYMax() - getYMin());
  }

  void moveBy(const Point &delta) {
    pmin_ += delta;
    pmax_ += delta;
  }

  void print(std::ostream &os) const {
    if (! set_)
      os << "( not set )";
    else
      os << "(" << pmin_ << ") (" << pmax_ << ")";
  }

  friend std::ostream &operator<<(std::ostream &os, const BBox &bbox) {
    bbox.print(os);

    return os;
  }

 private:
  void update() {
    if (pmin_.x > pmax_.x) std::swap(pmin_.x, pmax_.x);
    if (pmin_.y > pmax_.y) std::swap(pmin_.y, pmax_.y);
  }
};

typedef CBBox2DT<double> CBBox2D;

#endif
