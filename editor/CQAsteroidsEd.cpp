#include <CQAsteroidsEd.h>
#include <CQApp.h>
#include <CQMenu.h>
#include <CQUtil.h>
#include <CAsteroidsLib.h>
#include <QStatusBar>
#include <QLabel>

int
main(int argc, char **argv)
{
  CQApp qapp(argc, argv);

  Application *app = new Application("ed");

  app->init();

  app->show();

  return qapp.exec();
}

Application::
Application(const std::string &name) :
 CQMainWindow()
{
  setObjectName(name.c_str());

  asteroids_ = new CAsteroids(nullptr);

  shapeData_.setType(ShapeData::Type::SHIP);
}

QWidget *
Application::
createCentralWidget()
{
  canvas_ = new Canvas(this, "canvas");

  return canvas_;
}

void
Application::
createStatusBar()
{
  stateLabel_ = new QLabel;
  posLabel_   = new QLabel;

  statusBar()->addPermanentWidget(stateLabel_, 1);
  statusBar()->addPermanentWidget(posLabel_);

  stateLabel_->setText(" ");
  posLabel_  ->setText(" ");

  updateState();
}

void
Application::
setPointsType(const PointsType &t)
{
  pointsType_ = t;

  updateAll();
}

void
Application::
createMenus()
{
  CQMenu *fileMenu = new CQMenu(this, "&File");

  CQMenuItem *quitItem = new CQMenuItem(fileMenu, "&Quit");

  quitItem->setShortcut("Ctrl+Q");
  quitItem->setStatusTip("Quit the application");

  quitItem->connect(this, SLOT(close()));

  CQMenuItem *printItem = new CQMenuItem(fileMenu, "&Print");

  printItem->setShortcut("Ctrl+P");
  printItem->setStatusTip("Print the current shape");
  printItem->connect(this, SLOT(print()));

  CQMenuItem *printAllItem = new CQMenuItem(fileMenu, "&Print All");

  printAllItem->connect(this, SLOT(printAll()));

  CQMenuItem *helpItem = new CQMenuItem(fileMenu, "&Help");

  helpItem->setShortcut("Ctrl+H");
  helpItem->setStatusTip("Help");

  //helpItem->connect(this, SLOT(help()));

  //---

  CQMenu *viewMenu = new CQMenu(this, "&View");

  CQMenuItem *increaseLineWidthItem = new CQMenuItem(viewMenu, "&Increase Line Width");

  increaseLineWidthItem->connect(this, SLOT(increaseLineWidth()));

  CQMenuItem *decreaseLineWidthItem = new CQMenuItem(viewMenu, "&Decrease Line Width");

  decreaseLineWidthItem->connect(this, SLOT(decreaseLineWidth()));

  //---

  CQMenu *editMenu = new CQMenu(this, "&Edit");

  editMenu->startGroup();

  CQMenuItem *moveItem   = new CQMenuItem(editMenu, "&Move"  , CQMenuItem::CHECKED);
  CQMenuItem *addItem    = new CQMenuItem(editMenu, "&Add"   , CQMenuItem::CHECKABLE);
  CQMenuItem *deleteItem = new CQMenuItem(editMenu, "&Delete", CQMenuItem::CHECKABLE);

  editMenu->endGroup();

  moveItem  ->connect(this, SLOT(moveStateSlot  ()));
  addItem   ->connect(this, SLOT(addStateSlot   ()));
  deleteItem->connect(this, SLOT(deleteStateSlot()));

  //---

  editMenu->startGroup();

  CQMenuItem *drawPointsItem      =
    new CQMenuItem(editMenu, "&Draw Points"     , CQMenuItem::CHECKED);
  CQMenuItem *collisionPointsItem =
    new CQMenuItem(editMenu, "&Collision Points", CQMenuItem::CHECKABLE);

  editMenu->endGroup();

  drawPointsItem     ->connect(this, SLOT(drawPointsSlot     ()));
  collisionPointsItem->connect(this, SLOT(collisionPointsSlot()));

  //---

  CQMenuItem *resetPoints = new CQMenuItem(viewMenu, "&Reset Points");

  resetPoints->connect(this, SLOT(resetPoints()));
}

void
Application::
print()
{
  CFile file("/tmp/CQAsteroidsEd.h");

  if (! file.open(CFile::Mode::WRITE))
    return;

  printShape(file, shapeData_);

  file.close();
}

