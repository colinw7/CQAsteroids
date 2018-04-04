package org.colinw.asteroids;

public class AsteroidsObject {
  protected AsteroidsView     view_;

  protected double            x_;
  protected double            y_;
  protected double            a_;
  protected double            dx_;
  protected double            dy_;
  protected double            da_;
  protected double            size_;
  protected int               score_;
  protected boolean           wrap_on_edge_;

  protected Matrix            matrix_;
  protected boolean           remove_;

  protected Point             draw_coords_[];
  protected Point             draw_coords1_[];
  protected int               num_draw_coords_;

  protected Point             coll_coords_[];
  protected Point             coll_coords1_[];
  protected int               num_coll_coords_;

  protected BBox              bbox_;

  public AsteroidsObject(AsteroidsView view, double x, double y, double a, double dx, double dy, double da,
                         double size, int score, boolean wrap_on_edge) {
    view_ = view;
    x_    = x;
    y_    = y;
    a_    = a;
    dx_   = dx;
    dy_   = dy;
    da_   = da;
   
    size_  = size;
    score_ = score;

    wrap_on_edge_ = wrap_on_edge;
   
    matrix_ = new Matrix();
    
    remove_ = false;
    
    num_draw_coords_ = 0;
    num_coll_coords_ = 0;

    bbox_ = new BBox();

    matrix_.setRotation(2*Math.PI*a_);
  }

  public void setRemove() { remove_ = true; }

  public boolean getRemove() { return remove_; }

  public void setDrawCoords(Point draw_coords[], int num_draw_coords) {
    num_draw_coords_ = num_draw_coords;

    draw_coords_  = new Point[num_draw_coords];
    draw_coords1_ = new Point[num_draw_coords];

    for (int i = 0; i < num_draw_coords; ++i) {
      draw_coords_ [i] = new Point(draw_coords[i]);
      draw_coords1_[i] = new Point(draw_coords[i]);
    }

    updateDrawCoords();
  }

  public void setCollisionCoords(Point coll_coords[], int num_coll_coords) {
    num_coll_coords_ = num_coll_coords;

    coll_coords_  = new Point[num_coll_coords];
    coll_coords1_ = new Point[num_coll_coords];

    for (int i = 0; i < num_coll_coords; ++i) {
      coll_coords_ [i] = new Point(coll_coords[i]);
      coll_coords1_[i] = new Point(coll_coords[i]);
    }

    updateCollisionCoords();
  }

  public void move() {
    x_ += dx_;
    y_ += dy_;
    a_ += da_;

    if (wrap_on_edge_) {
      if (x_ > 1.0) x_ = 0.0;
      if (x_ < 0.0) x_ = 1.0;
      if (y_ > 1.0) y_ = 0.0;
      if (y_ < 0.0) y_ = 1.0;
    }
    else {
      if (x_ > 1.0) remove_ = true;
      if (x_ < 0.0) remove_ = true;
      if (y_ > 1.0) remove_ = true;
      if (y_ < 0.0) remove_ = true;
    }

    if (a_ < 0.0) a_ += 1.0;
    if (a_ > 1.0) a_ -= 1.0;

    matrix_.setRotation(2*Math.PI*a_);

    updateDrawCoords();
    updateCollisionCoords();
  }

  public void intersect() { }

  public boolean pointInside(double x, double y) {
    if (! bbox_.inside(x, y))
      return false;

    Polygon poly = new Polygon(coll_coords1_, num_coll_coords_);

    return poly.inside(x, y);
  }

  public void draw() {
    if (remove_) return;

    int i1 = num_draw_coords_ - 1;
    int i2 = 0;

    for ( ; i2 < num_draw_coords_; ++i2) {
      view_.drawLine(draw_coords1_[i1].x(), draw_coords1_[i1].y(),
                     draw_coords1_[i2].x(), draw_coords1_[i2].y());

      i1 = i2;
    }
  }

  public void hit() {
    remove_ = true;

    view_.addScore(score_);
  }

  public void cleanup() {
  }

  private void updateDrawCoords() {
    double x, y;

    for (int i = 0; i < num_draw_coords_; i++) {
      x = draw_coords_[i].x()*size_;
      y = draw_coords_[i].y()*size_;

      Point p = matrix_.multiplyPoint(x, y);
      
      draw_coords1_[i].setX(p.x() + x_);
      draw_coords1_[i].setY(p.y() + y_);
    }

    bbox_.reset();

    for (int i = 0; i < num_draw_coords_; ++i)
      bbox_.add(draw_coords1_[i].x(), draw_coords1_[i].y());
  }

  private void updateCollisionCoords() {
    double x, y;

    for (int i = 0; i < num_coll_coords_; i++) {
      x = coll_coords_[i].x()*size_;
      y = coll_coords_[i].y()*size_;

      Point p = matrix_.multiplyPoint(x, y);
      
      coll_coords1_[i].setX(p.x() + x_);
      coll_coords1_[i].setY(p.y() + y_);
    }
  }
}
