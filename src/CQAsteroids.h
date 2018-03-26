#include <QWidget>

class Canvas;
class CAsteroids;
class CQAsteroidsRenderer;
class QTimer;
class CQSound;

class CQAsteroids : public QWidget {
  Q_OBJECT

 private:
  Canvas              *canvas_;
  CAsteroids          *asteroids_;
  CQAsteroidsRenderer *renderer_;
  QTimer              *timer_;
  CQSound             *fire_sound_;
  CQSound             *thrust_sound_;

 public:
  CQAsteroids();
 ~CQAsteroids();

  QSize sizeHint() const { return QSize(600,600); }

  void newGame();

  void shipTurnLeft();
  void shipTurnRight();
  void shipThrust();
  void shipFire();
  void shipHyperspace();

  void draw(QPainter *painter);

 private slots:
  void update();
};