void
Application::
printAll()
{
  CFile file("/tmp/CQAsteroidsEd.h");

  if (! file.open(CFile::Mode::WRITE))
    return;

  printShape(file, shapeData_);

  file.close();
}

void
Application::
printShape(CFile &, const ShapeData &shapeData)
{
  std::cerr << "Points drawPoints[] = {\n";

  int np = shapeData.numDrawPoints();

  for (int i = 0; i < np; ++i) {
    const CPoint2D &p = shapeData.drawPoint(i);

    if (i > 0)
      std::cerr << ",\n";

    std::cerr << "  CPoint2D(" << p.x << ", " << p.y << ")";
  }

  std::cerr << "\n};\n";

  //--

  std::cerr << "Points collisionPoints[] = {\n";

  np = shapeData.numCollisionPoints();

  for (int i = 0; i < np; ++i) {
    const CPoint2D &p = shapeData.collisionPoint(i);

    if (i > 0)
      std::cerr << ",\n";

    std::cerr << "  CPoint2D(" << p.x << ", " << p.y << ")";
  }

  std::cerr << "\n};\n";
}

void
Application::
draw(QPainter *painter)
{
  QPen pen;

  pen.setWidth(1);
  pen.setCosmetic(true);
  pen.setColor(Qt::green);

  painter->setPen(pen);

  double x1 = -1.0;
  double x2 =  1.0;
  double y1 = -1.0;
  double y2 =  1.0;

  // draw border
  painter->drawLine(QPointF(x1, y1), QPointF(x2, y1));
  painter->drawLine(QPointF(x2, y1), QPointF(x2, y2));
  painter->drawLine(QPointF(x2, y2), QPointF(x1, y2));
  painter->drawLine(QPointF(x1, y2), QPointF(x1, y1));

  //---

  // draw grid
  pen.setColor(QColor(40,40,40));

  painter->setPen(pen);

  double dx = delta();
  double dy = delta();

  for (double x = x1 + dx; x <= x2 - dx; x += dx) {
    painter->drawLine(QPointF(x, y1), QPointF(x, y2));
  }

  for (double y = y1 + dy; y <= y2 - dy; y += dy) {
    painter->drawLine(QPointF(x1, y), QPointF(x2, y));
  }

  //---

  drawShape(painter, shapeData_);

  drawPreviewPoint(painter);

  drawSelected(painter);

  //---

  if (state_ == State::ADD && moving_ && ! mouseState_.escape) {
    pen.setColor(Qt::yellow);

    painter->setPen(pen);

    painter->drawLine(CQUtil::toQPoint(mouseState_.pressPoint),
                      CQUtil::toQPoint(mouseState_.movePoint ));
  }
}

void
Application::
drawShape(QPainter *painter, const ShapeData &shapeData)
{
  QPen pen;

  pen.setWidth(lineWidth());
  pen.setCosmetic(true);

  pen.setColor(Qt::white);

  painter->setPen(pen);

  QPainterPath drawPath;

  int i = 0;

  for (const auto &point : shapeData.drawPoints()) {
    if (i == 0)
      drawPath.moveTo(CQUtil::toQPoint(point));
    else
      drawPath.lineTo(CQUtil::toQPoint(point));

    ++i;
  }

  drawPath.closeSubpath();

  painter->strokePath(drawPath, pen);

  //---

  pen.setColor(QColor(255,255,200));

  painter->setPen(pen);

  QPainterPath collisionPath;

  i = 0;

  for (const auto &point : shapeData.collisionPoints()) {
    if (i == 0)
      collisionPath.moveTo(CQUtil::toQPoint(point));
    else
      collisionPath.lineTo(CQUtil::toQPoint(point));

    ++i;
  }

  collisionPath.closeSubpath();

  painter->strokePath(collisionPath, pen);
}

void
Application::
drawSelected(QPainter *painter)
{
  if (selectedPoint_ < 0)
    return;

  CPoint2D p = pointDataPos(selectedPoint_);

  drawCrossPoint(painter, p, Qt::gray);
}

