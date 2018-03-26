class CAsteroidsShip : public CAsteroidsObject {
 private:
  static CPoint2D draw_coords_[];
  static uint     num_draw_coords_;

  static CPoint2D collision_coords_[];
  static uint     num_collision_coords_;

  CAsteroidsBulletMgr bullet_mgr_;

  double rotateSpeed_;
  double thrust_;
  double thrustMax_;
  double bulletSize_;
  double bulletSpeed_;
  double bulletLife_;
  int    bulletNum_;

  int ai_;

  bool visible_;

 public:
  CAsteroidsShip(const CAsteroids &app,
                 double  x=0.5, double  y=0.5, double  a=0.0,
                 double dx=0.0, double dy=0.0, double da=0.0);

  void init();

  void setVisible(bool visible) { visible_ = visible; }

  void move();

  void intersect();

  void turnLeft();
  void turnRight();
  void turnStop();
  void thrust();
  bool fire();
  void hyperspace();

  void draw();
};
