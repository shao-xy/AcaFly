#include <GL/glut.h>
#include "AcaFly.h"

class TestDrawer : public AcaFlyDrawer {
public:
  TestDrawer(int argc, char * argv[]);
protected:
  void display() override;
};

TestDrawer::TestDrawer(int argc, char * argv[])
  : AcaFlyDrawer(argc, argv)
{
}

void TestDrawer::display()
{
  set_color(AcaFlyDrawer::GLD_YELLOW);
  glutWireTeapot(0.5);
}

int main(int argc, char * argv[])
{
  g_drawer = new TestDrawer(argc, argv);
  g_drawer->setLookAt(0, 1, 1, 0, 0, 0, 0, 1, 0);
  g_drawer->show();
  return 0;
}