void
Application::
drawPreviewPoint(QPainter *painter)
{
  if      (previewPoint_ >= 0) {
    CPoint2D p = pointDataPos(previewPoint_);

    drawCrossPoint(painter, p, Qt::yellow);
  }
  else if (previewLine_ >= 0) {
    int np = 0;

    if (pointsType() == PointsType::DRAW)
      np = shapeData_.numDrawPoints();
    else
      np = shapeData_.numCollisionPoints();

    CPoint2D p1 = pointDataPos(previewLine_           );
    CPoint2D p2 = pointDataPos((previewLine_ + 1) % np);

    //---

    QPointF qp1 = CQUtil::toQPoint(p1);
    QPointF qp2 = CQUtil::toQPoint(p2);

    QPen pen;

    pen.setWidth(1);
    pen.setCosmetic(true);
    pen.setColor(Qt::yellow);

    painter->setPen(pen);

    painter->drawLine(qp1, qp2);
  }
}

void
Application::
drawCrossPoint(QPainter *painter, const CPoint2D &p, const QColor &c)
{
  QPointF p1 = CQUtil::toQPoint(p);

  QPen pen;

  pen.setWidth(1);
  pen.setCosmetic(true);
  pen.setColor(c);

  painter->setPen(pen);

  double s = 0.02;

  painter->drawLine(p1 - QPointF( s, s), p1 + QPointF( s, s));
  painter->drawLine(p1 - QPointF(-s, s), p1 + QPointF(-s, s));
}

void
Application::
mousePress(const CPoint2D &p)
{
  mouseState_.pressed    = true;
  mouseState_.pressPoint = snapPoint(p);
  mouseState_.moving     = false;
  mouseState_.escape     = false;

  if      (state_ == State::MOVE) {
    selectAt(mouseState_.pressPoint);

    selectPoint_ = pointDataPos(selectedPoint_);
  }
  else if (state_ == State::DELETE) {
    selectAt(mouseState_.pressPoint);

    deleteSelected();
  }
}

void
Application::
mouseMove(const CPoint2D &p)
{
  mouseState_.movePoint = snapPoint(p);

  posLabel_->setText(QString("%1,%2").arg(mouseState_.movePoint.x).arg(mouseState_.movePoint.y));

  if (mouseState_.pressed) {
    mouseState_.moving = true;

    if (mouseState_.escape)
      return;

    if      (state_ == State::MOVE)
      moveTo(p);
    else if (state_ == State::ADD)
      updateAll();
  }
  else {
    previewPoint_ = nearestPoint(mouseState_.movePoint);
    previewLine_  = nearestLine (mouseState_.movePoint);

    updateAll();
  }
}

void
Application::
mouseRelease(const CPoint2D &p)
{
  mouseState_.pressed      = false;
  mouseState_.releasePoint = snapPoint(p);
  mouseState_.moving       = false;
  mouseState_.escape       = false;

  if (state_ == State::ADD) {
    if (mouseState_.escape)
      return;

    if (previewLine_ >= 0) {
      if (pointsType() == PointsType::DRAW)
        shapeData_.addDrawPoint(previewLine_, mouseState_.releasePoint);
      else
        shapeData_.addCollisionPoint(previewLine_, mouseState_.releasePoint);
    }

    selectedPoint_ = -1;

    updateAll();
  }
}

void
Application::
selectAt(const CPoint2D &p)
{
  selectedPoint_ = nearestPoint(p);
std::cerr << pointDataPos(selectedPoint_) << std::endl;

  updateAll();
}

void
Application::
escape()
{
  mouseState_.escape = true;

  if (mouseState_.moving && state_ == State::MOVE)
    moveTo(selectPoint_);
}

void
Application::
nextShape()
{
  shapeData_.setType(CAsteroidsShapeMgrInst->nextType(shapeData_.type()));

  selectedPoint_ = -1;

  updateAll();
}

void
Application::
prevShape()
{
  shapeData_.setType(CAsteroidsShapeMgrInst->prevType(shapeData_.type()));

  selectedPoint_ = -1;

  updateAll();
}

void
Application::
moveTo(const CPoint2D &p)
{
  move(MoveType::TO, p);
}

void
Application::
moveBy(const CPoint2D &p)
{
  move(MoveType::BY, p);
}

