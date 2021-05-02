#include <glut.h>
#include <stdlib.h>

#include "Block.h"
#include "Object3d.h"
#include "sfml_part/Vector2.hpp"
#include "sfml_part/Vector3.hpp"


double get_time() {
  static clock_t start_time = clock();
  return (double)(clock() - start_time) / CLOCKS_PER_SEC;
}

void Init() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  // glEnable(GL_LIGHT5);
  glEnable(GL_COLOR_MATERIAL);
}

void Idle() { glutPostRedisplay(); }

void Reshape(int w, int h) {
  sf::Vector2i window_size(w, h);

  double alpha = (double)h / w;

  glViewport(0, 0, window_size.x, window_size.y);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(60, 1 / alpha, 0.1, 100);
  // glOrtho(-1, 1, -alpha, +alpha, -100, 100);

  gluLookAt(5, 5, 5, 0, 0, 0, 0, 0, 1);
  glMatrixMode(GL_MODELVIEW);
}

void Keyboard(unsigned char key, int x, int y) {
  sf::Vector2i mouse_position(x, y);
  if (key == 27) exit(0);
}

void Special(int key, int x, int y) {
  sf::Vector2i mouse_position(x, y);
  if (key == GLUT_KEY_F4 && (glutGetModifiers() & GLUT_ACTIVE_ALT)) {
    exit(0);
  }
}

void Display() {
  glPushMatrix();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_TEXTURE_2D);
  //Block block({0, 0, 0}, {1, 1, 1}, {0, 0, 0});
  //block.Draw();
  static Object3d obj("block");
  glRotated(get_time() * 100, 0, 1, 0.3);
  obj.draw();
  glFinish();
  glDisable(GL_TEXTURE_2D);
  glPopMatrix();
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
  glutIdleFunc(Idle);
  Init();

  glutMainLoop();

  return 0;
}