package org.colinw.asteroids;

public class Matrix {
  private double m00_, m01_, m02_, m10_, m11_, m12_, m20_, m21_, m22_;
 
  Matrix() {
  }
  
  void setIdentity() {
    setInnerIdentity ();
    setOuterIdentity ();
    setBottomIdentity();
  }
  void setRotation(double a) {
    setInnerRotation (a);
    setOuterIdentity ();
    setBottomIdentity();
  }
  
  public Point multiplyPoint(double xi, double yi) {
    double xo = m00_*xi + m01_*yi + m02_;
    double yo = m10_*xi + m11_*yi + m12_;
    
    return new Point(xo, yo);
  }

  public void setInnerRotation(double a) {
    double c = Math.cos(a);
    double s = Math.sin(a);

    m00_ =  c; m01_ = -s;
    m10_ =  s; m11_ =  c;
  }

  void setInnerIdentity() {
    m00_ = 1.0; m01_ = 0.0;
    m10_ = 0.0; m11_ = 1.0;
  }

  public void setOuterIdentity() {
    m02_ = 0.0; m12_ = 0.0;
  }

  public void setBottomIdentity() {
    m20_ = 0.0; m21_ = 0.0; m22_ = 1.0;
  } 
}