void
Application::
move(const MoveType &moveType, const CPoint2D &p)
{
  CPoint2D p1 = snapPoint(p);

  if (selectedPoint_ >= 0) {
    CPoint2D p2 = pointDataPos(selectedPoint_);

    if      (moveType == MoveType::TO)
      p2 = p1;
    else if (moveType == MoveType::BY)
      p2 += p1;

    if (pointsType() == PointsType::DRAW)
      shapeData_.setDrawPoint(selectedPoint_, p2);
    else
      shapeData_.setCollisionPoint(selectedPoint_, p2);

    updateAll();
  }
}

void
Application::
deleteSelected()
{
  if (selectedPoint_ >= 0) {
    if (pointsType() == PointsType::DRAW)
      shapeData_.removeDrawPoint(selectedPoint_);
    else
      shapeData_.removeCollisionPoint(selectedPoint_);

    selectedPoint_ = -1;
    previewPoint_  = -1;

    updateAll();
  }
}

int
Application::
nearestPoint(const CPoint2D &p) const
{
  class MinDist {
   public:
    MinDist(const CPoint2D &p, double delta) :
     p_(p), delta_(delta) {
    }

    double minDist() const { return minD_; }

    int minPoint() const { return minPoint_; }

    bool update(int pointNum, const CPoint2D &p) {
      double d = std::hypot(p_.x - p.x, p_.y - p.y);

      if (minPoint_ < 0 || d < minD_) {
        minD_     = d;
        minPoint_ = pointNum;
      }

      return (minD_ < delta_);
    }

   private:
    CPoint2D p_;
    double   delta_    { 1E-3 };
    double   minD_     { 1E50 };
    int      minPoint_ { -1 };
  };

  //---

  MinDist minDist(p, delta());

  int i = 0;

  if (pointsType() == PointsType::DRAW) {
    for (const auto &point : shapeData_.drawPoints()) {
      if (minDist.update(i, point))
        break;

      ++i;
    }
  }
  else {
    for (const auto &point : shapeData_.collisionPoints()) {
      if (minDist.update(i, point))
        break;

      ++i;
    }
  }

//std::cerr << p << " " << minDist.minDist() << "\n";

  if (minDist.minDist() > delta())
    return -1;

  return minDist.minPoint();
}

int
Application::
nearestLine(const CPoint2D &p) const
{
  class MinDist {
   public:
    MinDist(const CPoint2D &p, double delta) :
     p_(p), delta_(delta) {
    }

    double minDist() const { return minD_; }

    int minLine() const { return minLine_; }

    bool update(int lineNum, const CLine2D &line) {
      double d;

      if (! CMathGeom2D::PointLineDistance(p_, line, &d))
        return false;

      if (minLine_ < 0 || d < minD_) {
        minD_    = d;
        minLine_ = lineNum;
      }

      return (minD_ < delta_);
    }

   private:
    CPoint2D p_;
    double   delta_   { 1E-3 };
    double   minD_    { 1E50 };
    int      minLine_ { -1 };
  };

  //---

  MinDist minDist(p, delta());

  if (pointsType() == PointsType::DRAW) {
    int np = shapeData_.numDrawPoints();

    int i1 = np - 1;

    for (int i2 = 0; i2 < np; i1 = i2++) {
      CLine2D line(shapeData_.drawPoint(i1), shapeData_.drawPoint(i2));

      if (minDist.update(i1, line))
        break;
    }
  }
  else {
    int np = shapeData_.numCollisionPoints();

    int i1 = np - 1;

    for (int i2 = 0; i2 < np; i1 = i2++) {
      CLine2D line(shapeData_.collisionPoint(i1), shapeData_.collisionPoint(i2));

      if (minDist.update(i1, line))
        break;
    }
  }

//std::cerr << p << " " << minDist.minDist() << "\n";

  if (minDist.minDist() > delta())
    return -1;

  return minDist.minLine();
}

CPoint2D
Application::
pointDataPos(int i) const
{
  if (i >= 0) {
    if (pointsType() == PointsType::DRAW)
      return shapeData_.drawPoint(i);
    else
      return shapeData_.collisionPoint(i);
  }
  else
    return CPoint2D(-999,-999);
}

CPoint2D
Application::
snapPoint(const CPoint2D &p) const
{
  return CPoint2D(int(p.x/delta())*delta(), int(p.y/delta())*delta());
}

void
Application::
increaseLineWidth()
{
  lineWidth_ += 1;

  updateAll();
}

void
Application::
decreaseLineWidth()
{
  if (lineWidth_ > 1) {
    lineWidth_ -= 1;

    updateAll();
  }
}

