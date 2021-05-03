#include <glut.h>
#include <stdlib.h>

#include <iostream>
#include <vector>

#include "model3d.h"
#include "vectors.h"

#define FPS 60

double get_time() {
  static clock_t start_time = clock();
  return (double)(clock() - start_time) / CLOCKS_PER_SEC;
}

void Init() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_ALPHA_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);
  glClearColor(1, 1, 1, 0);
}

void Idle() {
  static double last = get_time();
  std::cout << get_time() - last << "\n";
  last = get_time();

  glutPostRedisplay();
}

void Reshape(int w, int h) {
  Vector2i window_size(w, h);

  double alpha = (double)w / h;

  glViewport(0, 0, window_size.x, window_size.y);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(60, alpha, 0.1, 100);

  gluLookAt(5, 0, 0, 0, 0, 0, 0, 0, 1);
  glMatrixMode(GL_MODELVIEW);
}

void Keyboard(unsigned char key, int x, int y) {
  Vector2i mouse_position(x, y);
  if (key == 27) exit(0);
}

void Special(int key, int x, int y) {
  Vector2i mouse_position(x, y);
  if (key == GLUT_KEY_F4 && (glutGetModifiers() & GLUT_ACTIVE_ALT)) {
    exit(0);
  }
}

void Display() {
  glPushMatrix();
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    static Model3d obj("block.obj", "block.bmp");
    glRotated(get_time() * 200, 0, 1, 0.5);
    obj.draw();
    glFinish();
    glDisable(GL_TEXTURE_2D);
  }
  glPopMatrix();
}

void timer(int extra) {
  Idle();
  glutTimerFunc(1000 / FPS, timer, 0);
}

int main() {
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowPosition(30, 40);
  glutInitWindowSize(640, 480);
  glutCreateWindow("mine");

  glutKeyboardFunc(Keyboard);
  glutReshapeFunc(Reshape);
  glutDisplayFunc(Display);
  glutSpecialFunc(Special);

  glutTimerFunc((double)1 / FPS, timer, 0);

  // glutIdleFunc(Idle);

  Init();

  glutMainLoop();

  return 0;
}