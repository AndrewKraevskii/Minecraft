#include "Keyboard.h"

#include <glut.h>

#include <iostream>

bool Keyboard::is_button_down[256];
bool Keyboard::is_special_down[21];

std::vector<std::function<void(unsigned char, int, int)>>
    Keyboard::callbacks_down;
std::vector<std::function<void(unsigned char, int, int)>>
    Keyboard::callbacks_up;
std::vector<std::function<void(int, int, int)>>
    Keyboard::special_callbacks_down;
std::vector<std::function<void(int, int, int)>> Keyboard::special_callbacks_up;

void Keyboard::init() {
  for (auto& element : is_button_down) {
    element = false;
  }
  glutKeyboardFunc(button_down);
  glutKeyboardUpFunc(button_up);
  glutSpecialFunc(special_down);
  glutSpecialUpFunc(special_up);
}

void Keyboard::button_down(unsigned char key, int x, int y) {
  if (key >= 128)
    return;  // некоректно работает с символами с русской раскладки. Поэтому
             // придётся ограничить ввод

  if (is_button_down[key] == false) {
    for (auto& func : callbacks_down) {
      func(key, x, y);
    }
  }
  is_button_down[key] = true;

  std::cout << key << " down\n";
}

void Keyboard::button_up(unsigned char key, int x, int y) {
  if (key >= 128)
    return;  // некоректно работает с символами с русской раскладки. Поэтому
             // придётся ограничить ввод

  if (is_button_down[key]) {
    for (auto& func : callbacks_up) {
      func(key, x, y);
    }
  }
  is_button_down[key] = false;
  std::cout << key << " up\n";
}

void Keyboard::special_down(int key, int x, int y) {
  if (key <= GLUT_KEY_F12) {
    if (is_special_down[key - 1] == false) {
      for (auto& func : special_callbacks_down) {
        func(key, x, y);
      }
    }
    is_special_down[key - 1] = true;
  } else {
    if (is_special_down[key - GLUT_KEY_LEFT + GLUT_KEY_F12] == false) {
      for (auto& func : special_callbacks_down) {
        func(key, x, y);
      }
    }
    is_special_down[key - GLUT_KEY_LEFT + GLUT_KEY_F12] = true;
  }
}
void Keyboard::special_up(int key, int x, int y) {
  if (key <= GLUT_KEY_F12) {
    if (is_special_down[key - 1]) {
      for (auto& func : special_callbacks_down) {
        func(key, x, y);
      }
    }
    is_special_down[key - 1] = false;
  } else {
    if (is_special_down[key - GLUT_KEY_LEFT + GLUT_KEY_F12]) {
      for (auto& func : special_callbacks_down) {
        func(key, x, y);
      }
    }
    is_special_down[key - GLUT_KEY_LEFT + GLUT_KEY_F12] = false;
  }
}

bool Keyboard::is_special_pressed(int key) {
  if (key <= GLUT_KEY_F12) {
    return is_special_down[key - 1];
  }

  return is_special_down[key - GLUT_KEY_LEFT + GLUT_KEY_F12];
}

bool Keyboard::is_button_pressed(unsigned char key) {
  return is_button_down[key];
}

void Keyboard::callback_down(void (*func)(unsigned char key, int x, int y)) {
  callbacks_down.push_back(func);
}

void Keyboard::callback_up(void (*func)(unsigned char key, int x, int y)) {
  callbacks_up.push_back(func);
}

void Keyboard::special_callback_down(void (*func)(int key, int x, int y)) {
  special_callbacks_down.push_back(func);
}

void Keyboard::special_callback_up(void (*func)(int key, int x, int y)) {
  special_callbacks_up.push_back(func);
}

int Keyboard::get_modifiers() { return glutGetModifiers(); }