void
Application::
moveStateSlot()
{
  state_ = State::MOVE;

  updateState();
}

void
Application::
addStateSlot()
{
  state_ = State::ADD;

  updateState();
}

void
Application::
deleteStateSlot()
{
  state_ = State::DELETE;

  updateState();
}

void
Application::
drawPointsSlot()
{
  setPointsType(Application::PointsType::DRAW);
}

void
Application::
collisionPointsSlot()
{
  setPointsType(Application::PointsType::COLLISION);
}

void
Application::
resetPoints()
{
  if (pointsType_ == PointsType::DRAW)
    CAsteroidsShapeMgrInst->resetDrawPoints(shapeData_.type());
  else
    CAsteroidsShapeMgrInst->resetCollisionPoints(shapeData_.type());

  shapeData_.resetPoints();

  selectedPoint_ = -1;

  updateAll();
}

void
Application::
updateAll()
{
  update();

  updateState();
}

void
Application::
updateState()
{
  QString str;

  str += "Shape=" + QString(CAsteroidsShapeMgrInst->typeName(shapeData_.type()).c_str());

  str += " Mode=";

  if      (state_ == State::MOVE)
    str += "Move";
  else if (state_ == State::ADD)
    str += "Add";
  else if (state_ == State::DELETE)
    str += "Delete";

  if (pointsType_ == PointsType::DRAW)
    str += "Points: Draw";
  else
    str += "Points: Collision";

  stateLabel_->setText(str);
}

//---------

Canvas::
Canvas(Application *app, const std::string &name) :
 QWidget(app), app_(app)
{
  setObjectName(name.c_str());

  double margin = 0.1;

  range_.setWindowRange(-(1.0 + margin), -(1.0 + margin), 1.0 + margin, 1.0 + margin);

  setFocusPolicy(Qt::StrongFocus);

  setMouseTracking(true);
}

void
Canvas::
paintEvent(QPaintEvent *)
{
  QPainter painter(this);

  painter.setRenderHints(QPainter::Antialiasing);

  painter.fillRect(rect(), QBrush(QColor(0,0,0)));

  painter.setWorldMatrix(CQUtil::toQMatrix(range_.getMatrix()));

  app_->draw(&painter);
}

void
Canvas::
resizeEvent(QResizeEvent *)
{
  range_.setPixelRange(0, 0, width() - 1, height() - 1);
}

void
Canvas::
keyPressEvent(QKeyEvent *e)
{
  if      (e->key() == Qt::Key_Left)
    app_->moveBy(CPoint2D(-app_->delta(), 0));
  else if (e->key() == Qt::Key_Right)
    app_->moveBy(CPoint2D( app_->delta(), 0));
  else if (e->key() == Qt::Key_Down)
    app_->moveBy(CPoint2D(0, -app_->delta()));
  else if (e->key() == Qt::Key_Up)
    app_->moveBy(CPoint2D(0,  app_->delta()));
  else if (e->key() == Qt::Key_Escape)
    app_->escape();
  else if (e->key() == Qt::Key_PageDown)
    app_->prevShape();
  else if (e->key() == Qt::Key_PageUp)
    app_->nextShape();
  else if (e->key() == Qt::Key_A)
    app_->addStateSlot();
  else if (e->key() == Qt::Key_M)
    app_->moveStateSlot();
  else if (e->key() == Qt::Key_Delete)
    app_->deleteStateSlot();
  else if (e->key() == Qt::Key_C)
    app_->collisionPointsSlot();
  else if (e->key() == Qt::Key_D)
    app_->drawPointsSlot();

  update();
}

void
Canvas::
mousePressEvent(QMouseEvent *e)
{
  CPoint2D p;

  range_.pixelToWindow(CPoint2D(e->x(), e->y()), p);

  app_->mousePress(p);
}

void
Canvas::
mouseMoveEvent(QMouseEvent *e)
{
  CPoint2D p;

  range_.pixelToWindow(CPoint2D(e->x(), e->y()), p);

  app_->mouseMove(p);
}

void
Canvas::
mouseReleaseEvent(QMouseEvent *e)
{
  CPoint2D p;

  range_.pixelToWindow(CPoint2D(e->x(), e->y()), p);

  app_->mouseRelease(p);
}
