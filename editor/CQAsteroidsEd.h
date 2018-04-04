#ifndef CQAsteroidsEd_H
#define CQAsteroidsEd_H

#include <CAsteroidsShapeMgr.h>
#include <CQMainWindow.h>
#include <CDisplayRange2D.h>
#include <CLine2D.h>

#include <QWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QPainterPath>

class Application;
class CAsteroids;
class CFile;
class QLabel;

class Canvas : public QWidget {
  Q_OBJECT

 public:
  Canvas(Application *app, const std::string &name);

  const CDisplayRange2D &range() const { return range_; }

 private:
  void paintEvent(QPaintEvent *);

  void resizeEvent(QResizeEvent *);

  void keyPressEvent(QKeyEvent *);

  void mousePressEvent(QMouseEvent *e);
  void mouseMoveEvent(QMouseEvent *e);
  void mouseReleaseEvent(QMouseEvent *e);

 private:
  Application*     app_ { nullptr };
  CDisplayRange2D  range_;
};

//---

class Application : public CQMainWindow {
  Q_OBJECT

 public:
  enum class State {
    NONE,
    MOVE,
    ADD,
    DELETE
  };

  enum class MoveType {
    NONE,
    TO,
    BY
  };

  enum class PointsType {
    NONE,
    DRAW,
    COLLISION
  };

 private:
  class ShapeData;

 public:
  Application(const std::string &name);

  double lineWidth() const { return lineWidth_; }
  void setLineWidth(double r) { lineWidth_ = r; }

  const PointsType &pointsType() const { return pointsType_; }
  void setPointsType(const PointsType &t);

  void createMenus();

  QWidget *createCentralWidget();

  void createStatusBar();

  void draw(QPainter *painter);

  void drawShape(QPainter *painter, const ShapeData &shape);

  void drawSelected(QPainter *painter);

  void drawPreviewPoint(QPainter *painter);

  void drawCrossPoint(QPainter *painter, const CPoint2D &p, const QColor &c);

  void mousePress  (const CPoint2D &p);
  void mouseMove   (const CPoint2D &p);
  void mouseRelease(const CPoint2D &p);

  void selectAt(const CPoint2D &p);

  void escape();

  void nextShape();
  void prevShape();

  void moveTo(const CPoint2D &p);
  void moveBy(const CPoint2D &p);

  void move(const MoveType &moveType, const CPoint2D &p);

  void deleteSelected();

  int nearestPoint(const CPoint2D &p) const;
  int nearestLine(const CPoint2D &p) const;

  CPoint2D pointDataPos(int pointData) const;

  CPoint2D snapPoint(const CPoint2D &p) const;

  double delta() const { return delta_; }

  QSize sizeHint() const { return QSize(1200, 1200); }

 public slots:
  void print();
  void printAll();

  void increaseLineWidth();
  void decreaseLineWidth();

  void moveStateSlot();
  void addStateSlot();
  void deleteStateSlot();

  void drawPointsSlot();
  void collisionPointsSlot();

  void resetPoints();

 private slots:
  void updateAll();

  void updateState();

 private:
  void printShape(CFile &file, const ShapeData &shape);

 private:
  struct MouseState {
    bool     pressed { false };
    bool     moving { false };
    bool     escape { false };
    CPoint2D pressPoint;
    CPoint2D movePoint;
    CPoint2D releasePoint;
  };

  class ShapeData {
   public:
    using Type   = CAsteroidsShapeMgr::Type;
    using Points = CAsteroidsShapeMgr::Points;

   public:
    ShapeData() = default;

    const Type &type() const { return type_; }

    void setType(const Type &t) {
      type_ = t;

      resetPoints();
    }

    void resetPoints() {
      drawPoints_      = CAsteroidsShapeMgrInst->drawPoints     (type_);
      collisionPoints_ = CAsteroidsShapeMgrInst->collisionPoints(type_);
    }

    //---

    const Points &drawPoints() const { return drawPoints_; }
    Points &drawPoints() { return drawPoints_; }

    std::size_t numDrawPoints() const { return drawPoints_.size(); }

    const CPoint2D &drawPoint(int i) const {
      assert(i >= 0 && i < int(drawPoints_.size()));

      return drawPoints_[i];
    }

    void setDrawPoint(int i, const CPoint2D &p) {
      assert(i >= 0 && i < int(drawPoints_.size()));

      drawPoints_[i] = p;

      CAsteroidsShapeMgrInst->setDrawPoints(type_, drawPoints_);
    }

    void addDrawPoint(int i, const CPoint2D &p) {
      int np = numDrawPoints();

      drawPoints_.push_back(p);

      for (int i1 = np - 1; i1 >= i + 1; --i1)
        drawPoints_[i1 + 1] = drawPoints_[i1];

      drawPoints_[i + 1] = p;

      CAsteroidsShapeMgrInst->setDrawPoints(type_, drawPoints_);
    }

    void removeDrawPoint(int i) {
      int np = numDrawPoints();

      for (int i1 = i + 1; i1 < np; ++i1)
        drawPoints_[i1 - 1] = drawPoints_[i1];

      drawPoints_.pop_back();

      CAsteroidsShapeMgrInst->setDrawPoints(type_, drawPoints_);
    }

    //---

    const Points &collisionPoints() const { return collisionPoints_; }
    Points &collisionPoints() { return collisionPoints_; }

    std::size_t numCollisionPoints() const { return collisionPoints_.size(); }

    const CPoint2D &collisionPoint(int i) const {
      assert(i >= 0 && i < int(collisionPoints_.size()));

      return collisionPoints_[i];
    }

    void setCollisionPoint(int i, const CPoint2D &p) {
      assert(i >= 0 && i < int(collisionPoints_.size()));

      collisionPoints_[i] = p;

      CAsteroidsShapeMgrInst->setCollisionPoints(type_, collisionPoints_);
    }

    void addCollisionPoint(int i, const CPoint2D &p) {
      int np = numCollisionPoints();

      collisionPoints_.push_back(p);

      for (int i1 = np - 1; i1 >= i + 1; --i1)
        collisionPoints_[i1 + 1] = collisionPoints_[i1];

      collisionPoints_[i + 1] = p;

      CAsteroidsShapeMgrInst->setCollisionPoints(type_, collisionPoints_);
    }

    void removeCollisionPoint(int i) {
      int np = numCollisionPoints();

      for (int i1 = i + 1; i1 < np; ++i1)
        collisionPoints_[i1 - 1] = collisionPoints_[i1];

      collisionPoints_.pop_back();

      CAsteroidsShapeMgrInst->setCollisionPoints(type_, collisionPoints_);
    }

    //---

   public:
    Type   type_            { Type::SHIP };
    Points drawPoints_;
    Points collisionPoints_;
  };

  CAsteroids* asteroids_     { nullptr };
  ShapeData   shapeData_;
  State       state_         { State::MOVE };
  PointsType  pointsType_    { PointsType::DRAW };
  Canvas*     canvas_        { nullptr };
  QLabel*     stateLabel_    { nullptr };
  QLabel*     posLabel_      { nullptr };
  int         selectedPoint_ { -1 };
  int         previewPoint_  { -1 };
  int         previewLine_   { -1 };
  CPoint2D    selectPoint_;
  MouseState  mouseState_;
  bool        moving_        { false };
  int         lineWidth_     { 1 };
  double      delta_         { 0.025 };
};

#endif
