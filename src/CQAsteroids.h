#include <QWidget>

class Canvas;
class CQAsteroids;
class CQAsteroidsRenderer;
class QTimer;
class CQSound;

class CQAsteroidsApp : public QWidget {
  Q_OBJECT

  Q_PROPERTY(bool filled  READ isFilled  WRITE setFilled )
  Q_PROPERTY(bool colored READ isColored WRITE setColored)

 public:
  CQAsteroidsApp();

 ~CQAsteroidsApp();

  CQAsteroids *asteroids() const { return asteroids_; }

  bool isFilled() const;
  void setFilled(bool b);

  bool isColored() const;
  void setColored(bool b);

  void newGame();

  void togglePause();

  void shipTurnLeft();
  void shipTurnRight();
  void shipTurnStop();

  void shipThrust();
  void shipStopThrust();

  void shipFire();

  void shipHyperspace();

  void draw(QPainter *painter);

  void playSound(const std::string &name);

  QSize sizeHint() const override { return QSize(1200,1200); }

 private slots:
  void update();

 private:
  Canvas*              canvas_        { nullptr };
  CQAsteroids*         asteroids_     { nullptr };
  CQAsteroidsRenderer* renderer_      { nullptr };
  QTimer*              timer_         { nullptr };
  CQSound*             fire_sound_    { nullptr };
  CQSound*             thrust_sound_  { nullptr };
  CQSound*             explode_sound_ { nullptr };
  CQSound*             hyper_sound_   { nullptr };
};
