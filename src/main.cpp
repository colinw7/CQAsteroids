#include <CQAsteroids.h>
#include <CQApp.h>

int
main(int argc, char **argv)
{
  CQApp app(argc, argv);

  CQAsteroidsApp asteroids;

  asteroids.show();

  return app.exec();
}
