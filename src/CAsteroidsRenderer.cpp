#include <CAsteroidsRenderer.h>

void
CAsteroidsRenderer::
drawPolygon(const Points &points)
{
  int i1 = int(points.size() - 1);
  int i2 = 0;

  for ( ; i2 < int(points.size()); ++i2) {
    drawLine(points[uint(i1)], points[uint(i2)]);

    i1 = i2;
  }
}

void
CAsteroidsRenderer::
fillPolygon(const Points &points)
{
  int i1 = int(points.size() - 1);
  int i2 = 0;

  for ( ; i2 < int(points.size()); ++i2) {
    drawLine(points[uint(i1)], points[uint(i2)]);

    i1 = i2;
  }
}
