#ifndef CAsteroidsBigRock_H
#define CAsteroidsBigRock_H

class CAsteroidsBigRock : public CAsteroidsRock {
 public:
  CAsteroidsBigRock(const CAsteroids &app,
                    double x, double y, double a,
                    double dx, double dy, double da);

  void hit();

 private:
  static double default_size_;
};

#endif
