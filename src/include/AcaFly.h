#ifndef __INCLUDE_ACAFLY_H__
#define __INCLUDE_ACAFLY_H__

#include <GL/gl.h>
#include <vector>
#include <string>

#define DEFAULT_CANVAS_SIZE 500
#define DEFAULT_REFRESH_INTERVAL 30

class AcaFlyDrawer {
  std::string title;
  bool double_buffer;
  GLfloat canvas_size;
  unsigned int refresh_interval;
protected:
  GLsizei _w;
  GLsizei _h;
  GLdouble _eyex;
  GLdouble _eyey;
  GLdouble _eyez;
  GLdouble _centerx;
  GLdouble _centery;
  GLdouble _centerz;
  GLdouble _upx;
  GLdouble _upy;
  GLdouble _upz;
  GLdouble _fovy;
  GLdouble _aspect;
  GLdouble _zNear;
  GLdouble _zFar;
public:
  enum GLDCOLOR {
    GLD_BLACK = 0,
    GLD_RED,
    GLD_GREEN,
    GLD_BLUE,
    GLD_YELLOW,
    GLD_ORANGE,
    GLD_WHITE,
  };

  AcaFlyDrawer(int argc, char * argv[], GLfloat canvas_size = DEFAULT_CANVAS_SIZE, bool double_buffer = false, unsigned int refresh_interval = DEFAULT_REFRESH_INTERVAL);
  virtual ~AcaFlyDrawer();

  void set_title(std::string title);

  void setLookAt(GLdouble eyex, GLdouble eyey, GLdouble eyez,
                 GLdouble centerx, GLdouble centery, GLdouble centerz,
                 GLdouble upx, GLdouble upy, GLdouble upz);
  void setPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);

  void set_color(GLDCOLOR color);
  void set_color(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

  void line(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLDCOLOR color = GLD_WHITE);
  void circle(GLfloat x, GLfloat y, GLfloat radius, GLDCOLOR color = GLD_WHITE);
public:
  struct PiePiece {
    GLfloat percentage;
    GLDCOLOR color;
    PiePiece(GLfloat percentage, GLDCOLOR color) : percentage(percentage), color(color) {}
  };
  void pie(GLfloat x, GLfloat y, GLfloat radius, std::vector<PiePiece> pieces);

private:
  static void timer_refresh(int id);
  static void resize(GLsizei w, GLsizei h);
  static void display_wrapper(void);
protected:
  virtual void display() = 0;

  // wraps gluLookAt() and gluPerspective() in GL/glu.h
  void _setLookAt();
  void _setPerspective();

public:
  void show();
  void post_redraw();
};

extern AcaFlyDrawer * g_drawer;

#endif /* include/AcaFlyDrawer.h */
