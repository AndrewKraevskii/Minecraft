#include <glut.h>
#include <math.h>
#include <stdlib.h>

#include <iostream>
#include <vector>

#include "Camera.h"
#include "Keyboard.h"
#include "model3d.h"
#include "vectors.h"

#define FPS 60
#define MOUSE_SENSE_X 0.001
#define MOUSE_SENSE_Y 0.001
#define SPEED 3

Camera camera({-5, 0, 0}, {0, 1, 0}, {0, 0, 1});
Vector2i mouse = {-1, -1};

double get_time() {
  static clock_t start_time = clock();
  return (double)(clock() - start_time) / CLOCKS_PER_SEC;
}

void glutInit() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_ALPHA_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);
  glClearColor(0, 0, 0, 0);
}

void Idle() {
  static double last = get_time();
  // std::cout << 1 / (get_time() - last) << "\n";
  double pass_time = get_time() - last;
  last = get_time();

  if (Keyboard::is_button_pressed('w') || Keyboard::is_button_pressed('ö')) {
    camera.movelocal(Vector3d({SPEED, 0, 0}) * pass_time);
  }
  if (Keyboard::is_button_pressed('s') || Keyboard::is_button_pressed('û')) {
    camera.movelocal(Vector3d{-SPEED, 0, 0} * pass_time);
  }
  if (Keyboard::is_button_pressed('a') || Keyboard::is_button_pressed('ô')) {
    camera.movelocal(Vector3d{0, SPEED, 0} * pass_time);
  }
  if (Keyboard::is_button_pressed('d') || Keyboard::is_button_pressed('â')) {
    camera.movelocal(Vector3d{0, -SPEED, 0} * pass_time);
  }

  glutPostRedisplay();
}

void Reshape(int w, int h) {
  Vector2i window_size(w, h);

  double alpha = (double)w / h;

  glViewport(0, 0, window_size.x, window_size.y);
}

void KeyboardFunc(unsigned char key, int x, int y) {
  Vector2i mouse_position(x, y);
  if (key == 27) exit(0);
}

void Special(int key, int x, int y) {
  Vector2i mouse_position(x, y);
  if (key == GLUT_KEY_F4 && (Keyboard::get_modifiers() & GLUT_ACTIVE_ALT)) {
    exit(0);
  }
}

void MouseMove(int x, int y) {
  if (mouse.x == -1 || mouse.y == -1) {
    mouse = {x, y};
    return;
  }

  Vector2i move = mouse - Vector2i{x, y};
  camera.rotate_g(MOUSE_SENSE_X * move.x);
  camera.rotate_v(MOUSE_SENSE_Y * move.y);

  mouse = {glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2};
  glutWarpPointer(mouse.x, mouse.y);
}

void Display() {
  // Camera movement
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(
      60, (double)glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT), 0.1,
      90);
  camera.put_camera();
  glMatrixMode(GL_MODELVIEW);

  // fps count
  static int frames = 0;
  frames++;
  static double last = get_time();
  if ((int)(get_time() - last)) {
    std::cout << "fps = " << 1.0 * frames / (get_time() - last) << "\n";
    last = get_time();
    frames = 0;
  }

  // objects draw
  glPushMatrix();
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);

    static Model3d obj("block.obj", "block.png");

    obj.draw();

    glTranslated(-5, 0, 5);
    obj.draw();
    glTranslated(0, 0, -10);
    obj.draw();
    glTranslated(0, 5, 5);
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

void Init() {
  Keyboard::init();
  Keyboard::callback_down(KeyboardFunc);
  Keyboard::special_callback_down(Special);
}

int main() {
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowPosition(30, 40);
  glutInitWindowSize(1000, 600);
  glutCreateWindow("mine");

  glutReshapeFunc(Reshape);
  glutDisplayFunc(Display);

  glutPassiveMotionFunc(MouseMove);

  glutTimerFunc((double)1 / FPS, timer, 0);
  // glutIdleFunc(Idle);
  glutInit();

  Init();

  glutMainLoop();

  return 0;
}
