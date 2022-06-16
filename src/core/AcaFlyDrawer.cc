#include <cmath>
#include <iostream>
#include <GL/glut.h>

#include "AcaFly.h"

// left uninitialized
AcaFlyDrawer * g_drawer = nullptr;

AcaFlyDrawer::AcaFlyDrawer(int argc, char * argv[], GLfloat canvas_size, bool double_buffer, unsigned int refresh_interval)
  : title("AcaFlyDrawer"), double_buffer(double_buffer), canvas_size(canvas_size), refresh_interval(refresh_interval),
  _eyex(0), _eyey(0), _eyez(1),
  _centerx(0), _centery(0), _centerz(0),
  _upx(0), _upy(1), _upz(0),
  _fovy(60.0), _aspect(1.0), _zNear(0.1), _zFar(10)
{
  glutInit(&argc, argv);
}

AcaFlyDrawer::~AcaFlyDrawer()
{}

void AcaFlyDrawer::set_title(std::string title)
{
  this->title = title;
}

void AcaFlyDrawer::setLookAt(GLdouble eyex, GLdouble eyey, GLdouble eyez,
    GLdouble centerx, GLdouble centery, GLdouble centerz,
    GLdouble upx, GLdouble upy, GLdouble upz)
{
  _eyex = eyex;
  _eyey = eyey;
  _eyez = eyez;
  _centerx = centerx;
  _centery = centery;
  _centerz = centerz;
  _upx = upx;
  _upy = upy;
  _upz = upz;
}

void AcaFlyDrawer::setPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
  _fovy = fovy;
  _aspect = aspect;
  _zNear = zNear;
  _zFar = zFar;
}

void AcaFlyDrawer::set_color(GLDCOLOR color)
{
  switch (color) {
    case GLD_BLACK:
      set_color(0, 0, 0, 0);
      break;
    case GLD_RED:
      set_color(1, 0, 0, 0);
      break;
    case GLD_GREEN:
      set_color(0, 1, 0, 0);
      break;
    case GLD_BLUE:
      set_color(0, 0, 1, 0);
      break;
    case GLD_YELLOW:
      set_color(1, 1, 0, 0);
      break;
    case GLD_ORANGE:
      set_color(1, 0.5f, 0, 0);
      break;
    case GLD_WHITE:
    default:
      set_color(1, 1, 1, 0);
      break;
  }
}

void AcaFlyDrawer::set_color(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
  glColor4f(r, g, b, a);
}

void AcaFlyDrawer::line(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLDCOLOR color)
{
  set_color(color);
  glBegin(GL_LINES);
  glVertex2f(x1, y1);
  glVertex2f(x2, y2);
  glEnd();
}

void AcaFlyDrawer::circle(GLfloat x, GLfloat y, GLfloat radius, GLDCOLOR color)
{
  GLfloat PI = 3.1415926536f;
  int n = 3600;

  set_color(color);
  glBegin(GL_POLYGON);
  for (int i = 0; i < n; i++) {
    glVertex2f(x + radius * cos(2*PI*i/n), y + radius * sin(2*PI*i/n));
  }
  glEnd();
}

void AcaFlyDrawer::pie(GLfloat x, GLfloat y, GLfloat radius, std::vector<AcaFlyDrawer::PiePiece> pieces)
{
  GLfloat PI = 3.1415926536f;
  int n = 3600;
  int last_end = 0;
  for (AcaFlyDrawer::PiePiece piece : pieces) {
    int new_end = (int)(n * piece.percentage) + last_end;

    set_color(piece.color);
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    for (int i = last_end; i < new_end; i++) {
      glVertex2f(x + radius * cos(2*PI*i/n), y + radius * sin(2*PI*i/n));
    }
    glEnd();

    last_end = new_end;
  }
}

void AcaFlyDrawer::timer_refresh(int id)
{
  if (!g_drawer)  return;
  glutTimerFunc(g_drawer->refresh_interval, timer_refresh, 0);
}

void AcaFlyDrawer::display_wrapper(void)
{
  if (!g_drawer)	return;

  // Clear the board!
  glClear(GL_COLOR_BUFFER_BIT);

  // Let's draw!
  g_drawer->display();

  // Flush!
  if (g_drawer->double_buffer) {
    glutSwapBuffers();
  }
  else {
    glFlush();
  }
}

void AcaFlyDrawer::resize(GLsizei w, GLsizei h)
{
  if (h == 0)
    h = 1;

  // update information in g_drawer
  /*
  GLfloat canvas_size = g_drawer->canvas_size;
  GLfloat new_w = w <= h ? canvas_size : canvas_size * w/h;
  GLfloat new_h = w <= h ? canvas_size * h/w : canvas_size;
  g_drawer->_w = new_w;
  g_drawer->_h = new_h;
  g_drawer->_aspect = ((GLfloat) w) / ((GLfloat) h);

  glViewport(0, 0, new_w, new_h);
  */
  g_drawer->_w = w;
  g_drawer->_h = h;
  g_drawer->_aspect = ((GLfloat) w) / ((GLfloat) h);

  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  g_drawer->_setPerspective();

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  g_drawer->_setLookAt();
}

void AcaFlyDrawer::show()
{
  glutInitDisplayMode((double_buffer ? GLUT_DOUBLE : GLUT_SINGLE) | GLUT_RGB);
  glutInitWindowSize(canvas_size, canvas_size);
  glutInitWindowPosition(200, 200);
  glutCreateWindow(title.c_str());
  glutDisplayFunc(display_wrapper);
  glutReshapeFunc(resize);
  glutTimerFunc(refresh_interval, timer_refresh, 0);
  glutMainLoop();
}

void AcaFlyDrawer::post_redraw()
{
  glutPostRedisplay();
}

void AcaFlyDrawer::_setLookAt()
{
  gluLookAt(_eyex, _eyey, _eyez, _centerx, _centery, _centerz, _upx, _upy, _upz);
}

void AcaFlyDrawer::_setPerspective()
{
  gluPerspective(_fovy, _aspect, _zNear, _zFar);
}
